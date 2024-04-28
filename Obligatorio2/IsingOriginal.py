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

N=120

#Tiempo de compilado
Tmax=10e3
#Dimensiones de la red bidimensional
#Mag=np.zeros(int(Tmax/N*N))
#magnetizacion=0
#Temperatura
T=1
t=0
#suma=0
#Declaro s con valores aleatorios, -1 o 1.
f=open("C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Obligatorio2/Ising.txt", "w")
k=0
s=np.random.choice([-1,1], (N,N))
while(t<Tmax):
    for j in range(0,N*N):
        n=np.random.randint(0,N)
        m=np.random.randint(0,N)
        #Condiciones de contorno
        a,b,c,d=CondicionesContorno(n,m)

        E=2.0*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d])

        p=min(1.0, np.exp(-E/T))
        
        if(p>np.random.rand()):
            s[n][m]=-s[n][m]
        k+=1

    for i in range(N):
        # Recorrer columnas
        for j in range(N-1):
            # Escribir elemento en formato s(i, j)
            f.write(f'{s[i][j]},')  # Agregar un tabulador para separar los elementos
        f.write(f'{s[i][j]}')
        f.write('\n')  # Cambiar de línea después de escribir una fila
    f.write('\n')
    t=t+1
f.close()

    