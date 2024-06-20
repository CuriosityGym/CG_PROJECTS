#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "https://smartparking-da8df-default-rtdb.firebaseio.com/"  // Your Firebase Project URL goes here with "https:"
#define FIREBASE_AUTH "t8Y8FO4nbQcWjuyPRou0uRY61V9ktkKbGaH35YjQ"  // Your Firebase Database Secret goes here

#define WIFI_SSID "Curiosity Gym"  // Your WiFi SSID (Hotspot Name) for which your NodeMCU connects 
#define WIFI_PASSWORD "robotics4321"  // Password of your wifi network 

#define irPin1 D1  // D1
#define irPin2 D2  // D2
#define irPin3 D6  // D3
#define irPin4 D7  // D4

FirebaseData firebaseData;  // Create a Firebase Data object

void setup() 
{
  Serial.begin(115200);  // Select the same baud rate if you want to see the data on Serial Monitor
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(irPin3, INPUT);
  pinMode(irPin4, INPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);  // Enable auto reconnect WiFi
}

void loop() 
{
  // IR Sensor 1
  int sensor1 = digitalRead(irPin1);
  if (sensor1 == LOW)  // Assuming LOW means object detected
  {
    if (Firebase.setInt(firebaseData, "/U1", 1)) {
      Serial.println("U1 = 1");
    } else {
      Serial.println("Failed to set U1 value");
      Serial.println(firebaseData.errorReason());
    }
  }
  else
  {
    if (Firebase.setInt(firebaseData, "/U1", 0)) {
      Serial.println("U1 = 0");
    } else {
      Serial.println("Failed to set U1 value");
      Serial.println(firebaseData.errorReason());
    }
  }
  
  // IR Sensor 2
  int sensor2 = digitalRead(irPin2);
  if (sensor2 == LOW)  // Assuming LOW means object detected
  {
    if (Firebase.setInt(firebaseData, "/U2", 1)) {
      Serial.println("U2 = 1");
    } else {
      Serial.println("Failed to set U2 value");
      Serial.println(firebaseData.errorReason());
    }
  }
  else
  {
    if (Firebase.setInt(firebaseData, "/U2", 0)) {
      Serial.println("U2 = 0");
    } else {
      Serial.println("Failed to set U2 value");
      Serial.println(firebaseData.errorReason());
    }
  }
  
  // IR Sensor 3
  int sensor3 = digitalRead(irPin3);
  if (sensor3 == LOW)  // Assuming LOW means object detected
  {
    if (Firebase.setInt(firebaseData, "/U3", 1)) {
      Serial.println("U3 = 1");
    } else {
      Serial.println("Failed to set U3 value");
      Serial.println(firebaseData.errorReason());
    }
  }
  else
  {
    if (Firebase.setInt(firebaseData, "/U3", 0)) {
      Serial.println("U3 = 0");
    } else {
      Serial.println("Failed to set U3 value");
      Serial.println(firebaseData.errorReason());
    }
  }
  
  // IR Sensor 4
  int sensor4 = digitalRead(irPin4);
  if (sensor4 == LOW)  // Assuming LOW means object detected
  {
    if (Firebase.setInt(firebaseData, "/U4", 1)) {
      Serial.println("U4 = 1");
    } else {
      Serial.println("Failed to set U4 value");
      Serial.println(firebaseData.errorReason());
    }
  }
  else
  {
    if (Firebase.setInt(firebaseData, "/U4", 0)) {
      Serial.println("U4 = 0");
    } else {
      Serial.println("Failed to set U4 value");
      Serial.println(firebaseData.errorReason());
    }
  }

  delay(1000);  // Add a delay to avoid rapid Firebase updates
}
