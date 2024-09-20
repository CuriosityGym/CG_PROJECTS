#include <Servo.h>
Servo myServo;

int rainSensorPin = A0; // Pin connected to rain sensor
int threshold = 500; // Rain threshold value
int servoPin = 9;
bool rainDetected = false;
unsigned long startTime = 0;
int drainTime = 8000; // Time to let dirty water go to drainage (8 sec for prototype and for actual we should set 5 minutes)

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(rainSensorPin, INPUT);
  myServo.write(0); // Initial position for drainage
}

void loop() {
  int rainValue = analogRead(rainSensorPin);
  Serial.println(rainValue);
  if (rainValue < threshold && !rainDetected) {
    rainDetected = true;
    startTime = millis();
    myServo.write(0); // Keep valve in drainage position
  }
  
  if (rainDetected && millis() - startTime > drainTime) {
    myServo.write(40); // Rotate pipe to direct water to the tank
  }
  
  if (rainValue > threshold) {
    rainDetected = false; // Reset for next rain event
    myServo.write(0); // Return pipe to drainage position
  }
}
