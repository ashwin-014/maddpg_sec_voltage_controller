# core modules
import random
import math

# 3rd party modules
import gym
import numpy as np
from gym import spaces

import tensorflow as tf

from itertools import chain, combinations

import matplotlib.pyplot as plt

from collections import deque
# import adl_gen
# Global Vars - for all agents
# MAX_BATTERY_LIMIT = 10
# MIN_BATTERY_LIMIT = 2

MAIN_POWER_MAX_LIMIT = 50
MAIN_POWER_MIN_LIMIT = -50

# l = [[[0,1],[16,1],[0,1],[6,1]],[[10,2],[0,2],[6,2],[0,2]],[[0,3],[0,3],[0,3],[10,3]],[[2,4],[12,4],[0,4],[0,4]],[[8,5],[0,5],[10,5],[16,5]],[[0,6],[20,6],[0,6],[0,6]],[[12,7],[0,7],[12,7],[6,7]],[[13,8],[0,8],[0,8],[1,8]],[[6,9],[12,9],[8,9],[0,9]],[[0,10],[0,10],[0,10],[14,10]],[[0,11],[12,11],[2,11],[0,11]],[[10,12],[0,12],[0,12],[6,12]]]


# l = list(l)

# solar_power = [0, 0, 2, 3, 6, 12, 12, 12, 6, 1, 0, 0]
# wind_power = [0, 0, 2, 3, 12, 12, 0, 0, 6, 10, 5, 0]

# --------------- 12 intervals ------------------------ 
# renewables = [0, 0, 4, 6, 18, 24, 12, 12, 12, 11, 5, 0]
# batterylevel = [5, 4, 3, 2, 3, 3, 4, 6, 8, 5, 5, 3]
# demand_power = [0, 0, 2, 3, 12, 12, 0, 0, 6, 10, 5, 0]
# -----------------------------------------------------

# -------------- 4 intervals ----------------
# RENEWABLES = [0, 10, 6, 8, 12, 18, 24, 10, 2, 0, 0, 0]
# BATTERY_LEVEL = [2, 3, 8, 6, 4, 2, 3, 5, 8, 6, 4, 3]
# NON_ADL_DEMAND = [3, 4, 6, 8, 12, 10, 14, 18, 15, 13, 8, 4]
# ------------------------------------------
# mains_power = mains_power()


class Powerset:
    def __init__(self) :
        self.pow_set = []
        self.ADL_list = []
        self.new_ADL_list_for_concat = []
        self.new_ADL_list_for_nn = []
        self.allocated_load=[]

    def power_set(self, iterable):
        "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
        s = list(iterable)
        
        self.ADL_list = s
        
        # ---------------------------------------- removed print -------------------------------
        # print("ADL_List" ,self.ADL_list)
        # ------------------------------------------------------------------------

        self.pow_set =  list(chain.from_iterable(combinations(s, r) for r in range(len(s)+1)))
        return self.pow_set

# ------------------------------------------- work needed -------------------------------
# def concat_adl(self, old_adl, curr_adl):
#         self.ADL_list = []
#         i=0
        
#         for x in old_adl:        
           
#             if x[0] != 0 :
#                 self.ADL_list.append(np.asarray(old_adl[i]))
#             else:
#                 self.ADL_list.append(np.asarray(curr_adl[i]))
#             i=i+1
        
#         # ---------------------------------------- removed print -------------------------------
#         # print("concat",self.ADL_list)
#         # -----------------------------------------------------------------------

