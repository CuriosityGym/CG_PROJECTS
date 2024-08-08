#include <SPI.h>           // Include the SPI library for communication with the RFID module
#include <MFRC522.h>      // Include the MFRC522 library for RFID functionality
#include <Servo.h>        // Include the Servo library for controlling the servo motor

#define SS_PIN 10         // Define the Slave Select (SS)SDA pin for the RFID module
#define RST_PIN 9         // Define the Reset (RST) pin for the RFID module

#define SERVO_PIN 3       // Define the pin for controlling the servo motor
Servo myservo;           // Create a Servo object to control the servo motor

#define ACCESS_DELAY 2000 // Define the delay time (in milliseconds) for successful access
#define DENIED_DELAY 1000 // Define the delay time (in milliseconds) for access denial

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create an MFRC522 instance with the defined SS and RST pins

void setup() 
{
  Serial.begin(9600);    // Start serial communication at a baud rate of 9600
  SPI.begin();           // Initialize the SPI bus for communication with the RFID module
  mfrc522.PCD_Init();    // Initialize the MFRC522 RFID module

  myservo.attach(SERVO_PIN); // Attach the servo motor to the specified pin
  myservo.write(70);        // Set the servo position to 70 degrees (initial position)
  delay(7500);             // Wait for 7.5 seconds
  myservo.write(0);        // Move the servo back to 0 degrees (closed position)
  Serial.println("Put your card to the reader..."); // Prompt user to place card on the reader
  Serial.println();
}

void loop() 
{
  // Check if a new RFID card is present
  if (!mfrc522.PICC_IsNewCardPresent()) 
  {
    return;  // Exit the function if no new card is detected
  }
  
  // Read the serial number (UID) of the detected RFID card
  if (!mfrc522.PICC_ReadCardSerial()) 
  {
    return;  // Exit the function if the card serial number could not be read
  }
  
  // Display the UID of the RFID card on the serial monitor
  Serial.print("UID tag :");
  String content = ""; // Initialize a string to store the UID
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX); // Print each byte of the UID in hexadecimal format
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ")); // Add leading zero if needed
     content.concat(String(mfrc522.uid.uidByte[i], HEX)); // Concatenate each byte to the content string
  }
  
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase(); // Convert the content string to uppercase
  
  // Check if the UID matches the authorized UID
  if (content.substring(1) == "D3 8F D7 97") // Replace with the authorized card UID
  {
    Serial.println("Authorized access"); // Print message for authorized access
    Serial.println();
    myservo.write(70); // Open the door by setting the servo to 70 degrees
    delay(7500);       // Wait for 7.5 seconds
    myservo.write(0); // Close the door by setting the servo back to 0 degrees
  }
  else 
  {
    Serial.println("Access denied"); // Print message for denied access
    delay(DENIED_DELAY); // Wait for the defined denial delay time
  }
}
