#================================================
# Codigo de diferencias finitas no lineares     |
#                                               |    
# Burden Sec 11.4 - Ejercicio 1 Graficas        | 
#  
# Andres Arteaga                                |  
# Ana Cristina Molina                           |
#                                               |   
# Update: 10 de noviembre de 2020               |
#================================================


import matplotlib.pyplot as plt
import numpy as np

x_n=[] 
y_n=[] 

x_a=[] 
y_a=[] 

E_=[]

for i in range(1,21):
    x_nt,y_nt = np.loadtxt('ejercicio1_n_'+str(i)+'.txt', unpack=True)
    x_at,y_at = np.loadtxt('ejercicio1_a_'+str(i)+'.txt', unpack=True)
    x_n.append(x_nt)
    y_n.append(y_nt)
    x_a.append(x_at)
    y_a.append(y_at)

for i in range(len(x_a)):
    Et=np.abs(y_n[i]-y_a[i])
    E_.append(Et)

for i in range(len(x_a)):
    E_[i]=E_[i].mean()

N=[]
for i in range(1,21):
    N.append(i)

plt.figure(figsize=(8,6))
""" plt.plot(x_n[0],y_n[0],label=r'$y(x) numerica N=1 $')"""
plt.plot(x_n[1],y_n[1],label=r'$y(x)$ numerica N=2, h=1/3')
"""plt.plot(x_n[2],y_n[2],label=r'$y(x) numerica N=3 $')
plt.plot(x_n[3],y_n[3],label=r'$y(x) numerica N=4 $')
plt.plot(x_n[4],y_n[4],label=r'$y(x) numerica N=5 $')"""
plt.plot(x_n[5],y_n[5],label=r'$y(x)$ numerica N=6, h=1/7')
"""plt.plot(x_n[6],y_n[6],label=r'$y(x) numerica N=7 $')
plt.plot(x_n[7],y_n[7],label=r'$y(x) numerica N=8 $') 
plt.plot(x_n[8],y_n[8],label=r'$y(x) numerica N=9 $')"""
plt.plot(x_n[9],y_n[9],label=r'$y(x)$ numerica N=10, h=1/11')
plt.plot(x_a[-1],y_a[-1],'--',label=r'$y(x)$ analitica ')
plt.grid()
plt.xlabel('x')
plt.ylabel('y(x)')
plt.legend()
plt.savefig('Grafica.png')
plt.show()

plt.figure(figsize=(8,6))
plt.plot(N,E_,label=r'Error = mean[$|y_{exct}(x) - y_{num}(x)|$]')
plt.grid()
plt.xlabel('N')
plt.ylabel('Error')
plt.legend()
plt.savefig('Grafica2.png')
plt.show()