#         return self.ADL_list
# -----------------------------------------------------------------------------------------


    def concat_adl(self, old_adl, curr_adl):
        self.ADL_list = []

        # ---------------------------- old ----------------------
        i=0
        
        for x in old_adl:        
           
            if x[0] != 0 :
                self.ADL_list.append(np.asarray(old_adl[i]))
            else:
                self.ADL_list.append(np.asarray(curr_adl[i]))
            i=i+1
        # ----------------------------------------------------------

        # ---------------------------------------- removed print -------------------------------
        # print("concat",self.ADL_list)
        # -----------------------------------------------------------------------

        return self.ADL_list

    def remove(self, row_num):
        
        # ---------------------------------------- removed print -------------------------------
        # print(self.pow_set)
        # -------------------------------------------------------

        self.allocated_load = self.pow_set[row_num]

        # ---------------------------------------- removed print -------------------------------
        # print("alloc_load",self.allocated_load)
        # -------------------------------------------------------------------------

        # print("SD")
        temp3=[]
        temp4=[]
        if (self.allocated_load):
            for item in self.ADL_list:
                
                # ---------------------------------------- removed print -------------------------------
                # print(np.any(np.all(item == self.allocated_load, axis=1)))
                # ---------------------------------------------------------------------------------

                if not (np.any(np.all(item == self.allocated_load, axis=1))):
                    temp3.append(item)

                else:
                    temp3.append((0,0))
            
            for item in self.ADL_list:
                
                # ---------------------------------------- removed print -------------------------------
                # print(np.any(np.all(item == self.allocated_load, axis=1)))
                # ------------------------------------------------------------------------------------------

                if not (np.any(np.all(item == self.allocated_load, axis=1))):
                    temp4.append(item[0])
                else:
                    temp4.append(0)

        else:
            for item in self.ADL_list:
                temp3.append(item) 
            
            for item in self.ADL_list:
                temp4.append(item[0])
                
        # ss =[]
        # for k in self.allocated_load:
        #     ss.append(tuple(k))
        # ss = tuple(ss)
        # stuple = tuple(tuple(x) for x in self.allocated_load)
        # ADL_list_tuple = tuple(tuple(y) for y in self.ADL_list)
        # self.allocated_load = tuple(self.allocated_load)	
        # print(type(stuple))
        # print("stuple",stuple,"adl_lost",ADL_list_tuple)
        # s = set(stuple)
        # self.new_ADL_list_for_concat = [x for x in self.ADL_list if x not in s]

        # for x in ADL_list_tuple:        
        #     if x not in s :
        #         self.new_ADL_list_for_concat.append(x)
        #     else:
        #         self.new_ADL_list_for_concat.append((0,0))

        # for x in ADL_list_tuple:        
        #     if x not in s :
        #         self.new_ADL_list_for_nn.append(x[0])
        #     else:
        #         self.new_ADL_list_for_nn.append(0)

        # for i in self.allocated_load:
        #     for j in self.ADL_list:
        #         if i != j:
        #             self.new_ADL_list.append(j) 
        
        # ---------------------------------------- removed print -------------------------------
        # print(temp3, temp4)
        # -------------------------------------------------------------------

        return temp3,temp4

    def is_all(self):
        if not np.any(self.new_ADL_list_for_nn ) : #== [0,0,0,0] 
            return True
        else:
            return False

    def delay(self, curr_step):
        delay_period = []
        for t in range(len(self.allocated_load)):
            delay_period.append(curr_step - self.allocated_load[t][1])
        return sum(delay_period)

    def amount_allocated(self):
        sum = 0
        for k in range(len(self.allocated_load)):
            sum = sum + self.allocated_load[k][0]
        
        return sum


def get_probs(dist):
   
    # e = math.exp(1)
    # return (1.0 + e) / (1. + math.exp(x + 1))
    return dist.sample([1])

# def demand_power():
#     pass
# def solar(time):
#     d = tf.distributions.Normal(loc = 7, scale=1)
#     return d.prob(time)
# def wind(time):
#     d = tf.distributions.Normal(loc = 3, scale=1)
#     return d.prob(time)
# def mains_power(batterylevel, solar, wind, demand):
#     upp_limit = 500
#     low_limit = 0
#     extra = demand - (batterylevel+solar+wind)
#     if (extra>0):
#         return extra
#     else:
#         return low_limit
# def batterylevel(batterylevel, solar, wind, demand):
#     batterylevel = batterylevel − demand_power + solar + wind
#     return batterylevel

# ---------------------------------
class EntityState(object):
    def __init__(self):
        # state of charge
        self.p_soc = None
        # demand
        self.p_demand = None
        # supply
        self.p_supply = None
# state of agents (including communication and internal/mental state)

# class AgentState(EntityState):
#     def __init__(self):
#         super(AgentState, self).__init__()
#         # amount allocated now
#         self.current_allocation = [[0,0],[0,0],[0,0],[0,0]]
#         self.
#         # communication utterance
#         self.c = None
# action of the agent
class Action(object):
    def __init__(self):
        # physical action
        self.u = None
        # amount to be allocated
        self.amount_to_be_allocated = [[0,0],[0,0],[0,0],[0,0]]
        # communication action
        self.c = None
