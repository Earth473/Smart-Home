#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6ph36scG9"
#define BLYNK_TEMPLATE_NAME "New Template"
#define BLYNK_AUTH_TOKEN "GjAGwJFu-2KPFBth2D_mf_7I-ayvpXoZ"

#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define MQPIN 35
#define PIRPIN 15
#define LIGHTPIN 34
#define SOILPIN 32
#define RAINPIN 33

DHT dht(DHTPIN, DHTTYPE);

char auth[] = "GjAGwJFu-2KPFBth2D_mf_7I-ayvpXoZ";
char ssid[] = "";
char pass[] = "";

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(PIRPIN, INPUT);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *c");
    Blynk.virtualWrite(V1, h);
    Blynk.virtualWrite(V2, t);
  }
  int lightValue = analogRead(LIGHTPIN);
  Serial.print("Light Sensor Value: ");
  Serial.println(lightValue);
  Blynk.virtualWrite(V3, lightValue);

  int mqValue = analogRead(MQPIN);
  Serial.print("MQ Sensor Value: ");
  Serial.println(mqValue);
  Blynk.virtualWrite(V4, mqValue);

  int rainValue = analogRead(RAINPIN);
  Serial.print("Raindrop Sensor Value: ");
  Serial.println(rainValue);

  int pirValue = digitalRead(PIRPIN);
  String pirStatus = (pirValue == HIGH) ? "Motion detected" : "No motion";

  String combinedData = " %\n" + "Raindrop: " + String(rainValue) + "\n" + "PIR: " + pirStatus;
  Blynk.virtualWrite(V5, combinedData);
  delay(2000);
}