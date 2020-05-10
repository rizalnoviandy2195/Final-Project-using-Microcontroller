import statistics as st
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


read = pd.read_excel (r'D:\cita2\sem 10\Data\10 jatuh depan\10 data jatuh depan.xlsx', sheet_name='1 akmal')

data1 =read['SUM']
a1 = 0
a2 = 3

for i in range(0,len(data1)-1):
    data2 = st.mean(data1[a1:a2])
    data1[i] = data2
    print(int(data1[i]))
    a1 = a2 
    a2 = a1 + 3
    plt.plot(data1[i])

plt.show(data1)


    
    

"""for i in range(0,len(data1)):
    data1[i] = data2[i]
    a1 = a2 + 1
    a2 = a1 + 5
    print(data1[i])
    
for i in range(a1
    proses1[i] = [mean(range(a1,,a2)]
    print(proses1)"""




"""#program lain

read = pd.read_excel (r'D:\cita2\sem 10\Data\10 jatuh depan\10 data jatuh depan.xlsx', sheet_name='1 akmal')
data=read['mean']
data=data.dropna()
#print (data[0], data[1], data[2])
ba = 0
jarak = 2
bb = jarak
average = []
j = 0

for i in range(0,len(data)):
    data1 = (st.mean(data[ba:bb])) 
    average.append(data1)
    print("ba",data[ba],"bb",data[bb],"data1",data1) 
    data1 = 0
    ba = bb + 1 
    bb  = ba + jarak 
    #print("data ke",i,"=",data[i])
    
    #x = data[i] + data[i+1]
    #print(data[i])
    #average.append(x/n)
    #i+=1
    #print("datai", data[i], "x", x)
    #if (i%n == 0 and i!=0):
    #    average.append(x/n)
    #    j = j + 1
    #    x = 0

#print(average)"""
        
        

#list1 = pd.DataFrame(read, columns= list(['mean']))
#print(list1)

"""#list1 = [2,4,1,3,5,6,45,33,28,4,21,21]
n = 3

list2 = [st.mean(list1[i:i+n]) for i in range(0,len(list1),n)]

for i in range(0,len(list1),n):
    list1[i] = list2[i//n]
    print(list1[i])"""
    
