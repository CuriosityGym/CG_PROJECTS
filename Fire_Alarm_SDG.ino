#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace with your Wi-Fi credentials
const char* ssid = "your_SSID"; // Your Wi-Fi network SSID
const char* password = "your_PASSWORD"; // Your Wi-Fi network password

// IFTTT settings
const String IFTTT_KEY = "your_IFTTT_KEY"; // Replace with your IFTTT key
const String IFTTT_EVENT = "your_IFTTT_EVENT"; // Replace with your IFTTT event name
const String IFTTT_URL = "https://maker.ifttt.com/trigger/" + IFTTT_EVENT + "/with/key/" + IFTTT_KEY; // IFTTT URL for making the request

// Pin definitions
const int flameSensorPin = D1; // Digital flame sensor connected to D1
const int buzzerPin = D3;      // Buzzer connected to D3
const int ledPin = D4;         // LED connected to D4

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Initialize the flame sensor pin as input
  pinMode(flameSensorPin, INPUT);
  // Initialize the buzzer and LED pins as output
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password); // Start Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) { // Wait until the connection is established
    delay(500); // Wait for 500 milliseconds
    Serial.print("."); // Print a dot to indicate progress
  }
  Serial.println("Connected to WiFi"); // Print a message when connected
}

void loop() {
  int flameValue = digitalRead(flameSensorPin); // Read the flame sensor value

  // Check if flame is detected
  if (flameValue == LOW) { // Digital flame sensors often output LOW when a flame is detected
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    digitalWrite(ledPin, HIGH);    // Turn on the LED
    sendIFTTTNotification();       // Send notification through IFTTT
    delay(5000); // Delay for 5 seconds to avoid continuous notifications
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    digitalWrite(ledPin, LOW);    // Turn off the LED
  }

  delay(1000); // Delay for 1 second before the next check
}

void sendIFTTTNotification() {
  HTTPClient http; // Create an HTTPClient object
  http.begin(IFTTT_URL); // Start the HTTP connection
  int httpCode = http.GET(); // Send the GET request
  
  if (httpCode > 0) { // Check if the request was successful
    String payload = http.getString(); // Get the response payload
    Serial.println("IFTTT Notification Sent: " + payload); // Print the response
  } else {
    Serial.println("Error in IFTTT Notification"); // Print an error message if the request failed
  }
  
  http.end(); // End the HTTP connection
}
