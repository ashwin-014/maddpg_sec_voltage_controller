import matplotlib.pyplot as plt
import numpy as np
import csv

def adl_gen(n_days):
    x_w_batch = []
    for x in range(4):        
        w_batch = []
        for i in range(n_days) :    
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

            w_batch.append(new_arr)
        w_batch = np.rint(w_batch)
        print(len(w_batch))

        plt.figure()
        x_w_batch.append(w_batch)
        for j in range(n_days):
            print(j)
            # plt.subplot(8,4,j+1)
            # plt.plot(w_batch[j])
            
    plt.plot(np.rint(w*50))
    plt.show()

    for f in range(4):
        with open('adl_house_'+str(f)+'.csv', 'w') as file:
            writer = csv.writer(file)
            writer.writerows(x_w_batch[f])#[k] for k in range(n_days))

def non_adl_gen(n_days):
    x_w_batch = []
    for x in range(4):  
        w_batch = []
        for i in range(n_days) :  
            s = np.random.normal(9,2,1000)
            r = np.random.normal(4,4,1000)
            a = np.concatenate((s,r))
            w,x,y = plt.hist(a,12,normed=True)
            # plt.plot(w)
            # plt.show()
            w_batch.append(w*100)
        w_batch = np.rint(w_batch)
        x_w_batch.append(w_batch)
        for j in range(n_days):
            print(j)
            # plt.subplot(4,4,j+1)
            # plt.plot(w_batch[j])
            
        # plt.show()
    for f in range(4):
        with open('non_adl_house'+str(f)+'.csv', 'w') as file:
            writer = csv.writer(file)
            writer.writerows(x_w_batch[f] )

def renewable_gen(n_days):
    x_w_batch = []
    for x in range(4):
        w_batch = []
        for i in range(n_days) : 
            s = np.random.normal(6,3.5,1000)
            # r = np.random.normal(4,4,1000)
            # a = np.concatenate((s,r))
            w,x,y = plt.hist(s,12,normed=True)
            # plt.plot(w)
            # plt.show()
            w_batch.append(w*100)
        w_batch = np.rint(w_batch)
        x_w_batch.append(w_batch)
        for j in range(n_days):
            print(j)
            # plt.subplot(4,4,j+1)
            # plt.plot(w_batch[j])
            
        # plt.show()
    for f in range(4):
        with open('ren_house_'+str(f)+'.csv', 'w') as file:
            writer = csv.writer(file)
            writer.writerows(x_w_batch[f] )

def battery_gen(n_days):
    x_w_batch = []
    for x in range(4):
        w_batch = []
        for i in range(n_days) :
            s = np.random.normal(11,2,1000)
            r = np.random.normal(3,4,1000)
            a = np.concatenate((s,r))
            w,x,y = plt.hist(a,12,normed=True)
            # plt.plot(w)
            # plt.show()
            w_batch.append(w*50)
        w_batch = np.rint(w_batch)
        x_w_batch.append(w_batch)
        for j in range(n_days):
            print(j)
            # plt.subplot(4,4,j+1)
            # plt.plot(w_batch[j])
        
        # plt.show()
    for f in range(4):
        with open('battery_house_'+str(f)+'.csv', 'w') as file:
            writer = csv.writer(file)
            writer.writerows(x_w_batch[f])   

def main():
    adl_gen(30)
    non_adl_gen(16)
    renewable_gen(16)
    battery_gen(16)

if __name__ == '__main__':
    main()

