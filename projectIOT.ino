#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6mn72RaIW"
#define BLYNK_TEMPLATE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "frQU6b-amt7OQdYZYu9_OY5cVUu_AA55"

#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>  // ใช้ไลบรารี Blynk สำหรับ ESP8266

#define DHTPIN 2
#define DHTTYPE DHT22

char auth[] = "frQU6b-amt7OQdYZYu9_OY5cVUu_AA55";
char ssid[] = "Nnn";   // ชื่อ WiFi
char pass[] = "Nuttyss3415";   // รหัส WiFi

int analogPin = A0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  pinMode(analogPin, INPUT);

  Blynk.begin(auth, ssid, pass);   // เริ่มต้น Blynk
}

void loop() {
  Blynk.run();  // ให้ Blynk ทำงาน

  // Wait a few seconds between measurements.
  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F(" C "));
  Serial.print(f);
  Serial.print(F(" F  Heat index: "));
  Serial.print(hic);
  Serial.print(F(" C "));
  Serial.print(hif);
  Serial.println(F(" F"));

  // Soil Moisture Reading
  int val = analogRead(analogPin);
  // Convert soil moisture to percentage
  float moisture_percent = map(val, 1023, 0, 100, 0);
  Serial.print("Soil Moisture: ");
  Serial.print(moisture_percent);
  Serial.println("%");

  // Send data to Blynk
  Blynk.virtualWrite(V1, h);  // ส่งค่าความชื้นไปยัง Widget V1
  Blynk.virtualWrite(V2, t);  // ส่งค่าอุณหภูมิไปยัง Widget V2
  Blynk.virtualWrite(V3, moisture_percent);  // ส่งค่าความชื้นในดินไปยัง Widget V3
}
