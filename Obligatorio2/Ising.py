from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import scipy as sp
import io
from numba import jit
#Funciones
@jit(nopython=True)
def CondicionesContorno(n,m):
    #Condiciones de contorno
    if(n==N-1):#Si mi n está en el extremo N, quiero que a(que representa n+1 en E) 
        a=0  #sea el del otro extremo
    else:
        a=n+1
    if(n==0):#Si mi n está en el extremo 0, quiero que b(que representa n-1 en E) 
        b=N-1 #sea el del otro extremo
    else:
        b=n-1
    if(m==N-1):#Si mi m está en el extremo N, quiero que c(que representa m+1 en E) 
        c=0  #sea el del otro extremo
    else:
        c=m+1
    if(m==0):#Si mi m está en el extremo 0, quiero que d(que representa m+1 en E) 
        d=N-1  #sea el del otro extremo
    else:
        d=m-1
    return a,b,c,d
#Dimensiones de la red bidimensional
N=10
#Temperatura
T=1
k=0
#Tiempo de compilado
Tmax=10
t=0
#Declaro s con valores aleatorios, -1 o 1.
f=open("C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Obligatorio2/data.txt", "w")
s=np.random.choice([-1,1], (N,N))
while(t<Tmax):
    while k<N*N:
        k+=1
        n=np.random.randint(0,N)
        m=np.random.randint(0,N)
        #Condiciones de contorno
        a = (n + 1) % N #Si n+1 es N, el resto será 0, la posición será cero.
        b = (n - 1 + N) % N
        c = (m + 1) % N
        d = (m - 1 + N) % N

        E=2.0*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d])

        p=min(1.0, np.exp(-E/T))
        
        if(p>np.random.rand()):
            s[n][m]=-s[n][m]

    for i in range(N):
        f.write(','.join(map(str, s[i])) + '\n')
    f.write('\n')
    t=t+1
f.close()