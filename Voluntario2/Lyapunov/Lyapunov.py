import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import pandas as pd

# Leer el archivo CSV
file_path = 'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Voluntario2/Lyapunov/Lyapunov2.csv'  # Reemplaza esto con la ruta a tu archivo CSV
data = pd.read_csv(file_path)

# Asumiendo que la primera columna es t y las siguientes son las energías E=1, 3, 5, 10, 15
t = data.iloc[:, 0]
E1 = data.iloc[:, 1]
E3 = data.iloc[:, 2]
E5 = data.iloc[:, 3]
E10 = data.iloc[:, 4]
E15 = data.iloc[:, 5]

# Crear la gráfica
plt.figure(figsize=(10, 6))
plt.plot(t, E1, label='$[E_1=1, E_2=1.5]$', color='b')
plt.plot(t, E3, label='$[E_1=3, E_2=3.5]$', color='g')
plt.plot(t, E5, label='$[E_1=5, E_2=5.5]$', color='r')
plt.plot(t, E10, label='$[E_1=10, E_2=10.5]$', color='c')
plt.plot(t, E15, label='$[E_1=15, E_2=15.5]$', color='m')

# Añadir leyenda
plt.legend()

# Etiquetas de los ejes
plt.xlabel('Tiempo t')
plt.ylabel('Coeficiente de Lyapunov λ')

# Título del gráfico
plt.title('Coeficiente de Lyapunov λ en función de t para perturbación de energía $\Delta E=0.5$')

# Mostrar la gráfica
plt.grid(True)
plt.show()
