#Untuk Tugas 1

import numpy as np
import csv

f = open("datagabung1010.csv") #membuka file input
raw = f.readline()

ax = []; ay = []; az = []; sumvar = []; hasil = []; #membuat array untuk xyz

for i in range(7):
    try:
        raw = f.readline().strip() #strip -> leading space of a line string are removed
        aa,ab,ac,ad,ae,af,ag = raw.split(";") #memisahkan koma dari file csv, lihat csvmu ada yg [,] ada yg [;]
        ax.append(float(aa)) #memasukkan aa ke array ax
        ay.append(float(ab))
        az.append(float(ac))
        sumvar.append(float(ag))
    except:
        pass #apakah meskipun program di atas ada yang eror tetap dilanjutkan ke baris program selanjutnya?


    jmldata = 2 #per berapa data
    ax = str(ax)
    ay = str(ay)
    az = 

    for i in range(len(ax)-jmldata + 1):
            if sumvar[i] > 100000000:
                status = 1
            else:
                status = 0

            hasil = str(ax[i:i+jmldata]) + ", " + str(ay[i:i+jmldata]) + ", " + str(az[i:i+jmldata])

            print(hasil.replace("[","").replace("]",""))

    
    
