#define BLYNK_TEMPLATE_ID "TMPL3MgR_xQ7K"
#define BLYNK_TEMPLATE_NAME "fire alarm"
#define BLYNK_AUTH_TOKEN "qQ9u4Z9lL5TLqRKE-QS82xhA5EU-iK_d"

#define BLYNK_PRINT Serial   // Enables serial output for debugging
#include <ESP8266WiFi.h>     // Includes the ESP8266 WiFi library
#include <BlynkSimpleEsp8266.h>  // Includes the Blynk library for ESP8266

char auth[] = BLYNK_AUTH_TOKEN;  // Auth token for Blynk, required to connect to the Blynk cloud

// Replace these with your Wi-Fi credentials
char ssid[] = "tks12345";  // Enter your Wi-Fi SSID (network name)
char pass[] = "12345678";  // Enter your Wi-Fi password

BlynkTimer timer;  // Blynk timer object to run tasks periodically
int flag = 0;  // Flag to prevent multiple alerts
int flameSensorPin = D2;  // Pin connected to the flame sensor
int buzzerPin = D1;       // Pin connected to the buzzer
int pumpPin = D7;         // Pin connected to the water pump

// Function to read sensor data and send alert if necessary
void sendSensor() { 
  int flameDetected = digitalRead(flameSensorPin);  // Read the state of the flame sensor

  if (flameDetected == LOW && flag == 0) {  // Flame detected (assuming LOW signal for detection)
    Serial.println("Fire in the House");  // Print alert message to serial monitor
    Blynk.logEvent("fire_alert", "Fire Detected by Flame Sensor");  // Log the event on Blynk app
    
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
    digitalWrite(pumpPin, HIGH);    // Turn on the water pump
    delay(1000);                    // Keep the buzzer and pump on for 1 second
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer

    flag = 1;  // Set the flag to prevent multiple alerts
  }
  else if (flameDetected == HIGH) {  // If the flame is no longer detected
    flag = 0;  // Reset the flag
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
    digitalWrite(pumpPin, LOW);    // Turn off the water pump
  }
}

// Setup function, runs once when the device is powered on
void setup() {
  pinMode(flameSensorPin, INPUT);  // Set the flame sensor pin as input
  pinMode(buzzerPin, OUTPUT);      // Set the buzzer pin as output
  pinMode(pumpPin, OUTPUT);        // Set the water pump pin as output
  digitalWrite(buzzerPin, LOW);    // Ensure the buzzer is off at startup
  digitalWrite(pumpPin, LOW);      // Ensure the pump is off at startup

  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  Blynk.begin(auth, ssid, pass);  // Connect to Blynk cloud using Wi-Fi credentials
  timer.setInterval(1000L, sendSensor);  // Set the timer to run sendSensor function every second
}

// Main loop function, runs continuously
void loop() {
  Blynk.run();  // Run Blynk process to keep the connection alive
  timer.run();  // Run the timer to check sensor data periodically
}
