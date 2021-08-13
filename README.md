# DHT22_ESP32_WIFI_MQTT
Mesure de température et d'humidité avec sonde DHT22, envoi des donnees par wifi avec un ESP32 sur MQTT
- Le code mqtt_esp1_M00.ino doit etre charge dans un module ESP32.
  Je l'utilise sur des modules ESP32 DEV KIT WROOM.
- Le réseau wifi est généré par un raspberry Pi exécutant le programme RaspAp. 
  Pour l'installation de RaspAp voir https://www.framboise314.fr/raspap-creez-votre-hotspot-wifi-avec-un-raspberry-pi-de-facon-express/
- Un broker mqtt doit etre installé et executé sur un ordinateur en reseau. J'utilise mosquitto sur un raspberry Pi.
- Le code flows.json doit etre importé dans NODE RED sur un ordinateur en reseau. 
  Les adresses IP doivent etre adaptées ainsi que le chemin d'accès au fichier csv de sauvegarde des données.
  Ce code est écrit pour la réception de données de 2 sondes DHT22 cablées sur 2 ESP32: esp1 et esp2.

