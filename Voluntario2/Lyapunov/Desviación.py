import matplotlib.pyplot as plt
import pandas as pd

# Cargar datos desde el archivo CSV
file_path = 'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Voluntario2/desvia.csv'  # Cambia esta línea con la ruta correcta a tu archivo
data = pd.read_csv(file_path)

# Asignar columnas a las variables correspondientes
phi1 = data.iloc[:, 0]  # Primera columna
psi1 = data.iloc[:, 1]  # Segunda columna
phi2 = data.iloc[:, 2]  # Tercera columna
psi2 = data.iloc[:, 3]  # Cuarta columna

# Crear la gráfica
plt.figure(figsize=(10, 6))
plt.plot(phi1, psi1, '-', linewidth=0.5, markersize=2, label='$\\phi=0.1$, $\\psi=0.3$')
plt.plot(phi2, psi2, '-', linewidth=0.5, markersize=2, label='$\\phi=0.105$, $\\psi=0.305$')

# Añadir títulos y etiquetas
plt.title('Mapa de Poincaré, E=1')
plt.xlabel('$\\phi$ (radianes)')
plt.ylabel('$\\psi$ (radianes)')

# Añadir grid
plt.grid(True)

# Añadir leyenda
plt.legend()

# Mostrar la gráfica
plt.show()