# properties and state of physical world entity
class Entity(object):
    def __init__(self):
        # name 
        self.name = ''
        # properties:
        # self.size = 0.050
        self.max_gen_capacity = None
        self.max_load_capacity = None
        self.max_storage = None
        self.min_storage = None
        self.current_load = None
        
        # entity can move / be pushed
        # self.movable = False
        # entity collides with others
        # self.collide = True
        # material density (affects mass)
        # self.density = 25.0
        # color
        # self.color = None
        # max speed and accel
        # self.max_speed = None
        # self.accel = None
        # state
        # self.state = EntityState()
        # mass
        # self.initial_mass = 1.0
    # @property
    # def mass(self):
        # return self.initial_mass

# ---------------------------------
# agent and world
class Agent(Entity):
    def __init__(self):
        super(Agent, self).__init__()
        # agents are movable by default
        # self.movable = True
        # cannot send communication signals
        self.silent = True
        # cannot observe the world
        # self.blind = False
        # physical motor noise amount
        self.u_noise = None
        # communication noise amount
        self.c_noise = None
        # control range
        self.u_range = 1.0
        # Powerset
        self.ps = Powerset()
        # action
        self.action = Action()
        # script behavior to execute
        # self.action_callback = None
        
        self.delay=0

        self.is_all_allocated = False
        self.is_energy_balance = False
        self.failed_allocate= True
        self.cost = 0.00
        self.amount_allocated = 0
        self.ADL_list = []
        self.new_ADL_list_for_nn = [0,0,0,0]
        self.new_ADL_list_for_concat = [[0,0],[0,0],[0,0],[0,0]]
        
        self.deq_adl = []
        self.deq_for_unalloc = []
        self.temp_adl = []
        self.temp_nadl = []
        self.temp_ren = []
        self.temp_bat = []
        self.ndt = 0
        # state
        self.state = list()
        self.state.append(0)
        self.state.append(self.ndt)
        self.state.append(0)
        self.state.append(0)
        self.state.append(0)
        self.state.append(0)

        # self.l = [[[0,1],[16,1],[0,1],[6,1]],[[10,2],[0,2],[6,2],[0,2]],[[0,3],[0,3],[0,3],[10,3]],[[2,4],[12,4],[0,4],[0,4]],[[8,5],[0,5],[10,5],[16,5]],[[0,6],[20,6],[0,6],[0,6]],[[12,7],[0,7],[12,7],[6,7]],[[13,8],[0,8],[0,8],[1,8]],[[6,9],[12,9],[8,9],[0,9]],[[0,10],[0,10],[0,10],[14,10]],[[0,11],[12,11],[2,11],[0,11]],[[10,12],[0,12],[0,12],[6,12]]]


# ------------------------------- test ------------------------------
# deq_adl_0 = deque(x_w_batch[:,0,:])
# deq_adl_1 = deque(x_w_batch[:,1,:])
# deq_adl_2 = deque(x_w_batch[:,2,:])
# deq_adl_3 = deque(x_w_batch[:,3,:])
# --------------------------------------------------------------------------------------------------------


    def adl_demand(self):
        x_w_batch = np.zeros(shape=(12,4,2))
        
        # ---------------------------------------- removed print -------------------------------
        # print(x_w_batch)
        # ----------------------------------------------------------------------------
        for i in range(4):
            mu_s = 9 + np.random.normal(0,1)
            std_s = 0.4 + np.random.normal(0,0)

            mu_r = 4 - np.random.normal(0,1)
            std_r = 0.5 + np.random.normal(0,0)

            s = np.random.normal(mu_s,std_s,1000)
            r = np.random.normal(mu_r,std_r,1000)
            a = np.concatenate((s,r))
            w,x,y = plt.hist(a,12,normed=True)
            # plt.show()

            new_arr = np.stack((w*50, np.arange(0,12)),axis=-1)
            new_arr = np.rint(new_arr)
            
            # ---------------------------------------- removed print -------------------------------
            # print("x_val",i)
            # -------------------------------------------------------------------

            x_w_batch[:,i,:] = new_arr
        
        # ---------------------------------------- removed print -------------------------------
        # print('x_w_batch',x_w_batch, 'x_w_batch_tra', np.reshape(x_w_batch, (12,4,2)))
        # --------------------------------------------------------------------------
        
        return x_w_batch

    def non_adl_demand(self):
        s = np.random.normal(9,2,1000)
        r = np.random.normal(4,4,1000)
        a = np.concatenate((s,r))
        w,x,y = plt.hist(a,12,normed=True)
        # plt.plot(w)
        # plt.show()
        
        w = np.rint(w*100)

        return w

    def renewable_gen(self):
        s = np.random.normal(6,3.5,1000)
        w,x,y = plt.hist(s,12,normed=True)              
        w = np.rint(w*100)

        return w

    def battery_gen(self):
        s = np.random.normal(11,2,1000)
        r = np.random.normal(3,4,1000)
        a = np.concatenate((s,r))
        w,x,y = plt.hist(a,12,normed=True)
        w = np.rint(w*50)

        return w

    def reset(self):
        """
        Reset the state of the environment and returns an initial observation.
        Returns
        -------
        observation (object): the initial observation of the space.
        """
        self.silent = True
        self.u_noise = None
        # self.ps = Powerset()

        self.is_all_allocated = False
        self.is_energy_balance = False
        self.failed_allocate= True
        self.cost = 0.00
        
        self.amount_allocated = 0
        self.ADL_list = []
        self.new_ADL_list_for_nn = [0,0,0,0]
        self.new_ADL_list_for_concat =[[0,0],[0,0],[0,0],[0,0]]

        self.deq_adl = []
        self.deq_for_unalloc = []

        self.temp_adl = []
        self.temp_nadl = []
        self.temp_ren = []
        self.temp_bat = []
        self.ndt = 0

        self.state = list()
        self.state.append(0)
        self.state.append(self.ndt)
        self.state.append(0)
        self.state.append(0)
        self.state.append(0)
        self.state.append(0)
        
        return self.state


