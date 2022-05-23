# core modules
import random
import math

# 3rd party modules
import gym
import numpy as np
from gym import spaces

import tensorflow as tf

from itertools import chain, combinations


# Global Vars - for all agents
MAX_BATTERY_LIMIT = 10
MIN_BATTERY_LIMIT = 2

MAIN_POWER_MAX_LIMIT = 50
MAIN_POWER_MIN_LIMIT = 5

l = [[[0,1],[16,1],[0,1],[6,1]],[[10,2],[0,2],[6,2],[0,2]],[[0,3],[0,3],[0,3],[10,3]],[[2,4],[12,4],[0,4],[0,4]],[[8,5],[0,5],[10,5],[16,5]],[[0,6],[20,6],[0,6],[0,6]],[[12,7],[0,7],[12,7],[6,7]],[[13,8],[0,8],[0,8],[1,8]],[[6,9],[12,9],[8,9],[0,9]],[[0,10],[0,10],[0,10],[14,10]],[[0,11],[12,11],[2,11],[0,11]],[[10,12],[0,12],[0,12],[6,12]]]
# l = list(l)

# solar_power = [0, 0, 2, 3, 6, 12, 12, 12, 6, 1, 0, 0]
# wind_power = [0, 0, 2, 3, 12, 12, 0, 0, 6, 10, 5, 0]

# --------------- 12 intervals ------------------------ 
# renewables = [0, 0, 4, 6, 18, 24, 12, 12, 12, 11, 5, 0]
# batterylevel = [5, 4, 3, 2, 3, 3, 4, 6, 8, 5, 5, 3]
# demand_power = [0, 0, 2, 3, 12, 12, 0, 0, 6, 10, 5, 0]
# -----------------------------------------------------

# -------------- 4 intervals ----------------
RENEWABLES = [0, 10, 6, 8, 12, 18, 24, 10, 2, 0, 0, 0]
BATTERY_LEVEL = [2, 3, 8, 6, 4, 2, 3, 5, 8, 6, 4, 3]
NON_ADL_DEMAND = [3, 4, 6, 8, 12, 10, 14, 18, 15, 13, 8, 4]
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
        print(self.ADL_list)
        self.pow_set =  list(chain.from_iterable(combinations(s, r) for r in range(len(s)+1)))
        return self.pow_set

    def concat_adl(self, old_adl, curr_adl):
        self.ADL_list = []
        i=0
        
        for x in old_adl:        
           
            if x[0] != 0 :
                self.ADL_list.append(old_adl[i])
            else:
                self.ADL_list.append(curr_adl[i])
            i=i+1
        print(self.ADL_list)
        return self.ADL_list

    def remove(self, row_num):
        self.allocated_load = self.pow_set[row_num]
        print(self.allocated_load)
        print("SD")
        temp3=[]
        temp4=[]
        for item in self.ADL_list:
            if item not in self.allocated_load:
                temp3.append(item)
            else:
                temp3.append((0,0))
        
        for item in self.ADL_list:
            if item not in self.allocated_load:
                temp4.append(item[0])
            else:
                temp4.append(0)
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
        print(temp3, temp4)
        return temp3,temp4

    def is_all(self):
        if self.new_ADL_list_for_nn == [] :
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

