import pandas as pd
import matplotlib.pyplot as plt

# Cargar el archivo CSV
file_path = 'C:/Users/anton/OneDrive/Escritorio/A.MarinCarballoCompu2324/A.MarinCarballoCompu2324/Voluntario2/Optimizacion/Optimizacion4.csv'
data = pd.read_csv(file_path)

# Asumimos que las columnas del archivo CSV están en el siguiente orden:
# 1. Tiempo de simulación de "lm -02 Multithread Ryzen 4700 U"
# 2. Tmax
# 3. Tiempo de simulación de "lm -03 Joel"
# 4. Tiempo de simulación de "lm -03 Singlethread Ryzen 4700 U"
# 5. Tiempo de simulación de "lm -03 Multithread Ryzen 4700 U"
# 6. Tiempo de simulación de "Ryzen 4700 U Sin optimizar"
# 7. Tiempo de simulación de "Joel sin optimizar"

# Asignar cada columna a una variable
t_lm_02_multithread = data.iloc[:, 0]
tmax = data.iloc[:, 1]
t_lm_03_joel = data.iloc[:, 2]
t_lm_03_singlethread = data.iloc[:, 3]
t_lm_03_multithread = data.iloc[:, 4]
t_ryzen_no_opt = data.iloc[:, 5]  # Columna para "Ryzen 4700 U Sin optimizar"
t_joel_no_opt = data.iloc[:, 6]   # Nueva columna para "Joel sin optimizar"

# Crear el gráfico
plt.figure(figsize=(10, 6))

plt.plot(tmax, t_lm_02_multithread, label='lm -02 Multithread Ryzen 4700 U')
plt.plot(tmax, t_lm_03_joel, label='lm -03 Joel')
plt.plot(tmax, t_lm_03_singlethread, label='lm -03 Singlethread Ryzen 4700 U')
plt.plot(tmax, t_lm_03_multithread, label='lm -03 Multithread Ryzen 4700 U')
plt.plot(tmax, t_ryzen_no_opt, label='Ryzen 4700 U Sin optimizar')
plt.plot(tmax, t_joel_no_opt, label='Joel sin optimizar')  # Nueva línea para la nueva columna

# Configurar etiquetas y título
plt.xlabel('Tmax')
plt.ylabel('Tiempo de Simulación (t)')
plt.title('Tiempo de Simulación vs Tmax')
plt.legend()

# Mostrar el gráfico
plt.grid(True)
plt.show()
