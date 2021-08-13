# DHT22_ESP32_WIFI_MQTT
Mesure de température et d'humidité avec sonde DHT22, envoi des donnees par wifi avec un ESP32 sur MQTT
- Le code mqtt_esp1_M01.ino doit etre charge dans un module ESP32.
  Je l'utilise sur des modules ESP32 DEV KIT WROOM.
- Un broker mqtt doit etre installé et executé sur un ordinateur en reseau. J'utilise mosquitto sur un raspberry Pi.
- Le code flows.json doit etre importé dans NODE RED sur un ordinateur en reseau. 
  Les adresses IP doivent etre adaptées ainsi que le chemin d'accès au fichier csv de sauvegarde des données.

