import pandas as pd
import matplotlib.pyplot as plt

# Cargar datos desde el archivo CSV
filename = 'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Voluntario1/Magnetizacion.txt'
data = pd.read_csv(filename, header=None, names=['MagSuperior', 'ErrorSup', 'MagInferior', 'ErrorInf', 'Temperatura'])

# Calcular la magnetización total
data['MagTotal'] = data['MagSuperior'] + data['MagInferior']

# Graficar los datos
plt.figure(figsize=(10, 6))

# Graficar la magnetización superior
plt.errorbar(data['Temperatura'], data['MagSuperior'], yerr=data['ErrorSup'], fmt='-', linewidth=1, capsize=5, elinewidth=2, label='Magnetización Superior', color='blue')

# Graficar la magnetización inferior
plt.errorbar(data['Temperatura'], data['MagInferior'], yerr=data['ErrorInf'], fmt='-', linewidth=1, capsize=5, elinewidth=2, label='Magnetización Inferior', color='red')

# Graficar la magnetización total
plt.plot(data['Temperatura'], data['MagTotal'], '-.', linewidth=1, label='Magnetización Total', color='green')

# Añadir etiquetas y título
plt.xlabel('Temperatura (K)')
plt.ylabel('Magnetización (1/Am)')
plt.title('Magnetización vs Temperatura: N=64, 50000 Pasos Montecarlo')
plt.legend()

# Mostrar la gráfica
plt.grid(True)
plt.show()
