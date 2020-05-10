import numpy as np
import matplotlib.pyplot as plt

f = open("data15.csv")
raw = f.readline()

# Digital filter
b = [0.0201,    0.0402 ,   0.0201]
a = [1.0000,   -1.5610,    0.6414]

det = []; sx = []; sy = []; sz = []
dx = []; dy = []; dz = []; tot = []
lpf = []

for i in range(1000):
    try:
        raw = f.readline().strip()
        aa,ba,ca,da = raw.split(",")
        det.append(float(aa))
        sx.append(float(ba))
        sy.append(float(ca))
        sz.append(float(da))
    except:
        pass
    
det = np.array(det)
sx = np.array(sx)
sy = np.array(sy)
sz = np.array(sz)

jmldata = 10
varx = np.array([])
vary = np.array([])
varz = np.array([])
for i in range(len(sx)):
    varx = np.append(varx, np.sum((sx[i] - np.mean(sx[i-jmldata:i]))**2) / jmldata)
    vary = np.append(vary, np.sum((sy[i] - np.mean(sy[i-jmldata:i]))**2) / jmldata)
    varz = np.append(varz, np.sum((sz[i] - np.mean(sz[i-jmldata:i]))**2) / jmldata)
    

plt.subplot(211)    
plt.plot(sx)
plt.plot(sy)
plt.plot(sz)
plt.legend(['acc x', 'acc y', 'acc z'])
plt.xlabel("Time")

plt.subplot(212)
plt.plot(varx)
plt.plot(vary)
plt.plot(varz)
plt.xlabel("Time")
plt.ylabel("Variance")
plt.show()
