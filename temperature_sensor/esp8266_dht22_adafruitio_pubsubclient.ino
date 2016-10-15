/***************************************************
  Adafruit ESP8266 Sensor Module
  
  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino
  Works great with Adafruit's Huzzah ESP board:
  ----> https://www.adafruit.com/product/2471
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

// Libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// DHT 22 sensor
#define DHTPIN 2
#define DHTTYPE DHT22 

// WiFi parameters
#define WLAN_SSID       "<your_ssid>"
#define WLAN_PASS       "<your_pass"

// Adafruit IO
#define AIO_USERNAME    "<adafruit_username>"
#define AIO_KEY         "<adafruit_aio_key>"
#define TEMP_FEED_PATH  "<username>/feeds/temperature"
#define HUMIDITY_FEED_PATH "<username>/feeds/humidity"

// LEDs
#define BLUE_LED 4
#define GREEN_LED 5

// DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// Functions
void connect();

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClientSecure client;
PubSubClient mqttclient(client);


/*************************** Sketch Code ************************************/
void callback (char* topic, byte* payload, unsigned int length) {
  Serial.println(topic);
  Serial.write(payload, length);
  Serial.println("");
}

void setup() {

  // initialize led pins
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Init sensor
  dht.begin();

  Serial.begin(115200);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  digitalWrite(BLUE_LED, HIGH);
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
  delay(3000);

  // connect to adafruit io
  mqttclient.setServer("io.adafruit.com", 8883);
  mqttclient.setCallback(callback);  
  connect();

}

void loop() {

  Serial.println(F("check connection"));
  if (!mqttclient.connected()) {
    connect();
  }

  Serial.println(F("get data\n"));
  // Grab the current state of the sensor
  float humidity_data = dht.readHumidity();
  float temperature_data = dht.readTemperature(true);

  // Publish data
  mqttclient.publish(TEMP_FEED_PATH, String(temperature_data).c_str(), true);
  Serial.print("Temperature published: ");
  Serial.print(temperature_data);
  mqttclient.publish(HUMIDITY_FEED_PATH, String(humidity_data).c_str(), true);
  Serial.print("\nHumidity published: ");
  Serial.print(humidity_data);
  

  // Repeat every 20 seconds
  mqttclient.loop();
  delay(20000);

}

// connect to adafruit io via MQTT
void connect() {

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    delay(3000);
  }
  Serial.print(F("Connecting to Adafruit IO... "));
  while(!mqttclient.connected()) {
    if (mqttclient.connect("ESP8266Client", AIO_USERNAME, AIO_KEY)) {
      Serial.println(F("Adafruit IO Connected!"));  
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(BLUE_LED, LOW);
    } else {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      Serial.print(F("Adafruit IO connection failed! rc="));
      Serial.print(mqttclient.state());
      Serial.println("try again in 10 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }

}
