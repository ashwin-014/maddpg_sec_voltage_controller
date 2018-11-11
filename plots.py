import numpy as np
import matplotlib.pyplot as plt

w_init = np.array([ 0.00667176,  0.11875733,  0.37361857,  0.15945507,  0.00867329,  0., 0., 0.,  0.00400306,  0.14010697,  0.43299724,  0.09006876])
w_init = w_init*75

probs = np.random.random(12)
wx=w_init*(probs-0.5) + w_init
wx = np.rint(wx)
wx = wx/np.sum(wx)
print(wx)
plt.plot(wx)
plt.show()

# -------------------- Non ADL gen --------------------------------
# s = np.random.normal(9,2,1000)
# r = np.random.normal(4,4,1000)
# a = np.concatenate((s,r))
# w,x,y = plt.hist(a,12,normed=True)
w = np.array([ 0.00149354,  0.00273815,  0.01194831,  0.02041169,  0.03659169, 0.04381046,  0.06247969,  0.09334615,  0.13018676 , 0.0734323,   0.01842031,0.00298708])
w_non_adl = w*100
probs = np.random.random(12)
wx=w_non_adl*(probs-0.4) + w_non_adl
wx = np.rint(wx)
wx = wx/np.sum(wx)
print(wx)
plt.plot(wx)
plt.show()

# -------------------- Ren gen --------------------------------
# s = np.random.normal(6,3.5,1000)
# w,x,y = plt.hist(s,12,normed=True) 
w = np.array([ 0.00537982,  0.0145255,   0.03765872,  0.06778569,  0.10383046,  0.12104587,  0.09468477,  0.0527222,   0.02689908,  0.00914569,  0.00322789,  0.00107596])
w_ren = w*100
probs = np.random.random(12)
wx=w_ren*(probs-0.2) + w_ren
wx = np.rint(wx)
wx = wx/np.sum(wx)
print(wx)
plt.plot(wx)
plt.show()

# -------------------- Battery gen --------------------------------
# s = np.random.normal(11,2,1000)
# r = np.random.normal(3,4,1000)
# a = np.concatenate((s,r))
# w,x,y = plt.hist(a,12,normed=True)
w = np.array([ 0.00157395,  0.004497,    0.01596436,  0.02743172,  0.04474518,  0.04699368,  0.04429548,  0.05014158,  0.09038976,  0.0865673,   0.03170387,  0.0053964 ])
w_bat = w*50
probs = np.random.random(12)
wx=w_ren*(probs-0.5) + w_ren
wx = np.rint(wx)
wx = wx/np.sum(wx)
print(wx)
plt.plot(wx)
plt.show()