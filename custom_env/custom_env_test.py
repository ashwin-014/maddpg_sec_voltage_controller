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
from math import ceil
# import adl_gen
# Global Vars - for all agents
# MAX_BATTERY_LIMIT = 10
# MIN_BATTERY_LIMIT = 2

MAIN_POWER_MAX_LIMIT = 3
MAIN_POWER_MIN_LIMIT = -3

# l = [[[0,1],[16,1],[0,1],[6,1]],[[10,2],[0,2],[6,2],[0,2]],[[0,3],[0,3],[0,3],[10,3]],[[2,4],[12,4],[0,4],[0,4]],[[8,5],0,5],[10,5],[16,5]],[[0,6],[20,6],[0,6],[0,6]],[[12,7],[0,7],[12,7],[6,7]],[[13,8],[0,8],[0,8],[1,8]],[[6,9],[12,9],[8,9],[0,9]],[[0,10],[0,10],[0,10],[14,10]],[[0,11],[12,11],[2,11],[0,11]],[[10,12],[0,12],[0,12],[6,12]]]


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
        # self.u = None
        # amount to be allocated
        # self.amount_to_be_allocated = [[0,0],[0,0],[0,0],[0,0]]
        # communication action
        self.c = None
# properties and state of physical world entity
class Entity(object):
    def __init__(self):
        # name 
        self.name = ''
        # properties:
        # self.size = 0.050
        
    # ------------------------------- remove comment ------------------
        # self.max_gen_capacity = None
        # self.max_load_capacity = None
        # self.max_storage = None
        # self.min_storage = None
        # self.current_load = None
    # ------------------------------- remove comment ------------------

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
        # self.u_noise = None
        # communication noise amount
        # self.c_noise = None
        # control range
        # self.u_range = 1.0
        # Powerset
        self.ps = Powerset()
        # action
        self.action = Action()
        # script behavior to execute
        # self.action_callback = None
        
        self.delay=0
        self.time_step_not_fully_allocated = 0

        self.is_all_allocated = False
        self.is_energy_balance = False
        self.failed_allocate= True

        self.cost = 0.00
        self.rew = 0
        self.amount_allocated = 0
        self.allocated_load=[]

        self.ADL_list = []
        self.pow_set = []
        self.pow_set_for_nn = []

        self.new_ADL_list_for_nn = []
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

#         mu_s = 9 + np.random.normal(0,1)
#         std_s = 0.4 + np.random.normal(0,0)

#         mu_r = 4 - np.random.normal(0,1)
#         std_r = 0.5 + np.random.normal(0,0)

# # -------------------- ADL gen --------------------------------
#         s = np.random.normal(mu_s,std_s,1000)
#         r = np.random.normal(mu_r,std_r,1000)
#         a = np.concatenate((s,r))
        # self.w_init,x,y = plt.hist(a,12,normed=True)

        # self.w_init = np.array([ 0.00667176,  0.11875733,  0.37361857,  0.15945507,  0.00867329,  0., 0., 0.,  0.00400306,  0.14010697,  0.43299724,  0.09006876])
        # self.w_init = self.w_init*75
              

# -------------------- Non ADL gen --------------------------------
        # s = np.random.normal(9,2,1000)
        # r = np.random.normal(4,4,1000)
        # a = np.concatenate((s,r))
        # w,x,y = plt.hist(a,12,normed=True)
        # w = np.array([ 0.00149354,  0.00273815,  0.01194831,  0.02041169,  0.03659169, 0.04381046,  0.06247969,  0.09334615,  0.13018676 , 0.0734323,   0.01842031,0.00298708])
        # self.w_non_adl = w*100

# -------------------- Ren gen --------------------------------
        # s = np.random.normal(6,3.5,1000)
        # w,x,y = plt.hist(s,12,normed=True) 
        # w = np.array([ 0.00537982,  0.0145255,   0.03765872,  0.06778569,  0.10383046,  0.12104587,  0.09468477,  0.0527222,   0.02689908,  0.00914569,  0.00322789,  0.00107596])
        # self.w_ren = w*100

        w = np.array([ 0.00537982,  0.0145255,   0.03765872,  0.2778569,  0.30383046,  0.9668477,  0.9668477,  0.9668477,   0.95689908,  0.40914569,  0.10322789,  0.00107596])
        self.w_ren = w*10
