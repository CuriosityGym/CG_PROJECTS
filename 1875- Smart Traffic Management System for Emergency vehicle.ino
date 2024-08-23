#include <SPI.h>
#include <MFRC522.h>

// Define pins for RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// Define pins for LEDs (for a 4-way intersection)
#define RED_LED_1 4
#define YELLOW_LED_1 3
#define GREEN_LED_1 2


bool emergencyDetected = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();

  // Initialize LED pins for all directions
  pinMode(RED_LED_1, OUTPUT);
  pinMode(YELLOW_LED_1, OUTPUT);
  pinMode(GREEN_LED_1, OUTPUT);

}

void loop() {
  // Check for RFID Tag
  if (emergencyDetected){
    Serial.println("Emergency Vehicle Detected via RFID");
    manageTrafficForEmergency();
    rfid.PICC_HaltA();
  }

  // If no emergency is detected, maintain the normal traffic light sequence
  if (!emergencyDetected) {
    normalTrafficLight();
  }
}

void manageTrafficForEmergency() {
  
  stopAllDirections();
  delay(7000); // Red light for 7 seconds to allow emergency vehicle to pass

  // Clear emergency state and return to normal operation
  emergencyDetected = false;
}
void test1(){
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.println("Emergency Vehicle Detected via RFID");
    emergencyDetected = true;
    rfid.PICC_HaltA();
  }
}
void stopAllDirections() {
  // Turn off all green and yellow LEDs, turn on all red LEDs
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(YELLOW_LED_1, LOW);
  digitalWrite(RED_LED_1, HIGH);
}

void normalTrafficLight() {
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(YELLOW_LED_1, LOW);
  digitalWrite(RED_LED_1, HIGH);
  delay(3000);
  test1();
  if (emergencyDetected) return;
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(YELLOW_LED_1, HIGH);
  digitalWrite(RED_LED_1, LOW);
  delay(2000);
  test1();
  if (emergencyDetected) return;
  digitalWrite(GREEN_LED_1, HIGH);
  digitalWrite(YELLOW_LED_1, LOW);
  digitalWrite(RED_LED_1, LOW);
  delay(3000);
  test1();
  if (emergencyDetected) return;

}
