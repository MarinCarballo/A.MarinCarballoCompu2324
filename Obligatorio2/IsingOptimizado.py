from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import scipy as sp
import io
import time
from numba import jit
@jit(nopython=True)
def CondicionesContorno(n,m):
    a = (n + 1) % N #Si n+1 es N, el resto será 0, la posición será cero.
    b = (n - 1 + N) % N #Si n-1 es -1, el resto es N-1, la posición será N-1.
    c = (m + 1) % N
    d = (m - 1 + N) % N
    return a,b,c,d
start_time = time.time()
#Dimensiones de la red bidimensional
N=100
#Temperatura
T=1
#Tiempo de compilado
Tmax=1000
t=0
#Declaro s con valores aleatorios, -1 o 1.
f=open("C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Obligatorio2/Ising.txt", "w")
s=np.random.choice([-1,1], (N,N))
while(t<Tmax):
    k=0
    while(k<N*N):
        n=np.random.randint(0,N)
        m=np.random.randint(0,N)

        a,b,c,d=CondicionesContorno(n,m)

        E=2.0*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d])

        p=min(1.0, np.exp(-E/T))
        
        if(p>np.random.rand()):
            s[n][m]=-s[n][m]
        k=k+1
    for i in range(N):
        f.write(','.join(map(str, s[i])) + '\n')
    f.write('\n')
    t=t+1
f.close()
print("Tiempo de compilado:--- %s seconds ---" % (time.time() - start_time))