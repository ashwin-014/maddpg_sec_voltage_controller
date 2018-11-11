import numpy as np
import matplotlib.pyplot as plt

from math import ceil

def get12vals(sequence, num):
    length = float(len(sequence))
    for i in range(num):
        yield sequence[int(ceil(i * length / num))]


mu_s = 9 + np.random.normal(0,1)*((-1)**np.random.randint(0,1))
std_s = 0.4 + np.random.normal(0,0)*((-1)**np.random.randint(0,1))

mu_r = 4 + np.random.normal(0,1)*((-1)**np.random.randint(0,1))
std_r = 0.5 + np.random.normal(0,0)*((-1)**np.random.randint(0,1))

# -------------------- ADL gen --------------------------------
# s = np.random.normal(mu_s,std_s,1000)
# r = np.random.normal(mu_r,std_r,1000)

s = np.random.normal(8,4,100)

# plt.plot(s, np.arange(0,100))
# plt.show()

r = np.random.normal(10,4,100)

a = np.concatenate((s,r))

w_gen = get12vals(a,12) 
w_init = [j for j in w_gen]

# print(w_init)
# w_init = np.array([ 0.00667176,  0.11875733,  0.37361857,  0.15945507,  0.00867329,  0., 0., 0.,  0.00400306,  0.14010697,  0.43299724,  0.09006876])



w_init = w_init/np.sum(w_init)
# print(w_init)

# mul = np.random.multinomial(12, w_init, size=1)
# print(mul[0])
# mul = [1 if mul[0][i]>0 else 0 for i in range(len(mul))]
# mul = mul > 0
# mul = (1*mul).flatten()
# mul = np.reshape(1*mul,[-1, len(mul)])
# print(mul, mul.shape)

# ---------------- Non ADL ----------------

# s = np.random.normal(9,2,1000)
# r = np.random.normal(10,4,1000)
# a = np.concatenate((s,r))
# w_gen = get12vals(a,12) 
# w_init = [j for j in w_gen]
# w_init = (w_init/np.sum(w_init) - np.finfo(np.float32).eps)
# mul = np.random.multinomial(12, w_init, size=1)
# print(mul[0])
# # mul = mul > 0
# # mul = (1*mul).flatten()
# print(mul.flatten()+1, mul.shape)

# w_ren = mul*10
# probs = np.random.random(12)
# wx=np.rint(w_ren*(probs-0.2) + w_ren)
# wx/=max(wx)
# print(wx)

# ---------------- Non ADL ----------------

w = np.array([ 0.00149354,  0.00273815,  0.01194831,  0.02041169,  0.03659169, 0.04381046,  0.06247969,  0.09334615,  0.13018676 , 0.0734323,   0.01842031,0.00298708])
w_non_adl = w*100
probs = np.random.random(12)
wx=np.rint(w_non_adl*(probs-0.2) + w_non_adl)
wx/=max(wx)
print("non adl", wx*0.267)
# ---------------- ren ----------------

# s = np.random.normal(6,3.5,1000)
# w_gen = get12vals(a,12) 
# w_init = [j for j in w_gen]
# print(w_init)

# w_init = np.array([ 0.00537982,  0.0145255,   0.03765872,  0.06778569,  0.10383046,  0.12104587,  0.19468477,  0.1527222,   0.12689908,  0.0914569,  0.00322789,  0.00107596])
# w_init = (w_init/np.sum(w_init)) - np.finfo(np.float32).eps

# mul = np.random.multinomial(12, w_init, size=1)
# print(mul[0])
# mul = mul > 0
# mul = (1*mul).flatten()
# print(mul, mul.shape)

# plt.plot(mul)
# plt.show()

w = np.array([ 0.00537982,  0.0145255,   0.03765872,  0.2778569,  0.30383046,  0.9668477,  0.9668477,  0.9668477,   0.95689908,  0.40914569,  0.10322789,  0.00107596])
w_ren = w*10
probs = np.random.random(12)
wx=np.rint(w_ren*(probs-0.2) + w_ren)
wx/=max(wx)
# wx = np.rint(wx)
# wx = wx/np.sum(wx)
# wx[wx>0.1] = 1
# wx = wx - min(wx) / (max(wx)-min(wx))
print("ren",wx*2.500) #/max(wx)
# plt.plot(wx*4)
# plt.show()

w = np.array([ 0.00157395,  0.004497,    0.01596436,  0.02743172,  0.04474518,  0.04699368,  0.04429548,  0.05014158,  0.09038976,  0.0865673,   0.03170387,  0.0053964 ])
w_bat = w*50
probs = np.random.random(12)
wx=w_ren*(probs-0.5) + w_ren
wx = np.rint(wx)
wx/=max(wx)
# wx = wx/np.sum(wx)
print("bat",wx*3)

# ------------ price ----
s = np.random.normal(9,2,1000)
r = np.random.normal(10,4,1000)
a = np.concatenate((s,r))
w_gen = get12vals(a,12) 
w_init = np.array([j for j in w_gen])
w_init[ w_init < 0] = 0
# w_init = (1*w_init).flatten()
w_init = (w_init/np.sum(w_init) - np.finfo(np.float32).eps)
mul = np.random.multinomial(12, w_init, size=1)
unit_price = mul.flatten()+3
print("price:", unit_price)