# -------------------- Battery gen --------------------------------
        # s = np.random.normal(11,2,1000)
        # r = np.random.normal(3,4,1000)
        # a = np.concatenate((s,r))
        # w,x,y = plt.hist(a,12,normed=True)
        # w = np.array([ 0.00157395,  0.004497,    0.01596436,  0.02743172,  0.04474518,  0.04699368,  0.04429548,  0.05014158,  0.09038976,  0.0865673,   0.03170387,  0.0053964 ])
        # self.w_bat = w*50

        w = np.array([ 0.00157395,  0.004497,    0.01596436,  0.02743172,  0.04474518,  0.04699368,  0.04429548,  0.05014158,  0.09038976,  0.0865673,   0.03170387,  0.0053964 ])
        self.w_bat = w*50

        # self.l = [[[0,1],[16,1],[0,1],[6,1]],[[10,2],[0,2],[6,2],[0,2]],[[0,3],[0,3],[0,3],[10,3]],[[2,4],[12,4],[0,4],[0,4]],[[8,5],[0,5],[10,5],[16,5]],[[0,6],[20,6],[0,6],[0,6]],[[12,7],[0,7],[12,7],[6,7]],[[13,8],[0,8],[0,8],[1,8]],[[6,9],[12,9],[8,9],[0,9]],[[0,10],[0,10],[0,10],[14,10]],[[0,11],[12,11],[2,11],[0,11]],[[10,12],[0,12],[0,12],[6,12]]]


