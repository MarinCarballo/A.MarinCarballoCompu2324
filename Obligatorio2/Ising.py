from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import scipy as sp
import io

#Dimensiones de la red bidimensional
N=80
#Temperatura
T=0.0001
#Tiempo de compilado
Tmax=10e5
t=0
#Paso
h=1
#Declaro s con valores aleatorios, -1 o 1.
f=open("C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Obligatorio2/Ising.txt", "w")

s=np.random.choice([-1,1], (N,N))
while(t<Tmax):
    for j in range (0,N+1):
        n=np.random.randint(0,N)
        m=np.random.randint(0,N)
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

        E=2.0*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d])

        p=min(1.0, np.exp(-E/T))
        
        if(p>np.random.rand()):
            s[n][m]=-s[n][m]

    for i in range(N):
        # Recorrer columnas
        for j in range(N-1):
            # Escribir elemento en formato s(i, j)
            f.write(f'{s[i][j]},')  # Agregar un tabulador para separar los elementos
        f.write(f'{s[i][j]}')
        f.write('\n')  # Cambiar de línea después de escribir una fila
    f.write('\n')
    t=t+N*N
f.close()