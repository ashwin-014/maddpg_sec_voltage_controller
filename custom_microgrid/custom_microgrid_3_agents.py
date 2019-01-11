# core modules
import random
import math
import gym
import numpy as np
from gym import spaces
import tensorflow as tf
from itertools import chain, combinations
# import matplotlib.pyplot as plt
from collections import deque
import numpy as np
import matlab
# import matplotlib.pyplot as plt
import matlab.engine
from mat4py import loadmat, savemat
import logging
import h5py

# import subprocess
import os

LINE_VOLTAGE_MAX_LIMIT = 900
LINE_VOLTAGE_MIN_LIMIT = 650
LINE_CURRENT_MAX_LIMIT = 50
LINE_CURRENT_MIN_LIMIT = 2

LINE_CURRENT_RATED = 10
LINE_VOLTAGE_RATED = 750

SAMPLE_TIME = 0.01
TOTAL_SIM_TIME = 8
TOTAL_TIME_STEPS = int(TOTAL_SIM_TIME / SAMPLE_TIME)
REWARD_AMOUNT_COMMON = 100
"""

Custom implementation of openAI Gym environment API ( https://gym.openai.com/docs )

-- > Multi-agent system with each controller as agent

input state : output of each controller's voltage and current 
output state : Increase or decrease del_V to the primary droop controller ( Ops of neural network is equivalent to getting all other V and I values and averaging them, passing them through a PI controller and summing them )
obs dim ( dim of input )        :   num_controllers * 3 ( contimuous values )
action_dim ( dim of output )    :   num_controllers * 2 ( since action space is for the whole env and not for single agent ) ( discrete values )

each step runs the simulation till the current time step.
V and I for all agents are taken
only the local V and I are input to each neural network ( no communication )

xval is created as a timeseries to inpout to the sim in reqd format

input to the NN [ state ]   :   ( timestep, v, i )  //
output [ action ]           :   del_V               //  [0 or 1]  ( inc or dec )]

reward is calculated based on voltage and current levels

"""

class Agent():

    def __init__(self, agent_num):

        self.silent = True        
        self.v_level_failed= False
        self.i_level_failed= False
        self.vl = 750
        self.il = 10        
        self.del_v = 0
        self.del_i = 0
        self.state = np.asarray([0, LINE_VOLTAGE_RATED / LINE_VOLTAGE_RATED, LINE_CURRENT_RATED / LINE_CURRENT_RATED])
        self.input = np.zeros(TOTAL_TIME_STEPS)
        self.input_timeseries = np.stack([np.around(np.linspace(0, 8, TOTAL_TIME_STEPS), 2), self.input],axis=1)
        
        # if os.path.exists(self.input_file_name):
        #     os.remove(self.input_file_name)
        # else:
        #     logging.debug("not able to remove file...")
        
        # with open(self.input_file_name, 'w') as f : pass # .close()
        self.input_file_name = "D:\\maddpg_sec_conrtoller\\custom_microgrid\\input_" + str(agent_num) + ".mat"
        savemat(self.input_file_name, {'input_'+str(agent_num) : np.transpose(self.input_timeseries).tolist()})
        # self.check_input_file = h5py.File(self.input_file_name, "r")
        # self.check_input = self.check_input_file.get('input_' + str(agent_num))
        # self.check_input = np.array(self.check_input)
        self.check_input = loadmat(self.input_file_name)
        self.cost = 0
        self.reward = 0

    def reset(self, agent_num):
        self.state = np.asarray([0, LINE_VOLTAGE_RATED / LINE_VOLTAGE_RATED, LINE_CURRENT_RATED / LINE_CURRENT_RATED])
        self.v_level_failed= False
        self.i_level_failed= False
        self.vl = 750
        self.il = 10        
        self.del_v = 0
        self.del_i = 0
        self.input = np.zeros(TOTAL_TIME_STEPS)
        self.input_timeseries = np.stack([np.around(np.linspace(0, 8, TOTAL_TIME_STEPS), 2), self.input],axis=1)
        savemat(self.input_file_name, {'input_'+str(agent_num) : np.transpose(self.input_timeseries).tolist()})
        self.check_input = loadmat(self.input_file_name)
        # open(self.input_file_name, 'w').close()
        
        self.cost = 0
        self.reward = 0