# ------------------------------- test ------------------------------
# deq_adl_0 = deque(x_w_batch[:,0,:])
# deq_adl_1 = deque(x_w_batch[:,1,:])
# deq_adl_2 = deque(x_w_batch[:,2,:])
# deq_adl_3 = deque(x_w_batch[:,3,:])
# --------------------------------------------------------------------------------------------------------

    def get12vals(self,sequence, num):
        length = float(len(sequence))
        for i in range(num):
            yield sequence[int(ceil(i * length / num))]

    def adl_demand(self):
        x_w_batch = np.zeros(shape=(12,4,2))
        # probs = np.random.random(12)
        # wx=self.w_init*(probs-0.5) + self.w_init
        # wx = np.rint(wx)
        
        # ---------------------------------------- removed print -------------------------------
        # print(x_w_batch)
        # ----------------------------------------------------------------------------
        self.deq_adl = []
        self.deq_for_unalloc = []
        for i in range(4):
            # --------- OLD ------------------------
            
            # plt.show()
            # probs = np.random.random(12)
            # wx=self.w_init*(probs-0.5) + self.w_init
            # wx = np.rint(wx)
            # wx = wx/np.sum(wx)

            # new_arr = np.stack((wx, np.arange(0,12)),axis=-1)
            # # new_arr = np.rint(new_arr)
            
            # # ---------------------------------------- removed print -------------------------------
            # # print("x_val",i)
            # # -------------------------------------------------------------------

            # x_w_batch[:,i,:] = new_arr
            # self.deq_adl.append(deque(x_w_batch[:,i,:])) 
            # self.deq_for_unalloc.append(deque())
            # # print("\nadl:", new_arr)
            
            # --------- OLD ------------------------
            
            s = np.random.normal(8,4,100)
            r = np.random.normal(10,4,100)
            a = np.concatenate((s,r))

            # w_gen = self.get12vals(a,12) 
            w_init = np.empty(12)
            for j, el in enumerate(self.get12vals(a,12)): w_init[j] = el
            # w_init = [j for j in w_gen]
            w_init= w_init.clip(min=0)
            #---------------------------------------- removed print -------------------------------
            # print(w_init)
            #---------------------------------------- removed print -------------------------------
            w_init = (w_init/np.sum(w_init))- np.finfo(np.float32).epsneg
            mul = np.random.multinomial(12, w_init, size=1)
            mul = mul > 0
            mul = (1*mul).flatten()
            mul = np.stack((mul, np.arange(0,12)),axis=-1)
            #---------------------------------------- removed print -------------------------------
            # print(mul, mul.shape, x_w_batch.shape)
            #---------------------------------------- removed print -------------------------------
            x_w_batch[:,i,:] = mul
            self.deq_adl.append(deque(x_w_batch[:,i,:])) 
            self.deq_for_unalloc.append(deque())
            
            
        
        # ---------------------------------------- removed print -------------------------------
        # print('x_w_batch',x_w_batch, 'x_w_batch_tra', np.reshape(x_w_batch, (12,4,2)))
        # --------------------------------------------------------------------------
        # self.deq_adl = []
        # for x in range(4):
        #     self.deq_adl.append(deque(x_w_batch[:,x,:])) 
        
        # --------------- print removed ----------------
        # print("deq_adl",self.deq_adl)
        # --------------- print removed ----------------

        # self.deq_for_unalloc = []
        # for x in range(4):
        #     self.deq_for_unalloc.append(deque())
        return x_w_batch

    def non_adl_demand(self):

        # --------- OLD ------------------------

        # probs = np.random.random(12)
        # wx=self.w_non_adl*(probs-0.4) + self.w_non_adl
        # wx = np.rint(wx)
        # wx = wx/np.sum(wx)
        # --------- OLD ------------------------
        # # print("\nnon_adl:", wx)

        # # s = np.random.normal(9,2,1000)
        # # r = np.random.normal(4,4,1000)
        # # a = np.concatenate((s,r))
        # # w,x,y = plt.hist(a,12,normed=True)

        # # plt.plot(w)
        # # plt.show()
        
        # # w = np.rint(w*100)
        s = np.random.normal(9,2,1000)
        r = np.random.normal(10,4,1000)
        a = np.concatenate((s,r))
        w_init = np.empty(12)
        for j, el in enumerate(self.get12vals(a,12)): w_init[j] = el
        # w_init = [j for j in w_gen]
        w_init= w_init.clip(min=0)
        #---------------------------------------- removed print -------------------------------
        # print(w_init)
        #---------------------------------------- removed print -------------------------------
        w_init = (w_init/np.sum(w_init)) - np.finfo(np.float32).epsneg
        mul = np.random.multinomial(12, w_init, size=1)
        mul = mul > 0
        mul = (1*mul).flatten()
        
        return mul

    def renewable_gen(self):
        # ------- old -----------------
        # probs = np.random.random(12)
        # wx=self.w_ren*(probs-0.2) + self.w_ren
        # wx = np.rint(wx)
        # wx = wx/np.sum(wx)
        # ------- old -----------------
        # print("\nren:", wx)
        
        # s = np.random.normal(6,3.5,1000)
        # w,x,y = plt.hist(s,12,normed=True)              
        # w = np.rint(w*100)

        probs = np.random.random(12)
        wx=np.rint(self.w_ren*(probs-0.2) + self.w_ren)
        wx/=max(wx)

        return wx

    def battery_gen(self):
        # s = np.random.normal(11,2,1000)
        # r = np.random.normal(3,4,1000)
        # a = np.concatenate((s,r))
        # w,x,y = plt.hist(a,12,normed=True)
        # w = np.rint(w*50)
        # ------- old -----------------
        # probs = np.random.random(12)
        # wx=self.w_ren*(probs-0.5) + self.w_ren
        # wx = np.rint(wx)
        # wx = wx/np.sum(wx)
        # ------- old -----------------
        # print("\nbat:", wx)

        probs = np.random.random(12)
        wx=self.w_bat*(probs-0.5) + self.w_bat
        wx = np.rint(wx)
        wx/=max(wx)

        return wx

    # def concat_adl(self,curr_step):
    #     self.ADL_list = []

    #     time=11
    #     num=t=i=0
    #     adl_list_new=[]
    #     for num in range(4):
    #         unalloc_in = False
    #         if (self.deq_for_unalloc[num]):
    #             adl_list_new.append(self.deq_for_unalloc[num][0]) 
    #             print("\ninside unalloc : ", self.deq_for_unalloc[num][0],"\n")
    #             self.deq_for_unalloc[num].popleft()
    #             print("inside unalloc")
    #             unalloc_in = True

    #         else:        
    #             # code here
    #             inside = False
    #             for t in range(time-curr_step):
    #                 print("out",t,"deq",self.deq_adl[num][t][0])
    #                 if(self.deq_adl[num][t][0]) :
    #                     print("\ninside : ",self.deq_adl[num][t],"\n")
    #                     adl_list_new.append(self.deq_adl[num][t])
    #                     del self.deq_adl[num][t]
    #                     # deq_adl[num].popleft()
    #                     inside = True
    #                     break

    #             if inside==False:
    #                 adl_list_new.append(np.array([0.,curr_step]))
    #         if unalloc_in:
    #             if(np.all(self.deq_adl[num][0][0])) :
    #                 print("inside appending for unalloc existing")
    #                 print("\n", self.deq_adl[num][0], "\n")
    #                 self.deq_for_unalloc[num].append(self.deq_adl[num][0])
    #                 del self.deq_adl[num][0]
                    
    #             else:
    #                 print("inside appending fofr unalloc zero", self.deq_adl[num][0])
    #                 del self.deq_adl[num][0]

    #     print(adl_list_new)
    #     self.ADL_list = adl_list_new
    #     # ---------------------------------------- removed print -------------------------------
    #     # print("concat",self.ADL_list)
    #     # -----------------------------------------------------------------------

    #     return self.ADL_list

    def remove(self, row_num,curr_step):
        
        self.allocated_load = np.array(self.pow_set[row_num])
        
        # --------------- print removed ----------------
        # print("\nadl_list=", self.ADL_list, "allocated load=", self.allocated_load, "\nlen", self.allocated_load.shape[0], "\ntime = ", curr_step)
        # --------------- print removed ----------------

        temp3=[]
        temp4=[]
        time=11
        # self.time_step_not_fully_allocated =0
        if (self.allocated_load.size != 0):
            for num in range(4):
                if not (np.any(np.all(self.ADL_list[num] == self.allocated_load, axis=1))):       
                    temp3.append(self.ADL_list[num])
                    temp4.append(self.ADL_list[num][0])  
                    
                    self.time_step_not_fully_allocated +=1                                  
                    # --------------- print removed ----------------
                    # print("\nnot fully allocated :", self.time_step_not_fully_allocated)   
                    # --------------- print removed ----------------

                    if self.deq_for_unalloc[num]:
                        
                        if ( not (np.any(np.all(self.ADL_list[num] == list(self.deq_for_unalloc[num]), axis=1)))): #not (self.ADL_list[num][0] != 0) and
                            self.deq_for_unalloc[num].append(self.ADL_list[num])           
                    else:
                        if (self.ADL_list[num][0] != 0) :
                            self.deq_for_unalloc[num].append(self.ADL_list[num])     

                    if curr_step != 11:                    
                        if(self.deq_adl[num][0][0]) :
                            # --------------- print removed ----------------
                            # print("INDIVIDUAL UNALLOC !! inside appending for existing")
                            # print("\n", self.deq_adl[num][0], "\n")
                            # --------------- print removed ----------------
                            self.deq_for_unalloc[num].append(self.deq_adl[num][0])
                            del self.deq_adl[num][0]              
                        else:
                            # --------------- print removed ----------------
                            # print("INDIVIDUAL UNALLOC !! inside appending for zero", self.deq_adl[num][0])
                            # --------------- print removed ----------------
                            del self.deq_adl[num][0] 

                else:   
                    unalloc_in = False
                    if (self.deq_for_unalloc[num]):
                        # adl_list_new.append(self.deq_for_unalloc[num][0]) 
                        temp3.append(self.deq_for_unalloc[num][0])
                        temp4.append(self.deq_for_unalloc[num][0][0])
                        # print("\ninside unalloc : ", self.deq_for_unalloc[num][0],"\n")
                        self.deq_for_unalloc[num].popleft()
                        # print("inside unalloc")
                        unalloc_in = True

                    else:   
                    # self.time_step_not_fully_allocated -=1
                        inside = False
                        if curr_step!=11 :
                            for t in range(0,(time-(curr_step))):
                                # --------------- print removed ----------------
                                # print("remove_out",t,"remove_deq",self.deq_adl[num][t][0])
                                # --------------- print removed ----------------

                                if(self.deq_adl[num][t][0]) :
                                    # --------------- print removed ----------------
                                    # print("\ninside_remove : ",self.deq_adl[num][t],"\n")
                                    # --------------- print removed ----------------

                                    temp3.append(self.deq_adl[num][t])
                                    temp4.append(self.deq_adl[num][t][0])
                                    del self.deq_adl[num][t]     
                                    inside = True
                                    break
                        if inside==False:
                            temp3.append(np.array([0.,curr_step+1]))
                            temp4.append(np.array([0.]))
                    if unalloc_in:
                        if curr_step != 11:
                            if(self.deq_adl[num][0][0]) :
                                
                                # --------------- print removed ----------------
                                # print("inside appending for unalloc existing")
                                # print("\n", self.deq_adl[num][0], "\n")
                                # --------------- print removed ----------------

                                self.deq_for_unalloc[num].append(self.deq_adl[num][0])
                                del self.deq_adl[num][0]              
                            else:
                                
                                # --------------- print removed ----------------
                                # print("inside appending fofr unalloc zero", self.deq_adl[num][0])
                                # --------------- print removed ----------------

                                del self.deq_adl[num][0]          
                        # del self.deq_adl[num][0]                 
                    
        else:
            self.time_step_not_fully_allocated += 4
            # --------------- print removed ----------------
            # print("None allocated !! ")
            # --------------- print removed ----------------

            for num in range(4):              
                temp3.append(self.ADL_list[num])
                temp4.append(self.ADL_list[num][0])

                # ----------------------------------------------

                if self.deq_for_unalloc[num]:
                        
                    if ((self.ADL_list[num][0] != 0) and not (np.any(np.all(self.ADL_list[num] == list(self.deq_for_unalloc[num]), axis=1)))): #not (self.ADL_list[num][0] != 0) and
                        self.deq_for_unalloc[num].append(self.ADL_list[num])           
                    # else:
                    #     if (self.ADL_list[num][0] != 0) :
                    #         self.deq_for_unalloc[num].append(self.ADL_list[num])
                    
                    # ----------------------------------------------
                # if self.ADL_list[num][0] != 0 :
                #     self.deq_for_unalloc[num].append(self.ADL_list[num])

                if curr_step != 11:                    
                    if(self.deq_adl[num][0][0]) :
                        
                        # --------------- print removed ----------------
                        # print("NONE UNALLOC !! inside appending for unalloc existing")
                        # print("\n", self.deq_adl[num][0], "\n")
                        # --------------- print removed ----------------

                        self.deq_for_unalloc[num].append(self.deq_adl[num][0])
                        del self.deq_adl[num][0]              
                    else:
                        # --------------- print removed ----------------
                        # print("NONE UNALLOC !! inside appending fofr unalloc zero", self.deq_adl[num][0])
                        # --------------- print removed ----------------

                        del self.deq_adl[num][0] 
                # --------- to do : check for zero here ----------------
                # del self.deq_adl[num][0]
                
                

        # print("\nadl_list", self.ADL_list, "allocated load", self.allocated_load, "\n")
        return temp3,temp4

    def is_all(self):
        is_all_var = True
        for num in range(4):
            if self.deq_for_unalloc[num]:
                
                # --------------- print removed ----------------
                # print("\nis_all is False\n")
                # --------------- print removed ----------------

                is_all_var = False
                return False
        if is_all_var:    
            return True
        # if not np.any(self.deq_for_unalloc ) : #== [0,0,0,0] 
        #     return True
        # else:
        #     return False

    def delay_time(self, curr_step):
        delay_period = []
        for t in range(len(self.allocated_load)):
            delay_period.append(abs(curr_step - self.allocated_load[t][1]))
        # --------------- print removed ----------------
        # print("\ndelay period", delay_period)
        # --------------- print removed ----------------

        return sum(delay_period)

    def amount_allocated_fn(self):
        sum = 0
        for k in range(len(self.allocated_load)):
            sum = sum + self.allocated_load[k][0]        
        return sum


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
        self.rew = 0
        
        self.delay =0
        self.time_step_not_fully_allocated = 0
        
        self.amount_allocated = 0
        self.allocated_load = []

        self.ADL_list = []
        self.pow_set = []
        self.pow_set_for_nn = []
        self.new_ADL_list_for_nn = []
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
        self.discrete_action_space = False

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
            if self.discrete_action_space:                
                u_action_space = spaces.Discrete(self.world.dim_ADL ** 2)
                c_action_space = spaces.Discrete(self.world.dim_c)
            else:
                u_action_space = spaces.Box(low=MAIN_POWER_MIN_LIMIT, high=MAIN_POWER_MAX_LIMIT, shape=(2,)) # ,dtype=np.float32
                c_action_space = spaces.Box(low=0.0, high=1.0, shape=(self.world.dim_c,)) # ,dtype=np.float32
            total_action_space.append(u_action_space)
            # communication action space
            
            
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
            obs_dim = 3
            self.observation_space.append(spaces.Box(low=-np.inf, high=+np.inf, shape=(obs_dim,))) # ,dtype=np.float32
            # ------------------------------------------
            agent.action.c = np.zeros(self.world.dim_c)


        # General variables defining the environment
        # self.E_PRICE = tf.distributions.Normal(loc = 8, scale =1) #------- dynamic pricing
        self.TOTAL_TIME_STEPS = 12 # 12 for normal
        self.time_is_over = False
        self.curr_step = 0
        # self.unit_price = 5
        # ------------ price ----
        s = np.random.normal(9,2,1000)
        r = np.random.normal(10,4,1000)
        a = np.concatenate((s,r))
        w_gen = self.get12vals(a,12) 
        w_init = [j for j in w_gen]
        w_init = (w_init/np.sum(w_init) - np.finfo(np.float32).eps)
        mul = np.random.multinomial(12, w_init, size=1)
        self.unit_price = mul.flatten()+1

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
    def get12vals(self,sequence, num):
        length = float(len(sequence))
        for i in range(num):
            yield sequence[int(ceil(i * length / num))]
    def step(self, action_n):
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
 
        # set action for each agent
        for i, agent in enumerate(self.agents):
            self._set_action(action_n[i], agent, self.action_space[i])
        # advance world state
        # self.world.step()
        # record observation for each agent
        for k,agent in enumerate(self.agents):
            obs_n.append(self._get_obs(agent))
            reward_n.append(self._get_reward(agent, action_n[k]))
            done_n.append(self._get_done(agent))
            info_n['n'].append(self._get_info(agent))

        if self.time_is_over :
            # raise RuntimeError("Episode is done")
            print("Episode is done", self.curr_episode)
        else:
            self.curr_step += 1
       
        return obs_n, reward_n, done_n, info_n #self.is_all_allocated, self.is_energy_balance, done

    # -------------- to fix ------------------
    def find_sum(self, pow_set, action_load_alloc):
        diff = np.zeros(shape= len(pow_set))
        if pow_set[0] is None :
            pow_set[0] = 0

        # --------------------------- removed print ------------------------------------
        # print("\npow_set", pow_set)
        # --------------------------- removed print ------------------------------------

        for i in range(len(pow_set)):
            diff[i] = np.abs(np.sum(pow_set[i]) - np.abs(4*action_load_alloc[0]))

            # --------------------------- removed print ------------------------------------
            # print("\ni:",i,"\nsum:",np.sum(pow_set[i+1]),"alloc:",4*action_load_alloc[0]) #"shape:", pow_set[i+1].shape,
            # --------------------------- removed print ------------------------------------

        print("alloc_row_num",np.argmin(diff), "\nalloc:", pow_set[np.argmin(diff)])
        return np.argmin(diff)
    def _get_info(self, agent):
        return {}
    def _get_done(self, agent):
        remaining_steps = self.TOTAL_TIME_STEPS - self.curr_step-1
        self.time_is_over = (remaining_steps <= 0)
        
        return self.time_is_over
        # return 0

    def _set_action(self, action, agent, action_space):
      
        # need to add battery charging and discharging cost

        # --------------------------- removed print ------------------------------------
        # print("temp_adl_for_curr_step", agent.temp_adl[self.curr_step], "temp_concat_for_curr_step", agent.new_ADL_list_for_concat)
        # -------------------------------------------------------------------
        # agent.pow_set  = agent.ps.power_set(agent.ADL_list)

        if self.curr_step==0 :
            for num in range(4):
                for t in range(11-self.curr_step):
                    
                    # --------------- print removed ----------------
                    # print("init_",t,"init_deq",agent.deq_adl[num][t][0])
                    # --------------- print removed ----------------

                    if(agent.deq_adl[num][t][0]) :

                        # --------------- print removed ----------------
                        # print("\ninside_init: ",agent.deq_adl[num][t],"\n")
                        # --------------- print removed ----------------

                        agent.ADL_list.append(agent.deq_adl[num][t])
                        agent.new_ADL_list_for_nn.append(agent.deq_adl[num][t][0])
                        del agent.deq_adl[num][t]
                        # deq_adl[num].popleft()
                        # inside = True
                        break
                # agent.ADL_list.append(agent.deq_adl[num][0])
                # del agent.deq_adl[num][0] 

        else:
            agent.ADL_list = agent.new_ADL_list_for_concat    
        # -------------------------------------------------
       
        # --------------------------- removed print ------------------------------------
        # print("\nADL:",agent.ADL_list, "NN:", agent.new_ADL_list_for_nn)
        # --------------------------- removed print ------------------------------------

        # agent.ADL_list = agent.concat_adl(self.curr_step)
        agent.pow_set  = agent.ps.power_set(agent.ADL_list)
        agent.pow_set_for_nn = agent.ps.power_set(agent.new_ADL_list_for_nn)
        
        action_taken = self.find_sum(agent.pow_set_for_nn, action)

        # --------------------------- removed print ------------------------------------
        # print("action", action, "argmax_action",np.argmax(action))
        # -------------------------------------------------------------------

        agent.new_ADL_list_for_concat, agent.new_ADL_list_for_nn = agent.remove(action_taken,self.curr_step)
        
        agent.delay = agent.delay_time(self.curr_step)
        
        agent.amount_allocated = agent.amount_allocated_fn()
        agent.ndt = agent.temp_ren[self.curr_step] + agent.temp_bat[self.curr_step] - agent.temp_nadl[self.curr_step]
       
        remaining_steps = self.TOTAL_TIME_STEPS - self.curr_step-1
        self.time_is_over = (remaining_steps <= 0)
        
        if self.time_is_over:
            # print("\nadl_deque\n", agent.deq_adl, "\nunalloc_deque\n", agent.deq_for_unalloc)
            agent.is_all_allocated = agent.is_all()
            agent.failed_allocate = (self.time_is_over and (not agent.is_all_allocated))
            
            # --------------- print removed ----------------
            # if agent.failed_allocate:
                
                # print("Failed to allocate")
                # --------------- print removed ----------------
            # else:
                # --------------- print removed ----------------
                # print("Allocated!!")
                # --------------- print removed ----------------
            # --------------- print removed ----------------

                # agent.is_all_allocated = True  # abuse this a bit
                #self.cost = -10.0

    def _get_reward(self,agent, action):
        """Reward is given for energy_balance and all_allocated."""
        # for agent in agents:
        agent.cost=0

        if (((agent.amount_allocated - agent.ndt)) <= MAIN_POWER_MAX_LIMIT) and (((agent.amount_allocated - agent.ndt))>=MAIN_POWER_MIN_LIMIT):
            agent.cost += 1*agent.delay + self.unit_price[self.curr_step] * 10*(agent.amount_allocated - agent.ndt)
        else:
            agent.cost+=500
        
        agent.rew += (10 - (agent.time_step_not_fully_allocated*20)  - (agent.cost) - np.abs(int(action[1]) - agent.allocated_load.shape[0])*50 - np.abs(action[0] - agent.amount_allocated)*50)
        
        # --------------- print removed ----------------
        # print("\ncost = ", agent.cost, "\nreward = ", agent.rew, "time_step_not_fully_allocated", agent.time_step_not_fully_allocated, "\n")
        # --------------- print removed ----------------


        if self.time_is_over:
            if not agent.failed_allocate:
                # return self.price - 1
                agent.rew += (200)
                # --------------- print removed ----------------
                # print("\nfinal cost allocated = ", agent.cost, "\nfinal reward allocated = ", agent.rew, "\n")
                # --------------- print removed ----------------

            else:
                agent.rew -= 80.0*(len(agent.deq_for_unalloc[0])+len(agent.deq_for_unalloc[1])+len(agent.deq_for_unalloc[2])+len(agent.deq_for_unalloc[3]))
                
                # --------------- print removed ----------------
                # print("\nfinal cost unallocated = ", agent.cost, "\nfinal reward unallocated= ", agent.rew, "\n")
                # --------------- print removed ----------------
        
        return agent.rew

    def reset(self):
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

    def render(self, mode='human', close=False):
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
        
        if not self.time_is_over:
            agent.state.append(self.curr_step+1)
            agent.ndt = agent.temp_ren[self.curr_step+1] + agent.temp_bat[self.curr_step+1] - agent.temp_nadl[self.curr_step+1]
        else:
            agent.state.append(0)
            agent.ndt = 0
        agent.state.append(agent.ndt)
        
        # for i in agent.new_ADL_list_for_nn :
        #     agent.state.append(i)
        agent.state.append(np.sum(agent.new_ADL_list_for_nn))
        
        # ---------------------------------------- removed print -------------------------------
        # print(agent.state)
        # ---------------------------------------------------------

        # return state    #self.curr_step, self.ndt, self.new_ADL_list_for_nn
        
        # --------------- print removed ----------------
        # print(agent.state)
        # --------------- print removed ----------------

        return agent.state

    def _get_initial_state(self):
        #self._reset()
        self.agents = self.world.policy_agents

        self.curr_episode += 1
        
        self.time_is_over = False
        self.total_rew = 0
        self.curr_step = 0

        # ------------ price ----
        s = np.random.normal(9,2,1000)
        r = np.random.normal(10,4,1000)
        a = np.concatenate((s,r))
        w_gen = self.get12vals(a,12) 
        w_init = np.array([j for j in w_gen])
        w_init[ w_init < 0] = 0
        # w_init = (1*w_init).flatten()
        w_init = (w_init/np.sum(w_init) - np.finfo(np.float32).eps)
        mul = np.random.multinomial(12, w_init, size=1)
        self.unit_price = mul.flatten()+1

        initial_state_batch = []
        for i,agent in enumerate(self.agents):
            # initial_state_batch.append(agent.reset()) 
            agent.reset()
            agent.temp_adl = agent.adl_demand()
            agent.temp_nadl = agent.non_adl_demand()
            agent.temp_bat = agent.battery_gen()
            agent.temp_ren = agent.renewable_gen()
            agent.ndt = agent.temp_ren[0] + agent.temp_bat[0] - agent.temp_nadl[0]

            agent.state = list()
            agent.state.append(self.curr_step)
            agent.state.append(agent.ndt)
            sum=0
            for x in range(4):
                # agent.state.append(agent.deq_adl[x][0][0])
                sum+=agent.deq_adl[x][0][0]
            agent.state.append(sum)
            initial_state_batch.append(agent.state)
            
        return initial_state_batch
        # return obs_n

        # return self._get_obs()