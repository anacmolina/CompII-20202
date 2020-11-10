#================================================
# Codigo de diferencias finitas no lineares     |
#                                               |    
# Oscilador forzado Graficas                    | 
#  
# Andres Arteaga                                |  
# Ana Cristina Molina                           |
#                                               |   
# Update: 10 de noviembre de 2020               |
#================================================


#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np

x_n=[] 
y_n=[] 

x_a=[] 
y_a=[] 

E_=[]

for i in range(100,1100,100):
    x_nt,y_nt = np.loadtxt('F-D_n_'+str(i)+'.txt', unpack=True)
    x_at,y_at = np.loadtxt('F-D_a_'+str(i)+'.txt', unpack=True)
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
for i in range(100,1100,100):
    N.append(i)

plt.figure(figsize=(8,6))
plt.plot(x_n[1],y_n[1],label=r'$x(t)$ numerica N=200')
plt.plot(x_n[5],y_n[5],label=r'$x(t)$ numerica N=600 ')
plt.plot(x_n[9],y_n[9],label=r'$x(t)$ numerica N=1000')
plt.plot(x_a[-1],y_a[-1],'--',label=r'$x(t)$ analitica ')
plt.grid()
plt.legend()
plt.xlabel('t [s]')
plt.ylabel('x(t) [m]')
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
