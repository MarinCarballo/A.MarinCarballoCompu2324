import matplotlib.pyplot as plt

# Datos proporcionados
temperatures = [1, 2, 3, 4, 5]
densidad_up = [0.710219, 0.684500, 0.598031, 0.469094, 0.500500]
densidad_down = [0.289781, 0.315500, 0.401969, 0.530906, 0.499500]

# Calcular la suma de Densidad Up y Densidad Down
densidad_sum = [up + down for up, down in zip(densidad_up, densidad_down)]

# Crear la gráfica
plt.figure(figsize=(10, 6))
plt.plot(temperatures, densidad_up, label='Densidad s=+1', marker='o')
plt.plot(temperatures, densidad_down, label='Densidad s=-1', marker='o')
plt.plot(temperatures, densidad_sum, label='Densidad Total', marker='o', linestyle='--')

# Añadir etiquetas y título
plt.xlabel('T (K)')
plt.ylabel('Densidad')
plt.title('Densidad frente a temperatura. N=32')
plt.legend()
plt.grid(True)
plt.show()
