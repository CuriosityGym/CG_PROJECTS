#define BLYNK_TEMPLATE_ID "TMPL3pg6USCZk"   // Template ID for Blynk
#define BLYNK_TEMPLATE_NAME "Fire Alert"    // Name of the Blynk template
#define BLYNK_AUTH_TOKEN "b4z-zlnSkcfbUD5fQxJvqKJKvoFQkUXG" // Authentication token for Blynk

#define BLYNK_PRINT Serial   // Enables serial output for debugging
#include <ESP8266WiFi.h>     // Includes the ESP8266 WiFi library
#include <BlynkSimpleEsp8266.h>  // Includes the Blynk library for ESP8266

// Auth token for Blynk, required to connect to the Blynk cloud
char auth[] = BLYNK_AUTH_TOKEN;

// Replace these with your Wi-Fi credentials
char ssid[] = "******";  // Enter your Wi-Fi SSID (network name)
char pass[] = "*********";  // Enter your Wi-Fi password

BlynkTimer timer;  // Blynk timer object to run tasks periodically
int flag = 0;  // Flag to prevent multiple alerts

int flameSensorPin = D1;  // Pin connected to the flame sensor

// Function to read sensor data and send alert if necessary
void sendSensor() { 
  int flameDetected = digitalRead(flameSensorPin);  // Read the state of the flame sensor

  if (flameDetected == LOW && flag == 0) {  // Flame detected (assuming LOW signal for detection)
    Serial.println("Fire in the House");  // Print alert message to serial monitor
    Blynk.logEvent("fire_alert", "Fire Detected by Flame Sensor");  // Log the event on Blynk app
    flag = 1;  // Set the flag to prevent multiple alerts
  }
  else if (flameDetected == HIGH) {  // If the flame is no longer detected
    flag = 0;  // Reset the flag
  }
}

// Setup function, runs once when the device is powered on
void setup() {
  pinMode(flameSensorPin, INPUT);  // Set the flame sensor pin as input

  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  Blynk.begin(auth, ssid, pass);  // Connect to Blynk cloud using Wi-Fi credentials
  timer.setInterval(5000L, sendSensor);  // Set the timer to run sendSensor function every 5 seconds
}

// Main loop function, runs continuously
void loop() {
  Blynk.run();  // Run Blynk process to keep the connection alive
  timer.run();  // Run the timer to check sensor data periodically
}
