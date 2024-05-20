import pandas as pd
import matplotlib.pyplot as plt

# Crear el DataFrame con los últimos datos proporcionados y calcular la Magnetización total
latest_data_with_total = {
    "T": [1.0, 2.0, 3.0, 4.0, 5.0],
    "Magnetización Superior": [0.102461, 0.110384, 0.026712, 0.148042, 0.148734],
    "Magnetización Inferior": [-0.102461, -0.110384, -0.026712, -0.148042, -0.148734]
}

latest_df_with_total = pd.DataFrame(latest_data_with_total)
latest_df_with_total["Magnetización Total"] = latest_df_with_total["Magnetización Superior"] + latest_df_with_total["Magnetización Inferior"]

# Guardar el DataFrame con la Magnetización Total en un archivo CSV
latest_df_with_total.to_csv('magnetizacion_ultima_con_total.csv', index=False)

# Graficar los datos incluyendo la Magnetización Total
plt.figure(figsize=(10, 6))
plt.plot(latest_df_with_total["T"], latest_df_with_total["Magnetización Superior"], marker='o', label="Magnetización Superior")
plt.plot(latest_df_with_total["T"], latest_df_with_total["Magnetización Inferior"], marker='s', label="Magnetización Inferior")
plt.plot(latest_df_with_total["T"], latest_df_with_total["Magnetización Total"], marker='^', label="Magnetización Total", linestyle='--')

# Configurar el gráfico
plt.xlabel("Temperatura (T)")
plt.ylabel("Magnetización")
plt.title("Magnetización vs Temperatura")
plt.legend(loc='best', fontsize='small')
plt.grid(True)

# Mostrar el gráfico
plt.show()