# multi-agent world
class World(object):
    def __init__(self):
        # list of agents and entities (can change at execution-time!)
        self.agents = []
        # self.landmarks = []
        # communication channel dimensionality
        self.dim_c = 0
        self.dim_ADL = 4
        # position dimensionality
        # self.dim_p = 2
        # color dimensionality
        # self.dim_color = 3
        # simulation timestep
        self.dt = 1
        # physical damping
        # self.damping = 0.25
        # contact response parameters
        # self.contact_force = 1e+2
        # self.contact_margin = 1e-3
    # return all entities in the world
    # @property
    # def entities(self):
    #     return self.agents # + self.landmarks
    # return all agents controllable by external policies
    @property
    def policy_agents(self):
        return [agent for agent in self.agents]
    # return all agents controlled by world scripts
    # update state of the world
    def step(self):
        # set actions for scripted agents 
        # for agent in self.scripted_agents:
            # agent.action = agent.action_callback(agent, self)
        # gather forces applied to entities
        # p_force = [None] * len(self.entities)
        # apply agent physical controls
        # p_force = self.apply_action_force(p_force)
        # apply environment forces
        # p_force = self.apply_environment_force(p_force)
        # integrate physical state
        # self.integrate_state(p_force)
        # update agent state
        for agent in self.agents:
            self.update_agent_state(agent)
    
    def update_agent_state(self, agent):
        pass

    def reset_world(self):
        # random properties for agents
               
        # set random initial states
        for agent in self.agents:
            agent.reset()

class mk_world(object):
    def __init__(self):
        self.world = World()

    def make_world(self):
        
        # set any world properties first
        self.world.dim_c = 0
        num_agents = 4       
        # add agents
        self.world.agents = [Agent() for i in range(num_agents)]
        for i, agent in enumerate(self.world.agents):
            agent.name = 'agent %d' % i
            agent.reset()

        # make initial conditions
        self.reset_world(self.world)
        return self.world

    def reset_world(self,world):
        # random properties for agents
               
        # set random initial states
        for agent in world.agents:
            agent.reset()
    
        
        # set communication state (directly for now)
        # if agent.silent:
        #     # agent.state.c = np.zeros(self.dim_c)
        # else:
        #     noise = np.random.randn(*agent.action.c.shape) * agent.c_noise if agent.c_noise else 0.0
        #     agent.state.c = agent.action.c + noise 
# ---------------------------------

