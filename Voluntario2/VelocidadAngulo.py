import matplotlib.pyplot as plt
import pandas as pd

# Cargar datos desde el archivo CSV
file_path = 'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Voluntario2/VelocidadAngulo.txt'
data = pd.read_csv(file_path)

phi = data.iloc[:, 0]
psi = data.iloc[:, 1]

# Crear la gráfica
plt.figure(figsize=(10, 6))
plt.plot(phi, psi, 'o-', linewidth=0.5, markersize=2)  # Ajustar el grosor de las líneas y el tamaño de los marcadores

# Añadir títulos y etiquetas
plt.title('Velocidad $\dot{\phi}$ frente a $\phi$')
plt.xlabel('$\phi (radianes)$')
plt.ylabel('$\dot{\phi} (radianes/s)$')

# Añadir grid
plt.grid(True)

# Añadir leyenda
plt.legend()

# Mostrar la gráfica
plt.show()
