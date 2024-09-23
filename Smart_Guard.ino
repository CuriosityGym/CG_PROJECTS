#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "https://smartguard-c5c40-default-rtdb.firebaseio.com/"  // Your Firebase Project URL
#define FIREBASE_AUTH "uqjBZv63fRbaqH5T2TKqfkjrOoQEGnU1VF2JqobG"  // Firebase Database Secret

// WiFi credentials
#define WIFI_SSID "XXXXXX" //enter your hotspot name here
#define WIFI_PASSWORD "XXXXXXX" // enter hotspot password here

const int irPin = D1;      // IR sensor pin
const int touchPin = D2;   // Touch sensor pin
const int buzzerPin = D6;  // Buzzer pin
const int ledPin = D5;     // LED pin

FirebaseData firebaseData; // Create a FirebaseData object
bool alarmTriggered = false; // Flag to track if the alarm was triggered
bool touchActive = false;    // Flag to track if the touch sensor should be active
bool manualReset = false;    // Flag to manually turn off the LED
unsigned long triggerTime = 0; // Variable to track when the alarm was triggered
const unsigned long resetDelay = 10000; // 10 seconds in milliseconds

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
    Serial.println("Thief detected! LED turned ON, touch sensor activated.");
    digitalWrite(ledPin, HIGH); // Turn on LED
    alarmTriggered = true;      // Set flag to prevent multiple detections
    touchActive = true;         // Enable the touch sensor after thief detection
    triggerTime = millis();     // Record the time when the alarm was triggered

    // Update Firebase when thief is detected
    if (Firebase.setInt(firebaseData, "/alert", 1)) {
      Serial.println("Firebase updated: alert=1");
    } else {
      Serial.print("Failed to update Firebase: alert=1. Error: ");
      Serial.println(firebaseData.errorReason());
    }
  }

  // Check if the touch sensor is active and detects a touch
  if (touchActive) {
    int touchSensorState = digitalRead(touchPin);
    if (touchSensorState == HIGH) {
      Serial.println("Object touched! Buzzer turned ON.");
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
    } else {
      digitalWrite(buzzerPin, LOW);   // Turn off the buzzer when no touch is detected
    }
  }

  // Check if the time since alarm was triggered exceeds 3000 seconds (resetDelay)
  if (alarmTriggered && millis() - triggerTime >= resetDelay) {
    Serial.println("3000 seconds elapsed: Resetting system and turning off LED.");
    resetSystem(); // Call the function to reset the system and Firebase
  }

  delay(500); // Small delay to avoid flooding the loop
}

// Function to manually reset the system, e.g., through a button press or a remote command.
void manualTurnOff() {
  manualReset = true;  // Set the manual reset flag to true, allowing for the system to reset in the loop
}

// Function to reset the system and update Firebase alert to 0
void resetSystem() {
  digitalWrite(ledPin, LOW);   // Turn off LED
  alarmTriggered = false;      // Reset alarm flag
  touchActive = false;         // Deactivate touch sensor
  manualReset = false;         // Reset manual flag

  // Reset Firebase alert
  if (Firebase.setInt(firebaseData, "/alert", 0)) {
    Serial.println("Firebase updated: alert=0");
  } else {
    Serial.print("Failed to update Firebase: alert=0. Error: ");
    Serial.println(firebaseData.errorReason());
  }

  Serial.println("System reset complete.");
}