class Make_World():
    def __init__(self, num_agents = 3):
        self.agents = []
        self.dim_phasors = 3    # may come into use later
        self.dim_c = 0          # may come into use later

        logging.debug('init microgrid .... !!')

        for i in range(num_agents):
            logging.debug("agent_ {0}".format (i))

            self.agents.append(Agent(agent_num = i)) 

    def get_agents(self):
        return self.agents

class SecondaryController(gym.Env) :

    def __init__(self, num_agents = 3,  eng_name = None):
        
        self.num_agents = num_agents
        self.n = num_agents
        
        self.action_space = []
        self.observation_space = []
        self.discrete_action_space = True
        self.world = Make_World(num_agents=self.num_agents)
        self.agents = self.world.get_agents()
        logging.debug(len(self.agents))
        self.curr_episode = 0

        self.penalty = 10
        self.del_v = 0
        self.del_i = 0
        self.delta_v_change = 10 # (V) for changes in voltage to be multiplied to NN output
        # self.delta_i_change = 2 # (A)
        
        self.prev_len = 0
        self.full_signal = []

        self.tim = np.linspace(0, 10, num=TOTAL_TIME_STEPS)
        # self.xval = np.ones((1000, 2), dtype=float)

        # ------ action spaces init ------------
        action_dim = 3 # inc, dec and no change
        for agent in self.agents:
            total_action_space = []
            # physical action space
            if self.discrete_action_space:             
                # it can either increase or decrease voltage in steps. Dim = 2
                u_action_space = spaces.Discrete(action_dim) # self.world.dim_phasors *  2
                logging.debug("discrete {0}".format( u_action_space))
                # comm action space : for future work
                c_action_space = spaces.Discrete(self.world.dim_c)
            else:
                # can remove since it is not needed
                u_action_space = spaces.Box(low=LINE_VOLTAGE_MIN_LIMIT, high=LINE_VOLTAGE_MAX_LIMIT, shape=(2,2)) # ,dtype=np.float32
                logging.debug("absas {0}".format(u_action_space))
                c_action_space = spaces.Box(low=0.0, high=1.0, shape=(self.world.dim_c,)) # ,dtype=np.float32

            total_action_space.append(u_action_space)  
            logging.debug("asas {0}".format( total_action_space))          
        
            if not agent.silent:
                total_action_space.append(c_action_space)
            
            # Total action space 
            # only for comm case
            # not needed
            if len(total_action_space) > 1:
                # all action spaces are discrete, so simplify to MultiDiscrete action space
                if all([isinstance(act_space, spaces.Discrete) for act_space in total_action_space]):
                    act_space = spaces.MultiDiscrete([[0,act_space.n-1] for act_space in total_action_space])
                else:
                    act_space = spaces.Tuple(total_action_space)
                self.action_space.append(act_space)
            else:
                self.action_space.append(total_action_space[0])
            
            # -------------------------------------- removed print -----------------------------
            # print(np.asarray(self.action_space).shape)
            # ----------------------------------------------------------------

            # Is this Correct?
            # Voltage and current are observed
            obs_dim = 3 
            # should spaces be limited to rated values?
            self.observation_space.append(spaces.Box(low=-np.inf, high=+np.inf, shape=(obs_dim,))) # ,dtype=np.float32
            # ------------------------------------------
            # agent.action.c = np.zeros(self.world.dim_c)

        logging.debug("len act sp : {0}".format(len(self.action_space)))
        logging.debug("len obs sp : {0}".format(len(self.observation_space)))

        # ---------- matlab engine init -------------
        if eng_name is None:            
            names = matlab.engine.find_matlab()
            logging.debug(names)      
            self.eng = matlab.engine.connect_matlab(names[0])  
        
        logging.debug('succesfully connected\n\n')
        logging.debug('starting controls .. \n\n')
                

    def step(self, action_n):
        
        obs_n = []
        reward_n = []
        done_n = []
        info_n = {'n': []}

        # check for init state and start simulation:
        if self.curr_step ==0:
            self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','start',nargout=0)

        if self.time_is_over :
            # raise RuntimeError("Episode is done")
            self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','stop',nargout=0)
            logging.debug("Episode done : {0}".format(self.curr_episode))

        # set action for each agent and
        # advance microgrid state
        ## for i, agent in enumerate(self.agents):
        logging.debug("step : {0}".format(self.curr_step))
        self._set_action(action_n)
                
        # record observation,reward, done and info for each agent
        for k,agent in enumerate(self.agents):
            obs_n.append(self._get_obs(agent))
            reward_n.append(self._get_reward(agent))
            done_n.append(self._get_done())
            info_n['n'].append(self._get_info())

        if not self.time_is_over:
            self.curr_step += 1
        return obs_n, reward_n, done_n, info_n 

    def _get_info(self):
        # not implemented
        # for logging
        return {}

    # advance state by one timestep and also give actions to the agents
    # is action_space reqd ?
    def _set_action(self, action_n):
        
        # logging.debug("len agents : {0}".format(len(self.agents)))
        # logging.debug(len(action_n))
        # generate inputs for each controller chip        
        for i, agent in enumerate(self.agents):

            if np.argmax(action_n[i]) == 0 :
                delv = self.delta_v_change
            elif np.argmax(action_n[i]) == 1:
                delv = -self.delta_v_change
            else:
                delv= 0
            logging.debug("delv ----> : {0}".format(agent.del_v))
            if not self.curr_step >= 800: # TOTAL_TIME_STEPS
                # agent.input_timeseries[self.curr_step +1] = [self.tim[self.curr_step +1], agent.del_v]
                agent.input_timeseries[self.curr_step][1] = agent.del_v
            
            # write to file : 
            savemat(agent.input_file_name, {'input' : np.transpose(agent.input_timeseries).tolist()})
            agent.check_input = loadmat(agent.input_file_name)
            logging.debug("checking the last written voltage : {0}".format(agent.check_input))

        # self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','start',nargout=0)        
        # and simulate the microgrid
        # while self.eng.get_param('test_v_control_and_i_control_with_droop_copy','SimulationStatus')!=('stopped' or 'terminating'):            
        if self.eng.get_param('test_v_control_and_i_control_with_droop_copy','SimulationStatus')=='paused':
            # Trying changing constant value
            for i, agent in enumerate(self.agents):
                if np.argmax(action_n[i]) == 0:
                    curr_ref = int(self.eng.get_param('test_v_control_and_i_control_with_droop_copy/Vref'+str(i),'Value')) # ,nargout=0)
                    print("0", curr_ref, type(curr_ref))
                    self.eng.set_param('test_v_control_and_i_control_with_droop_copy/Vref'+str(i),'Value',str(curr_ref+1),nargout=0)
                if np.argmax(action_n[i]) == 1:
                    curr_ref = int(self.eng.get_param('test_v_control_and_i_control_with_droop_copy/Vref'+str(i),'Value')) # ,nargout=0)
                    print("1", curr_ref, type(curr_ref))
                    self.eng.set_param('test_v_control_and_i_control_with_droop_copy/Vref'+str(i),'Value',str(curr_ref-1),nargout=0)
                if np.argmax(action_n[i]) == 2:
                    curr_ref = int(self.eng.get_param('test_v_control_and_i_control_with_droop_copy/Vref'+str(i),'Value')) # ,nargout=0)
                    print("2", curr_ref, type(curr_ref))
                    self.eng.set_param('test_v_control_and_i_control_with_droop_copy/Vref'+str(i),'Value',str(curr_ref),nargout=0)

            # ToDo : operations check
            logging.debug("curr step : {0}".format(self.curr_step))
            self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','update',nargout=0) #if you have updated any simulation parameters
            
            if self.curr_step >= TOTAL_TIME_STEPS : # * SAMPLE_TIME:                    
                logging.debug("stopping.. : \t self.curr_step : {1}".format(self.curr_step))
                self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','stop',nargout=0)
            
            self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','continue',nargout=0)
            
        else:
            self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','stop',nargout=0)
            logging.debug("stopped *************************** error")
        
        self.full_signal = self.eng.workspace['V_out_1'].get('signals').get('values')     

        if self.curr_step <= 0 : 
            # return some safe value and wait till the transient settles
            return 0   

        # generate inputs to NN 
        for i, agent in enumerate(self.agents):
            agent.vl = np.array(self.eng.workspace['V_out_' + str(i)].get('signals').get('values')[-1], dtype=float)[0]
            logging.debug("Vl : {0}".format(agent.vl))
            agent.il = np.array(self.eng.workspace['I_out_' + str(i)].get('signals').get('values')[-1], dtype=float)[0]
            logging.debug("Il : {0}".format(agent.il))

            # not needed
            # agent.vl = agent.vl + action_n[i,0] * self.delta_v_change
            # agent.il = agent.il + action_n[i,1] * self.delta_i_change
            agent.del_v = float(LINE_VOLTAGE_RATED) - agent.vl
            agent.del_i = float(LINE_CURRENT_RATED) - agent.il            

            if  agent.vl  <= LINE_VOLTAGE_MIN_LIMIT and agent.vl >=LINE_VOLTAGE_MAX_LIMIT:
                logging.debug("V failed:")
                agent.v_level_failed = True

            if agent.il  <= LINE_CURRENT_MIN_LIMIT and agent.il >=LINE_CURRENT_MAX_LIMIT:
                logging.debug("I failed:")
                agent.i_level_failed = True
        self.prev_len = len(self.full_signal)


    def reset(self):
        self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','stop',nargout=0)

    def render(self):
        return

    def _get_reward(self, agent):

        if not(agent.v_level_failed) and not(agent.i_level_failed):
            agent.cost = agent.del_v *  self.penalty + agent.del_i * self.penalty        
        elif agent.v_level_failed and not(agent.i_level_failed):
            agent.cost = 100 + agent.del_i * self.penalty
        elif agent.i_level_failed and not(agent.v_level_failed):
            agent.cost = agent.del_v * self.penalty + 100             
        else:
            agent.cost = 200
        agent.reward = -agent.cost + REWARD_AMOUNT_COMMON
        
        return agent.reward

    def _get_obs(self, agent):

        agent.state = np.zeros(3)
        if not self.time_is_over:
            agent.state[0] =  self.curr_step+1
        else:
            agent.state[0] =  0
        agent.state[1] =  agent.vl / LINE_VOLTAGE_RATED
        agent.state[2] =  agent.il / LINE_CURRENT_RATED
        # ---------------------------------------- remove print -------------------------------
        logging.debug("state : {0}".format(agent.state))
        # ---------------------------------------------------------
        return agent.state

    def _get_done(self):

        remaining_steps = TOTAL_TIME_STEPS - self.curr_step+1
        self.time_is_over = (remaining_steps <= 0)
        
        return self.time_is_over

    def _get_initial_state(self):

        self.curr_episode += 1
        
        self.time_is_over = False
        self.total_rew = 0
        self.curr_step = 0
        self.prev_len = 0
        self.del_v = 0
        self.del_i = 0

        # self.agents = [Agent() for i in range(self.num_agents) ]
        for agent_num, agent in enumerate(self.agents):
            agent.reset(agent_num)

        initial_state_batch = [agent.state for agent in self.agents]
        
        return initial_state_batch



        # ---------------------------------- old set action ------------------------------------

    #     def _set_action(self, action_n):
        
    #     print("len agents : ", len(self.agents))
    #     print(len(action_n))
    #     # generate inputs for each controller chip
    #     for i, agent in enumerate(self.agents):

    #         if np.argmax(action_n[i]) == 0 :
    #             delv = self.delta_v_change
    #         elif np.argmax(action_n[i]) == 1:
    #             delv = -self.delta_v_change
    #         else:
    #             delv= 0

    #         # print(agent.input.shape)
    #         # print(np.full((TOTAL_TIME_STEPS - self.prev_len), delv).shape)
    #         agent.input[self.prev_len : ]=np.full((TOTAL_TIME_STEPS - self.prev_len), delv)

    #         agent.input_timeseries = np.stack([self.tim, agent.input], axis=1)        
    #         agent.input_timeseries = matlab.double(agent.input_timeseries.tolist())
    #         self.eng.workspace['input_' + str(i)] = agent.input_timeseries

    #     self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','start',nargout=0)
        
    #     # and simulate the microgrid
    #     j=0          
    #     while self.eng.get_param('test_v_control_and_i_control_with_droop_copy','SimulationStatus')!=('stopped' or 'terminating'):            
    #         if self.eng.get_param('test_v_control_and_i_control_with_droop_copy','SimulationStatus')=='paused':
    #             # operations check
    # #             print('%f  : %f' ,prev_len, len(self.eng.workspace['ScopeData'].get('signals').get('values')))
    # #             print(self.eng.workspace['ScopeData'].get('signals').get('values')) # [prev_len:]

    #             # print("j : ", j)
    #             # print("curr step : ", self.curr_step)

    #             self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','update',nargout=0) #if you have updated any simulation parameters
                
    #             if j >= self.curr_step : # * SAMPLE_TIME:                    
    #                 print("stopping.. : ", j, " : step : ", self.curr_step)
    #                 self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','stop',nargout=0)
                
    #             self.eng.set_param('test_v_control_and_i_control_with_droop_copy','SimulationCommand','continue',nargout=0)
                
    #             j+=1
        
    #     self.full_signal = self.eng.workspace['V_out_1'].get('signals').get('values')     

    #     if self.curr_step <= 0 : 
    #         # return some safe value and wait till the transient settles
    #         return 0   

    #     # generate inputs to NN 
    #     for i, agent in enumerate(self.agents):

    #         agent.vl = np.array(self.eng.workspace['V_out_' + str(i)].get('signals').get('values')[-1], dtype=float)[0]
    #         print("Vl : ", agent.vl)
    #         agent.il = np.array(self.eng.workspace['I_out_' + str(i)].get('signals').get('values')[-1], dtype=float)[0]

    #         print("Il : ", agent.il)

    #         # not needed
    #         # agent.vl = agent.vl + action_n[i,0] * self.delta_v_change
    #         # agent.il = agent.il + action_n[i,1] * self.delta_i_change

    #         agent.del_v = float(LINE_VOLTAGE_RATED) - agent.vl
    #         agent.del_i = float(LINE_CURRENT_RATED) - agent.il            

    #         if not (agent.vl  <= LINE_VOLTAGE_MAX_LIMIT) and not (agent.vl >=LINE_VOLTAGE_MIN_LIMIT):
    #             print("V failed:")
    #             agent.v_level_failed = True

    #         if not (agent.il  <= LINE_CURRENT_MAX_LIMIT) and not (agent.il >=LINE_CURRENT_MIN_LIMIT):
    #             print("I failed:")
    #             agent.i_level_failed = True
        

    #     self.prev_len = len(self.full_signal)