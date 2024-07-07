import matplotlib.pyplot as plt
import numpy as np

# Datos para el primer gráfico
T1 = np.array([1, 2, 3, 4, 5])
densidad_s_plus = np.array([0.7, 0.65, 0.6, 0.45, 0.5])
densidad_s_minus = np.array([0.3, 0.35, 0.4, 0.55, 0.5])
densidad_total = np.array([1, 1, 1, 1, 1])

# Barras de error (valores ficticios para el ejemplo)
error_s_plus = np.array([0.000575, 0.000619,  0.001013, 0.001012, 0.000986])
error_s_minus = np.array([0.000575, 0.000619,  0.001013, 0.001012, 0.000986])

# Crear el primer gráfico con barras de error
plt.figure(figsize=(10, 6))
plt.errorbar(T1, densidad_s_plus, yerr=error_s_plus, fmt='-', linewidth=1, capsize=5, elinewidth=2, label='Densidad s=+1')
plt.errorbar(T1, densidad_s_minus, yerr=error_s_minus, fmt='-', linewidth=1, capsize=5, elinewidth=2, label='Densidad s=-1')
plt.plot(T1, densidad_total, 'go--', label='Densidad Total')
plt.xlabel('T (K)')
plt.ylabel('Densidad')
plt.title('Densidad frente a temperatura. N=32')
plt.legend()
plt.grid(True)

plt.show()
