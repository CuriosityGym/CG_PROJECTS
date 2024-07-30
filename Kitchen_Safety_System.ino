//Kitchen Safety System

int redLed = 12;           // Pin for the red LED
int greenLed = 11;         // Pin for the green LED
int buzzer = 10;           // Pin for the buzzer
int smokeSensorPin = A5;   // Pin for the smoke sensor (analog pin A5)
// Your threshold value
int sensorThreshold = 400; // Threshold value for the smoke sensor

void setup() {
  pinMode(redLed, OUTPUT);       // Set red LED as output
  pinMode(greenLed, OUTPUT);     // Set green LED as output
  pinMode(buzzer, OUTPUT);       // Set buzzer as output
  pinMode(smokeSensorPin, INPUT);// Set smoke sensor pin as input
  Serial.begin(9600);            // Initialize serial communication at 9600 bps
}

void loop() {
  int analogSensorValue = analogRead(smokeSensorPin); // Read the analog value from the smoke sensor

  Serial.print("Pin A5: ");
  Serial.println(analogSensorValue);
  
  // Check if the analog value exceeds the threshold
  if (analogSensorValue > sensorThreshold) {
    digitalWrite(redLed, HIGH);   // Turn on the red LED
    digitalWrite(greenLed, LOW);  // Turn off the green LED
    tone(buzzer, 1000, 200);      // Activate the buzzer with a frequency of 1000 Hz for 200 ms
  } else {
    digitalWrite(redLed, LOW);    // Turn off the red LED
    digitalWrite(greenLed, HIGH); // Turn on the green LED
    noTone(buzzer);               // Deactivate the buzzer
  }
  delay(100); // Wait for 100 ms before the next loop
}