class MultiAgent(gym.Env):

    def __init__(self):
        self.__version__ = "0.1.0"
        print("MGEnv - Version {}".format(self.__version__))
        
        w = mk_world()
        self.world = w.make_world()
        self.agents = self.world.policy_agents
         # set required vectorized gym env property
        self.n = len(self.world.policy_agents)

        self.shared_reward = False
        self.time = 0

        # configure spaces
        self.action_space = []
        self.observation_space = []

        self.total_rew = 0
        
        # Define what the agent can do
        # Buy or Sell to mains, Buy or Sell to other MGs, Charge or Discharge Battery, ADL jobs
        # self.action_space = spaces.Discrete(34)

        # Observation is the remaining time
        # low = np.array([0.0,  # remaining_tries
        #                 ])
        # high = np.array([self.TOTAL_TIME_STEPS,  # remaining_tries
        #                  ])

        # ToDo ---- Change for including a set of time intervals
        # self.observation_space = spaces.Discrete(3)
        
        for agent in self.agents:
            total_action_space = []
            # physical action space
            u_action_space = spaces.Discrete(self.world.dim_ADL ** 2)
            total_action_space.append(u_action_space)
            # communication action space
            c_action_space = spaces.Discrete(self.world.dim_c)
            
            if not agent.silent:
                total_action_space.append(c_action_space)
            # Total action space 
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


            # ------------------------------------------
            # Is this Correct?
            self.observation_space.append(spaces.Discrete(self.world.dim_ADL+2) )
            # ------------------------------------------
            agent.action.c = np.zeros(self.world.dim_c)


        # General variables defining the environment
        # self.E_PRICE = tf.distributions.Normal(loc = 8, scale =1) #------- dynamic pricing
        self.TOTAL_TIME_STEPS = 12 # 12 for normal
        self.time_is_over = False
        self.curr_step = 0
        self.unit_price = 5

        

        # Store what the agent tried
        self.curr_episode = -1
        # self.action_episode_memory = []
        
        # ------------------------------------------
        # for agent in self.agents:
            
        #     self.agent.cost = 0
        #     self.agent.is_energy_balance = False
        #     self.agent.is_all_allocated = False
        #     self.agent.failed_allocate= True
        #     self.agent.ndt = RENEWABLES[0] + BATTERY_LEVEL[0] - NON_ADL_DEMAND[0]        # self.solar_power = 0

        #     self.agent.ps = Powerset()

        #     self.agent.amount_allocated = 0
        #     self.agent.ADL_list = []
        #     self.agent.new_ADL_list_for_nn = [0,0,0,0]
        #     self.agent.new_ADL_list_for_concat =[[0,0],[0,0],[0,0],[0,0]]
        #     self.agent.delay=0
        # ------------------------------------------

        # self.demand_power = 0
        # self.batterylevel = 0
        # self.mains_power = 0

    def _step(self, action_n):
        """
        The agent takes a step in the environment.
        Parameters
        ----------
        action : int
        Returns
        -------
        ob, reward, episode_over, info : tuple
            ob (object) :
                an environment-specific object representing your observation of
                the environment.
            reward (float) :
                amount of reward achieved by the previous action. The scale
                varies between environments, but the goal is always to increase
                your total reward.
            episode_over (bool) :
                whether it's time to reset the environment again. Most (but not
                all) tasks are divided up into well-defined episodes, and done
                being True indicates the episode has terminated. (For example,
                perhaps the pole tipped too far, or you lost your last life.)
            info (dict) :
                 diagnostic information useful for debugging. It can sometimes
                 be useful for learning (for example, it might contain the raw
                 probabilities behind the environment's last state change).
                 However, official evaluations of your agent are not allowed to
                 use this for learning.
        """

        obs_n = []
        reward_n = []
        done_n = []
        info_n = {'n': []}
        self.agents = self.world.policy_agents
        
        # set day ahead schedule for all agents
        if self.curr_step == 0:
            for agent in self.agents:
                agent.temp_adl = agent.adl_demand()
                agent.temp_nadl = agent.non_adl_demand()
                agent.temp_bat = agent.battery_gen()
                agent.temp_ren = agent.renewable_gen()
                agent.ndt = agent.temp_ren[0] + agent.temp_bat[0] - agent.temp_nadl[0]


        # set action for each agent
        for i, agent in enumerate(self.agents):
            self._set_action(action_n[i], agent, self.action_space[i])
        # advance world state
        # self.world.step()
        # record observation for each agent
        for agent in self.agents:
            obs_n.append(self._get_obs(agent))
            reward_n.append(self._get_reward(agent))
            done_n.append(self._get_done(agent))
            info_n['n'].append(self._get_info(agent))

        if self.time_is_over :
            raise RuntimeError("Episode is done")
        self.curr_step += 1
        # self._set_action(action)
        # reward = self._get_reward()
        # ob = self._get_state()
        return obs_n, reward_n, done_n, info_n #self.is_all_allocated, self.is_energy_balance, done

    # -------------- to fix ------------------
    def _get_info(self, agent):
        return {}
    def _get_done(self, agent):
        remaining_steps = self.TOTAL_TIME_STEPS - self.curr_step
        self.time_is_over = (remaining_steps <= 0)
        return self.time_is_over

    def _set_action(self, action, agent, action_space):
        # agent.action_episode_memory[self.curr_episode].append(action)
        # need to add battery charging and discharging cost

        # self.cost = −self.unit_price∗(self.demand_power − (self.solar_power + self.wind_power + self.mains_power))**2 + (1 − self.unit_price) ∗ (self.mains_power)**2

        # chance_to_take = get_chance(self.cost)
        # energy_is_balanced = (random.random() < chance_to_take)
        
        # energy_is_balanced = 
        # all_is_allocated = 
        #ps = powerset()

        # --------------------------- removed print ------------------------------------
        # print("temp_adl_for_curr_step", agent.temp_adl[self.curr_step], "temp_concat_for_curr_step", agent.new_ADL_list_for_concat)
        # -------------------------------------------------------------------

        agent.ADL_list = agent.ps.concat_adl(agent.temp_adl[self.curr_step],agent.new_ADL_list_for_concat)
        agent.ADL_list  = agent.ps.power_set(agent.ADL_list)

        # --------------------------- removed print ------------------------------------
        # print("action", action, "argmax_action",np.argmax(action))
        # -------------------------------------------------------------------

        agent.new_ADL_list_for_concat, agent.new_ADL_list_for_nn = agent.ps.remove(np.argmax(action))
        agent.is_all_allocated = agent.ps.is_all()
        
        agent.delay = agent.ps.delay(self.curr_step)
        
        agent.amount_allocated = agent.ps.amount_allocated()
        agent.ndt = agent.temp_ren[self.curr_step] + agent.temp_bat[self.curr_step] - agent.temp_nadl[self.curr_step]
       
        remaining_steps = self.TOTAL_TIME_STEPS - self.curr_step
        self.time_is_over = (remaining_steps <= 0)
        agent.failed_allocate = self.time_is_over and not agent.is_all_allocated
        if agent.failed_allocate:
            agent.is_all_allocated = True  # abuse this a bit
            #self.cost = -10.0

    def _get_reward(self,agent):
        """Reward is given for energy_balance and all_allocated."""
        # for agent in agents:

        if (((agent.amount_allocated - agent.ndt)) <= MAIN_POWER_MAX_LIMIT) and (((agent.amount_allocated - agent.ndt))>=MAIN_POWER_MIN_LIMIT):
            agent.cost = 0.1*agent.delay + self.unit_price * (agent.amount_allocated - agent.ndt)
        else:
            agent.cost=101
    
        if not agent.failed_allocate:
            # return self.price - 1
            self.total_rew = (-agent.cost)
        else:
            self.total_rew = -500.0
        
        return self.total_rew

    def _reset(self):
        """
        Reset the state of the environment and returns an initial observation.
        Returns
        -------
        observation (object): the initial observation of the space.
        """
        self.curr_episode += 1        
        self.time_is_over = False
        self.total_rew = 0

        self.curr_step = 0
        for agent in self.agents :
            agent.reset()
        # return self._get_state()

    def _render(self, mode='human', close=False):
        return
    
    # -------------- to fix ------------------
    def _get_obs(self, agent):
        """Get the observation."""
        # ob = [self.TOTAL_TIME_STEPS - self.curr_step]  
        # self.solar_power = solar(self.curr_step)
        # self.wind_power = wind(self.curr_step)
        # self.batterylevel = batterylevel(self.solar_power,self.wind_power,self.demand_power)
        # self.demand_power = demand_power()      
        # self.mains_power = mains_power()
        # return self.demand_power,self.solar_power, self.wind_power, self.batterylevel, self.mains_power
        agent.state = list()
        agent.state.append(self.curr_step)
        agent.state.append(agent.ndt)
        
        for i in agent.new_ADL_list_for_nn :
            agent.state.append(i)
        
        # ---------------------------------------- removed print -------------------------------
        # print(agent.state)
        # ---------------------------------------------------------

        # return state    #self.curr_step, self.ndt, self.new_ADL_list_for_nn
        return agent.state

    def _get_initial_state(self):
        #self._reset()
        self.agents = self.world.policy_agents

        self.curr_episode += 1
        
        self.time_is_over = False
        self.total_rew = 0
        self.curr_step = 0

        initial_state_batch = []
        for i,agent in enumerate(self.agents):
            initial_state_batch.append(agent.reset()) 

        return initial_state_batch
        # return obs_n

        # return self._get_obs()