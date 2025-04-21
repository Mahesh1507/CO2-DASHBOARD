#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials (your mobile hotspot)
const char* ssid = "MAHI";
const char* password = "12345678";

// MQTT Broker settings (YOUR PC's IP)
const char* mqtt_server = "192.168.204.116"; // From your ipconfig
const int mqtt_port = 1883;
const char* mqtt_topic = "co2/sensor";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.println("\nConnecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Verify PC connectivity
  Serial.print("Pinging MQTT server...");
  if (espClient.connect(mqtt_server, mqtt_port)) {
    Serial.println("SUCCESS");
    espClient.stop();
  } else {
    Serial.println("FAILED");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connecting...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.publish("status", "online");
      return;
    }
    
    Serial.print("failed, rc=");
    Serial.println(client.state());
    delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Read sensor value (replace this with your actual sensor reading code)
  int sensorValue = analogRead(34); // Assuming sensor is connected to GPIO34
  // Convert analog reading to PPM (adjust formula based on your sensor)
  float ppm = map(sensorValue, 0, 4095, 300, 2000);
  
  // Publish to MQTT
  char ppmString[8];
  dtostrf(ppm, 1, 2, ppmString);
  client.publish("co2/sensor", ppmString);
  
  delay(1000); // Wait 1 second before next reading
}