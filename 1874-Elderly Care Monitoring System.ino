#include "arduino_secrets.h"
#include "thingProperties.h"
//#include <PulseSensorPlayground.h>   // Include the PulseSensorPlayground library
#include <ACROBOTIC_SSD1306.h>       // Include the ACROBOTIC SSD1306 library
#include <Wire.h>
const int PulseSensorPin = A0;       // Pin where the pulse sensor is connected

//PulseSensorPlayground pulseSensor;   // Create an instance of the PulseSensorPlayground object
unsigned long lastBeatTime = 0;
unsigned long interval = 0;
//int myBPM = 0;
bool beatDetected = false;
int threshold = 550;  // Adjust based on your sensor's sensitivity

void setup() {
  Serial.begin(115200); // Begin serial communication at a baud rate of 115200
  initProperties();
   ArduinoCloud.begin(ArduinoIoTPreferredConnection);
   
   setDebugMessageLevel(2);
   ArduinoCloud.printDebugInfo();
  Wire.begin();
  oled.init();                      // Initialize SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0, 0);
  oled.putString("Heart Rate Monitor"); // Display title



}

void loop() {
  ArduinoCloud.update();           // Update the Arduino Cloud connection
 int sensorValue = analogRead(PulseSensorPin);  // Read the analog value from the pulse sensor
//Serial.print("sensorValue ");
      //Serial.println(sensorValue);   // Print the myBPM value to the Serial Monitor
  if (sensorValue > threshold) {  // If the sensor value is above the threshold
    if (!beatDetected) {          // and a beat has not been detected yet
      beatDetected = true;         // mark the beat as detected
      unsigned long currentTime = millis();
      interval = currentTime - lastBeatTime;  // Calculate time since last beat
      lastBeatTime = currentTime;             // Update last beat time

      int BPMvalue  = 60000 / interval;  // Calculate myBPM (60000 ms in a minute)
    
       myBPM = (BPMvalue + 50);
      // Serial.println(BPMvalue); 
      if (myBPM>70){

      Serial.print("Heartbeat detected! BPM: ");
      Serial.println(myBPM);   // Print the myBPM value to the Serial Monitor

      oled.clearDisplay();                // Clear the display
      oled.setTextXY(0, 0);               // Reset cursor to the top-left corner
      oled.putString(" A HeartBeat ");    // Display title
      oled.setTextXY(2, 0);               // Move cursor to the next line
      oled.putString(" Happened ! ");     // Display title
      oled.setTextXY(4, 0);               // Move cursor to the next line
      oled.putString("  myBPM: ");
      oled.putString(String(myBPM).c_str());  // Display myBPM value
    }}
  } else {
    beatDetected = false;  // Reset the beat detection flag when the signal drops below the threshold
      //oled.clearDisplay();                // Clear the display
      oled.setTextXY(0, 0);               // Reset cursor to the top-left corner
      oled.putString(" . "); 
      delay(50);
      //oled.clearDisplay();                // Clear the display
      oled.setTextXY(0, 0);               // Reset cursor to the top-left corner
      oled.putString(" .. "); 
      delay(50);
      //oled.clearDisplay();                // Clear the display
      oled.setTextXY(0, 0);               // Reset cursor to the top-left corner
      oled.putString(" ... "); 
      delay(50);
      //oled.clearDisplay();                // Clear the display
      oled.setTextXY(0, 0);               // Reset cursor to the top-left corner
      oled.putString(" .... "); 
        delay(50);
      //oled.clearDisplay();                // Clear the display
      oled.setTextXY(0, 0);               // Reset cursor to the top-left corner
      oled.putString(" ..... ");
        delay(50);
      //oled.clearDisplay();                // Clear the display
      oled.setTextXY(0, 0);               // Reset cursor to the top-left corner
      oled.putString(" ...... "); 
     delay(50);
     oled.clearDisplay();  
  }

  delay(10);  // Small delay to stabilize readings
}