#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "https://smartguard-c5c40-default-rtdb.firebaseio.com/"  // Your Firebase Project URL
#define FIREBASE_AUTH "uqjBZv63fRbaqH5T2TKqfkjrOoQEGnU1VF2JqobG"  // Firebase Database Secret

// WiFi credentials
#define WIFI_SSID "Curiosity Gym"
#define WIFI_PASSWORD "robotics4321"

const int irPin = D1;      // IR sensor pin
const int touchPin = D2;   // Touch sensor pin
const int buzzerPin = D6;  // Buzzer pin
const int ledPin = D5;     // LED pin

FirebaseData firebaseData; // Create a FirebaseData object
bool alarmTriggered = false; // Flag to track if alarm was triggered

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);  // Auto-reconnect to WiFi
  Serial.println("Firebase initialized.");

  // Initialize sensor and actuator pins
  pinMode(irPin, INPUT);
  pinMode(touchPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Initially turn off buzzer and LED
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.println("System initialized and waiting for detection...");
}

void loop() {
  // Check if thief (IR sensor) is detected
  int irSensorState = digitalRead(irPin);
  if (irSensorState == LOW && !alarmTriggered) {
    Serial.println("Thief detected! LED turned ON.");
    digitalWrite(ledPin, HIGH); // Turn on LED
    alarmTriggered = true; // Set flag to prevent multiple Firebase updates

    // Update Firebase when thief detected
    if (Firebase.setInt(firebaseData, "/alert", 1)) {
      Serial.println("Firebase updated: alert=1");
    } else {
      Serial.print("Failed to update Firebase: alert=1. Error: ");
      Serial.println(firebaseData.errorReason());
    }
  } else if (irSensorState == HIGH && alarmTriggered) {
    // Reset alarm when no thief detected
    Serial.println("Thief gone, resetting alert.");
    digitalWrite(ledPin, LOW); // Turn off LED
    alarmTriggered = false; // Reset flag

    // Reset Firebase alert
    if (Firebase.setInt(firebaseData, "/alert", 0)) {
      Serial.println("Firebase updated: alert=0");
    } else {
      Serial.print("Failed to update Firebase: alert=0. Error: ");
      Serial.println(firebaseData.errorReason());
    }
  }

  // Check for touch sensor
  int touchSensorState = digitalRead(touchPin);
  if (touchSensorState == HIGH && alarmTriggered) {
    Serial.println("Object touched! Buzzer turned ON.");
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off buzzer when no touch detected
  }

  delay(500); // Small delay to avoid flooding the loop
}
