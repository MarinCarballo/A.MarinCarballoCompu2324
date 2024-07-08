import pandas as pd
import matplotlib.pyplot as plt

# Cargar el archivo CSV
file_path = 'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Voluntario2/Péndulo Doble - Optimización.csv'  # Reemplaza con la ruta a tu archivo CSV
data = pd.read_csv(file_path)

# Asumimos que las columnas del archivo CSV están en el siguiente orden:
# 1. Tiempo de simulación de "lm -02 Multithread Ryzen 4700 U"
# 2. Tmax
# 3. Tiempo de simulación de "lm -03 Joel"
# 4. Tiempo de simulación de "lm -03 Singlethread Ryzen 4700 U"
# 5. Tiempo de simulación de "lm -03 Multithread Ryzen 4700 U"

# Asignar cada columna a una variable
t_lm_02_multithread = data.iloc[:, 0]
tmax = data.iloc[:, 1]
t_lm_03_joel = data.iloc[:, 2]
t_lm_03_singlethread = data.iloc[:, 3]
t_lm_03_multithread = data.iloc[:, 4]

# Crear el gráfico
plt.figure(figsize=(10, 6))

plt.plot(tmax, t_lm_02_multithread, label='lm -02 Multithread Ryzen 4700 U')
plt.plot(tmax, t_lm_03_joel, label='lm -03 Joel')
plt.plot(tmax, t_lm_03_singlethread, label='lm -03 Singlethread Ryzen 4700 U')
plt.plot(tmax, t_lm_03_multithread, label='lm -03 Multithread Ryzen 4700 U')

# Configurar etiquetas y título
plt.xlabel('Tmax')
plt.ylabel('Tiempo de Simulación (t)')
plt.title('Tiempo de Simulación vs Tmax, con paso fijo h=0.001')
plt.legend()

# Mostrar el gráfico
plt.grid(True)
plt.show()
