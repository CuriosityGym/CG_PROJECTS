#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN A0
#define RELAY_PIN 3

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Read soil moisture
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);

  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  // Control irrigation based on soil moisture
  if (soilMoistureValue > 700) { // Adjust threshold as necessary
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Irrigation ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Irrigation OFF");
  }

  delay(2000); // Delay between readings
}
