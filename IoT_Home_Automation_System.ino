// Define Blynk template ID, name, and authentication token
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

// Include necessary libraries
#include <ESP8266WiFi.h>             // Library for ESP8266 Wi-Fi functionality
#include <BlynkSimpleEsp8266.h>      // Library for Blynk integration with ESP8266
#include <DHT.h>                     // Library for DHT11 sensor

// Define pin connections for sensors and actuators
#define DHTPIN D4      // Digital pin connected to the DHT11 data pin
#define DHTTYPE DHT11  // Specify that the sensor type is DHT11
#define PIRPIN D2      // Digital pin connected to the PIR motion sensor
#define RELAYPIN D3    // Digital pin connected to the relay module
#define LEDPIN D5      // Digital pin connected to the LED
#define LDRPIN A0      // Analog pin connected to the LDR
#define BUZZER_PIN D6  // Digital pin connected to the buzzer

// Wi-Fi credentials
char auth[] = "";  // Blynk authentication token
char ssid[] = "";  // Your Wi-Fi SSID
char pass[] = "";  // Your Wi-Fi password

// Create an instance of the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendSensorData() {
  // Read humidity value from DHT sensor
  double humidity = dht.readHumidity();
  
  // Read temperature value from DHT sensor (in Celsius)
  double temperature = dht.readTemperature(); 

  // Check if any readings failed (returns 'NaN' if sensor fails)
  if (isnan(humidity) || isnan(temperature)) {
    // Print error message if DHT sensor readings fail
    Serial.println("Failed to read from DHT sensor!");
    return;  // Exit the function if readings are invalid
  }

  // Send the temperature data to Blynk virtual pin V3
  Blynk.virtualWrite(V3, temperature);
  
  // Send the humidity data to Blynk virtual pin V4
  Blynk.virtualWrite(V4, humidity);

  // Print the humidity and temperature values to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}

void setup() {
  Serial.begin(115200);             // Initialize serial communication at 115200 baud
  Blynk.begin(auth, ssid, pass);   // Initialize Blynk with authentication and Wi-Fi credentials

  // Set pin modes
  pinMode(PIRPIN, INPUT);           // Set PIR sensor pin as input
  pinMode(RELAYPIN, OUTPUT);        // Set relay control pin as output
  pinMode(LEDPIN, OUTPUT);          // Set LED pin as output
  pinMode(BUZZER_PIN, OUTPUT);      // Set buzzer pin as output
  dht.begin();                      // Initialize the DHT11 sensor
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();                      // Process Blynk events

  // Read the PIR motion sensor
  int motionDetected = digitalRead(PIRPIN);  // Read the state of the PIR sensor
  Blynk.virtualWrite(V1, motionDetected);   // Send PIR sensor state to Blynk virtual pin V1

  // Read the LDR (Light Dependent Resistor) value
  int ldrValue = analogRead(LDRPIN);  // Read the analog value from LDR
  Blynk.virtualWrite(V2, ldrValue);  // Send LDR value to Blynk virtual pin V2

  if (motionDetected == HIGH) {
    // If motion is detected
    Serial.println("Motion detected!");
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
  } else {
    // If no motion is detected
    digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
  }

  // Control the LED based on LDR value
  if (ldrValue > 800) {  // Adjust the threshold as needed
    digitalWrite(LEDPIN, HIGH);  // Turn on the LED if LDR value is below the threshold
  } else {
    digitalWrite(LEDPIN, LOW);   // Turn off the LED if LDR value is above the threshold
  }

  // Print sensor data to Serial Monitor
  Serial.print("Motion Detected: ");
  Serial.println(motionDetected);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  delay(500);  // Delay for readability and to avoid excessive serial output
  timer.run();
}

// Callback function to handle relay state updates from the Blynk app
BLYNK_WRITE(V5) {
  int relayState = param.asInt();  // Get the state from Blynk virtual pin V5
  if (relayState == 1) {
    digitalWrite(RELAYPIN, HIGH);  // Turn on the relay if the state is 1
    Serial.println("Relay ON - DC Motor ON");
  } else {
    digitalWrite(RELAYPIN, LOW);   // Turn off the relay if the state is not 1
    Serial.println("Relay OFF - DC Motor OFF");
  }
}
