#Untuk Tugas 1

import numpy as np
import csv

f = open("datagabung1010.csv") #membuka file input
raw = f.readline()

ax = []; ay = []; az = []; sumvar = []; hasil = []; #membuat array untuk xyz

for i in range(100):
    try:
        raw = f.readline().strip() #strip -> leading space of a line string are removed
        aa,ab,ac,ad,ae,af,ag = raw.split(";") #memisahkan koma dari file csv, lihat csvmu ada yg [,] ada yg [;]
        ax.append(float(aa)) #memasukkan aa ke array ax
        ay.append(float(ab))
        az.append(float(ac))
        sumvar.append(float(ag))
        print(" ,".join(str(ax)))
    except:
        pass #apakah meskipun program di atas ada yang eror tetap dilanjutkan ke baris program selanjutnya?

     
"""
with open('hasilTugas1colab.csv', mode='w') as file:
    writer = csv.writer(file, delimiter=',', quotechar=' ', quoting=csv.QUOTE_MINIMAL)

    jmldata = 10 #per berapa data
        #hasil = np.array([])

    for i in range(len(ax)-jmldata + 1):
            if sumvar[i] > 100000000:
                status = 1
            else:
                status = 0
        
            hasil1 = "".join(str(ax[i:i+jmldata]))
            #hasil2 = ay[i:i+jmldata]
            #hasil3 = az[i:i+jmldata]
            #hasil = str(hasil)
            print (hasil1)
            #writer.writerow(hasil)
    #        np.savetxt("array.txt", [ax[i:i+jmldata],ay[i:i+jmldata],az[i:i+jmldata],status], fmt="%s")
    #writer.writerow([ax[i:i+jmldata], ay[i:i+jmldata], az[i:i+jmldata], status])
    
"""    
