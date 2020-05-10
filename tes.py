import numpy as np

f = open("datagabung1.csv") #membuka file input
raw = f.readline()


for i in range(30000):
    try:
        raw = f.readline().strip() #strip -> leading space of a line string are removed
        aa,ab,ac,ad,ae,af,ag = raw.split(";") #memisahkan koma dari file csv, lihat csvmu ada yg [,] ada yg [;]
        ax.append(float(aa)) #memasukkan aa ke array ax
        ay.append(float(ab))
        az.append(float(ac))
        sumvar.append(float(ag))
    except:
        pass

