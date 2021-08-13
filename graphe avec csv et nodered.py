# -*- coding: utf-8 -*-

# graphe avec csv.py
''' Programme pour la représentation graphique des températures et humidite
    en fonction du temps.
'''

import matplotlib.pyplot as plt  # Importation du module pour tracer le graphe
import pandas as pd              # Importation du module pour la lecture du fichier csv

plt.style.use('seaborn')         # Utilisation d'une grille pour le graphe

data = pd.read_csv('alex.csv')
temps = pd.to_datetime(data['t'])  # Transformation du temps en datatime
t_ext = data['esp2/t2']  # sonde 1W
t_int = data['esp1/t1']  # sonde 1W
h1 = data['esp1/h1']     # humidite sonde dht22
h2 = data['esp2/h2']
plt.ylim(-5, 100)
plt.plot_date(temps, t_ext, 'b.-')  # Courbe de température extérieure

plt.plot_date(temps, t_int, 'r.-')  # Courbe de température intérieure

plt.plot_date(temps, h1, 'r.-')      # humidite sonde dht22
plt.plot_date(temps, h2, 'b.-')

plt.title('Représentation des températures et humidités en fonction du temps')
plt.ylabel('Températures [°C] - Humidités [%HR]')
plt.xlabel('Temps')

plt.tight_layout()
plt.show()

