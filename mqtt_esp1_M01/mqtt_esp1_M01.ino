/*
 ---------------------------------------------
 programme provenant des exemples de arduino ie
 pour la sonde nommee esp1 dans cette application.
 programme pour une carte esp32 dev kit
 ---------------------------------------------
 
 Basic ESP32 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP32 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outESP1" every two seconds
  - publishes the temperature measured by the DHT22 sensor to the topic "esp1/t1" every two seconds
  - publishes the HR% measured by the DHT22 sensor to the topic "esp1/h1" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h> // Librairie des capteurs DHT

// Update these with values suitable for your network.
const int LED=2;

const char* ssid = "raspi-webgui";  // adresse wifi
const char* password = "********";  // mot de passage du reseau wifi
const char* mqtt_server = "10.3.141.1";  //adresse du serveur mqtt

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(LED, LOW);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP1Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello from ESP1");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  dht.begin();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

 

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello from ESP1", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outESP1", msg);
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print(" | Humidite : ");
    Serial.println(h);
    client.publish("esp1/t1", String(t).c_str());
    client.publish("esp1/h1", String(h).c_str());
  }
}
