import math as mt
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
file_name =  'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Obligatorio1/energias.txt'
#Créditos a Daniel Hernández.
data = pd.read_csv(file_name, delimiter=',', header=1, names=['m', 'V', 'E', 't'])
print(data)

fig=plt.figure(figsize=[30,30])
ax=fig.gca()
plt.plot( data.t, data.m, 'b')
plt.plot( data.t, data.E, 'r')
plt.plot( data.t, data.V, 'g')

plt.ylabel(r'E',fontsize=30)
plt.xlabel(r't',fontsize=30)
for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(2)
    
plt.grid()

plt.tick_params(axis="x", labelsize=20, labelrotation=0, labelcolor="black")
plt.tick_params(axis="y", labelsize=20, labelrotation=0, labelcolor="black")

#plt.xlim(0,0.3)
#plt.ylim(data.x[0],data.x[100])
plt.show()