class MGEnv(gym.Env):
    

    def __init__(self):
        self.__version__ = "0.1.0"
        print("MGEnv - Version {}".format(self.__version__))

        # General variables defining the environment
        # self.E_PRICE = tf.distributions.Normal(loc = 8, scale =1) #------- dynamic pricing
        self.TOTAL_TIME_STEPS = 12 # 12 for normal
        self.time_is_over = False
        self.curr_step = -1
        self.is_energy_balance = False
        self.is_all_allocated = False

        self.ps = Powerset()

        # Define what the agent can do
        # Buy or Sell to mains, Buy or Sell to other MGs, Charge or Discharge Battery, ADL jobs
        self.action_space = spaces.Discrete(34)

        # Observation is the remaining time
        # low = np.array([0.0,  # remaining_tries
        #                 ])
        # high = np.array([self.TOTAL_TIME_STEPS,  # remaining_tries
        #                  ])

        # ToDo ---- Change for including a set of time intervals
        self.observation_space = spaces.Discrete(3)

        # Store what the agent tried
        self.curr_episode = -1
        self.action_episode_memory = []
        self.cost_fn = 0
        self.unit_price = 5
        self.failed_allocate= True
        self.ndt = RENEWABLES[0] + BATTERY_LEVEL[0] - NON_ADL_DEMAND[0]        # self.solar_power = 0

        self.amount_allocated = 0
        self.ADL_list = []
        self.new_ADL_list_for_nn = [0,0,0,0]
        self.new_ADL_list_for_concat =[[0,0],[0,0],[0,0],[0,0]]
        self.delay=0
        # self.demand_power = 0
        # self.batterylevel = 0
        # self.mains_power = 0

    def _step(self, action):
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
        if self.time_is_over :
            raise RuntimeError("Episode is done")
        self.curr_step += 1
        self._take_action(action)
        reward = self._get_reward()
        ob = self._get_state()
        return ob, reward, self.time_is_over, {} #self.is_all_allocated, self.is_energy_balance, done

    # -------------- to fix ------------------
    def _take_action(self, action):
        self.action_episode_memory[self.curr_episode].append(action)
        # need to add battery charging and discharging cost

        # self.cost = −self.unit_price∗(self.demand_power − (self.solar_power + self.wind_power + self.mains_power))**2 + (1 − self.unit_price) ∗ (self.mains_power)**2

        # chance_to_take = get_chance(self.cost)
        # energy_is_balanced = (random.random() < chance_to_take)
        
        # energy_is_balanced = 
        # all_is_allocated = 
        #ps = powerset()
        print(l[self.curr_step], self.new_ADL_list_for_concat)
        self.ADL_list = self.ps.concat_adl( l[self.curr_step],self.new_ADL_list_for_concat)
        self.ADL_list  = self.ps.power_set(self.ADL_list)
        self.new_ADL_list_for_concat, self.new_ADL_list_for_nn = self.ps.remove(action)
        self.is_all_allocated = self.ps.is_all()
        
        self.delay = self.ps.delay(self.curr_step)
        
        self.amount_allocated = self.ps.amount_allocated()
        self.ndt = RENEWABLES[self.curr_step] + BATTERY_LEVEL[self.curr_step] - NON_ADL_DEMAND[self.curr_step]
       
        remaining_steps = self.TOTAL_TIME_STEPS - self.curr_step-1
        self.time_is_over = (remaining_steps <= 0)
        self.failed_allocate = self.time_is_over and not self.is_all_allocated
        if self.failed_allocate:
            self.is_all_allocated = True  # abuse this a bit
            #self.cost = -10.0

    def _get_reward(self):
        """Reward is given for energy_balance and all_allocated."""
        if (((self.amount_allocated - self.ndt)) <= MAIN_POWER_MAX_LIMIT) and (((self.amount_allocated - self.ndt))>=MAIN_POWER_MIN_LIMIT):
            self.cost = 0.1*self.delay + self.unit_price * (self.amount_allocated - self.ndt)
        else:
            self.cost=101
        
        if not self.failed_allocate:
            # return self.price - 1
            return -self.cost + 100
        else:
            return -100.0

    def _reset(self):
        """
        Reset the state of the environment and returns an initial observation.
        Returns
        -------
        observation (object): the initial observation of the space.
        """
        self.curr_episode += 1
        self.action_episode_memory.append([])
        self.is_all_allocated = False
        self.is_energy_balance = False
        self.failed_allocate= True
        self.cost = 0.00
        self.time_is_over = False
        self.amount_allocated = 0
        self.ADL_list = []
        self.new_ADL_list_for_nn = [0,0,0,0]
        self.new_ADL_list_for_concat =[[0,0],[0,0],[0,0],[0,0]]
        self.curr_step = -1
        self.ndt = RENEWABLES[0] + BATTERY_LEVEL[0] - NON_ADL_DEMAND[0]

        return self._get_state()

    def _render(self, mode='human', close=False):
        return
    
    # -------------- to fix ------------------
    def _get_state(self):
        """Get the observation."""
        # ob = [self.TOTAL_TIME_STEPS - self.curr_step]  
        # self.solar_power = solar(self.curr_step)
        # self.wind_power = wind(self.curr_step)
        # self.batterylevel = batterylevel(self.solar_power,self.wind_power,self.demand_power)
        # self.demand_power = demand_power()      
        # self.mains_power = mains_power()
        # return self.demand_power,self.solar_power, self.wind_power, self.batterylevel, self.mains_power
        state = list()
        state.append(self.curr_step)
        state.append(self.ndt)
        
        for i in self.new_ADL_list_for_nn :
            state.append(i)
        print(state)
        return state    #self.curr_step, self.ndt, self.new_ADL_list_for_nn

    def _get_initial_state(self):
        #self._reset()
        self.curr_episode += 1
        self.action_episode_memory.append([])
        self.is_all_allocated = False
        self.is_energy_balance = False
        self.failed_allocate= True
        self.cost = 0.00
        self.time_is_over = False
        self.amount_allocated = 0
        self.ADL_list = []
        self.new_ADL_list_for_nn = [0,0,0,0]
        self.new_ADL_list_for_concat = [[0,0],[0,0],[0,0],[0,0]]
        self.curr_step = -1
        self.ndt = RENEWABLES[0] + BATTERY_LEVEL[0] - NON_ADL_DEMAND[0]

        return self._get_state()