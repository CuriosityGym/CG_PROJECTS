#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>        // For BMP180 Barometric Sensor
#include <DHT.h>                    // For DHT11 Temperature & Humidity Sensor
#include <ACROBOTIC_SSD1306.h>      // ACROBOTIC library for OLED

// DHT11 Sensor
#define DHTPIN D4                   // DHT11 sensor pin
#define DHTTYPE DHT11               // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// BMP180 Sensor
Adafruit_BMP085 bmp;

// MQ135 Air Quality Sensor
const int mq135Pin = A0;            // MQ135 analog pin

// Function to determine air quality status based on AQI
String getAirQualityStatus(float aqi) {
  if (aqi <= 50) {
    return "Good";
  } else if (aqi <= 100) {
    return "Satisfactory";
  } else if (aqi <= 200) {
    return "Moderate";
  } else if (aqi <= 300) {
    return "Poor";
  } else if (aqi <= 400) {
    return "Very Poor";
  } else {
    return "Severe";
  }
}

void setup() {
  // Start serial communication
  Serial.begin(115200);
initProperties();
 ArduinoCloud.begin(ArduinoIoTPreferredConnection);
setDebugMessageLevel(2);
 ArduinoCloud.printDebugInfo();

  // Initialize OLED display
   oled.init();
   oled.clearDisplay();

  // Initialize DHT11 sensor
  dht.begin();

  // Initialize BMP180 sensor
  if (!bmp.begin()) {
    Serial.println("BMP180 sensor not found!");
    while (1);
  }

}

void loop() {
  ArduinoCloud.update(); 
  // Reading from DHT11 sensor
  int humidity = dht.readHumidity();
  humidityvalue = humidity;
  int temperature = dht.readTemperature();
  temperaturevalue=temperature;

  // Reading from BMP180 sensor
  int pressure = bmp.readPressure();
  pressurevalue = pressure;
  int altitude = bmp.readAltitude();
altitudevalue =altitude;
  // Reading from MQ135 Air Quality Sensor
  int airQuality = analogRead(mq135Pin);
  
  // Convert raw sensor value to approximate AQI
  int aqi = map(airQuality, 0, 1023, 0, 500); // Map raw value to AQI scale (0-500)
  airQualityValue = aqi;
  String airQualityStatus = getAirQualityStatus(aqi);
//airQualityStatus1 = airQualityStatus;
  // Output sensor readings to Serial Monitor
  Serial.println("------ Environmental Monitoring Data ------");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Pressure: "); Serial.print(pressure / 100); Serial.println(" hPa");
  Serial.print("Altitude: "); Serial.print(altitude); Serial.println(" meters");
  Serial.print("Air Quality (AQI): "); Serial.println(aqi);
  Serial.print("Air Quality Status: "); Serial.println(airQualityStatus);
  Serial.println("------------------------------------------");

  // Display sensor data on OLED using ACROBOTIC library
   oled.clearDisplay();
   oled.setTextXY(0, 0);  
   oled.putString(" Temp: ");  oled.putString(String(temperature).c_str());  oled.putString(" C"); //String(myBPM).c_str()
   oled.setTextXY(1, 0);
   oled.putString(" Humidity: ");  oled.putString(String(humidity).c_str());  oled.putString(" %");
   oled.setTextXY(2, 0);
   //oled.putString(" Pressure: ");  oled.putString (String(pressure / 100).c_str());  oled.putString(" hPa");
   oled.setTextXY(3, 0);
   oled.putString(" Altitude: ");  oled.putString(String(altitude).c_str());  oled.putString(" m");
   oled.setTextXY(4, 0);
   oled.putString(" AQI: ");  oled.putString(String(aqi).c_str());
   oled.setTextXY(5, 0);
   oled.putString(" Status: "); 
     oled.setTextXY(6, 0);
   oled.putString("      ");   oled.putString(String(airQualityStatus).c_str());
  delay(5000); // Wait 5 seconds before the next reading
}

// You can also include WiFi code here for sending data to a server
