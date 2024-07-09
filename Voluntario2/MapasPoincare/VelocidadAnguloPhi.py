import matplotlib.pyplot as plt
import pandas as pd
params = {'mathtext.default': 'regular' }          
plt.rcParams.update(params)

# Ruta del archivo CSV
file_path = 'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Voluntario2/MapasPoincare/PhiPunto.csv'

# Cargar datos desde el archivo CSV
data = pd.read_csv(file_path)

# Energías específicas
energias_especificas = [1, 3, 5, 10, 15]

# Colores para cada energía
colores = ['b', 'g', 'r', 'c', 'm']

# Crear la gráfica
plt.figure(figsize=(10, 6))

# Iterar sobre las energías específicas y sus respectivos pares de columnas
for i, E in enumerate(energias_especificas):
    phi = data.iloc[:, 2 * i]
    psi = data.iloc[:, 2 * i + 1]
    plt.plot(phi, psi, '-', linewidth=0.5, markersize=2, label=f'E={E}', color=colores[i])

# Añadir títulos y etiquetas
plt.title('Mapa de Poincaré, $\dot{\phi}$ frente a $\phi$, [$\phi_i$=0.1 rad, $ψ_i$=0.3 rad]')
plt.xlabel('$\phi (radianes)$')
plt.ylabel('$\dot{\phi} (radianes/s)$')

# Añadir grid
plt.grid(True)

# Añadir leyenda
plt.legend()

# Mostrar la gráfica
plt.show()
