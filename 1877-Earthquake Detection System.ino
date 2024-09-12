#include "arduino_secrets.h"
#include "thingProperties.h"

const int buzzerPin = D5;  // Buzzer pin
const int vibrationPin = D6;  // Vibration sensor pin
const int redLedPin = D1;  // Red LED pin
const int blueLedPin = D2;  // Blue LED pin
const int vibrationThreshold = 5;  // Threshold for detecting seismic activity

// Variables for tracking events
bool earthquakeAlert = false;

int vibrationCount = 0;
int vibrationDuration = 0;


void setup() {
  Serial.begin(9600);
  initProperties();
   ArduinoCloud.begin(ArduinoIoTPreferredConnection);
   
   setDebugMessageLevel(2);
   ArduinoCloud.printDebugInfo();
  // Initialize buzzer, LEDs, and vibration sensor
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);  // Turn off buzzer initially
  pinMode(vibrationPin, INPUT);  // Vibration sensor pin

  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  
  digitalWrite(redLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
}

void loop() {
 ArduinoCloud.update();   
  // Read vibration sensor
  int vibration = digitalRead(vibrationPin);
   
  Serial.print("Vibration Sensor: ");
  Serial.println(vibration ? "Vibration Detected" : "No Vibration");


  // Check for building collapse (continuous vibrations)
  if (vibration == HIGH) {
    vibrationCount++;
    Serial.println(vibrationCount);
    if (vibrationCount >= vibrationThreshold) {
    triggerEarthquakeAlert() ;
      
    //collapseAlert1 = collapseAlert;
    }
  } else {
    vibrationCount = 0;  // Reset count if vibration stops
  }

  // delay(500);  // Delay for stability
}

// Function to trigger earthquake alert
void triggerEarthquakeAlert() {
earhquakealert1 = "Earthquake detected!";
  playSiren();  // Start siren
  earthquakeAlert = true;  // Update cloud variable for IFTTT trigger
 Serial.println("Earthquake detected! Alert triggered.");
}


void playSiren() {
  for (int i = 0; i < 20; i++) {  // Repeat the tone 20 times for a longer sound
       
    tone(buzzerPin, 800);  // Lower frequency (800 Hz)
     digitalWrite(redLedPin, HIGH);
    digitalWrite(blueLedPin, LOW);
   
    delay(300);  // Play for 300 milliseconds
    tone(buzzerPin, 1200);  // Higher frequency (1200 Hz)
    digitalWrite(redLedPin, LOW);
    digitalWrite(blueLedPin, HIGH);
   
    delay(300);  // Play for 300 milliseconds
  }
  noTone(buzzerPin);  // Stop the tone after the loop
    digitalWrite(redLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
 

}