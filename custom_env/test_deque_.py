import random
import math
# 3rd party modules
import numpy as np
from itertools import chain, combinations
import matplotlib.pyplot as plt
from collections import deque
# --------------------------------------------------------------------------------------------------------



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

deq_adl_0 = deque(x_w_batch[:,0,:])
deq_adl_1 = deque(x_w_batch[:,1,:])
deq_adl_2 = deque(x_w_batch[:,2,:])
deq_adl_3 = deque(x_w_batch[:,3,:])

print(deq_adl_0, deq_adl_1, deq_adl_2, deq_adl_3)

deq_adl = []
for x in range(4):
    deq_adl.append(deque(x_w_batch[:,x,:])) 
# print(deq_adl[0], deq_adl[1], deq_adl[2], deq_adl[3])
for x in range(4):
    deq_adl[x].pop()
# print(deq_adl[0][0], deq_adl[1], deq_adl[2], deq_adl[3])

time = 11

for t in range(time):
    adl_list_new=[]
    for num in range(4):

        adl_list_new.append(deq_adl[num][0])
        deq_adl[num].popleft()
    print(adl_list_new)


num=t=i=0
deq_adl = []
for x in range(4):
    deq_adl.append(deque(x_w_batch[:,x,:])) 
print("deq_adl",deq_adl)

deq_for_unalloc = []
for x in range(4):
    # r = deque(x_w_batch[:,x,:])
    deq_for_unalloc.append(deque(reversed(deque(x_w_batch[:,x,:])))) 
print("deq_unalloc",deq_for_unalloc)

for i in range(time):
    adl_list_new=[]
    for num in range(4):
        unalloc_in = False
        if np.all(deq_for_unalloc[num][0]):
            adl_list_new.append(deq_for_unalloc[num][0]) 
            deq_for_unalloc[num].popleft()
            print("inside unalloc")
            unalloc_in = True
            # continue

        elif (len(adl_list_new) < (num+1) ):
            # code here
            inside = False
            for t in range(time-i):
                print("out",t,"deq",deq_adl[num][t][0])
                if(deq_adl[num][t][0]) :
                    print("inside",deq_adl[num][t][0])
                    adl_list_new.append(deq_adl[num][t])
                    del deq_adl[num][t]
                    # deq_adl[num].popleft()
                    inside = True
                    break

            if inside==False:
                adl_list_new.append(np.array([0.,13.]))
        if unalloc_in:
            if(np.all(deq_adl[num][0][0])) :
                deq_for_unalloc[num].append(deq_adl[num][0])
                del deq_adl[num][0]
                print("inside appending for unalloc existing")
            else:
                del deq_adl[num][0]
                print("inside appending fofr unalloc zero")

    print(adl_list_new)        

print("deq_adl",deq_adl)
print("unallocated:",deq_for_unalloc)

class agent(object):
    def __init__():

        for x in range(4):
            deq_adl[x] = deque()
        for x in range(4):
            deq_for_unalloc[x] = deque()
        
    def dq_append(self, parameter_list):
        pass

    def dq_pop(self, parameter_list):
        pass

    def concat_adl(self, old_adl, curr_adl):
        self.ADL_list = []
        i=0
        
        for x in old_adl:        
           
            if x[0] != 0 :
                self.ADL_list.append(np.asarray(old_adl[i]))
            else:
                self.ADL_list.append(np.asarray(curr_adl[i]))
            i=i+1
        
        # ---------------------------------------- removed print -------------------------------
        # print("concat",self.ADL_list)
        # -----------------------------------------------------------------------

        return self.ADL_list

    def is_all(self):
        if not np.any(self.new_ADL_list_for_nn ) : #== [0,0,0,0] 
            return True
        else:
            return False

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

                if not (np.any(np.all(self.ADL_list[0] == self.allocated_load, axis=1))):
                    temp3.append(item)
                    deq_for_unalloc_0.appendleft(item)
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