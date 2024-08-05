#include<ThingSpeak.h>    // Include ThingSpeak library

#include <ESP8266WiFi.h> 

int thingspeakResponse = 0;   //Initialize the ThingSpeakResponse variable

int channelID = 0;   //Initialize the ThingSpeak Channel variable

const char* thingspeakAPIKEY="APIKEY";  //Initialize the ThingSpeak APIKEY variable


WiFiClient client;  // Initialize New WifiClient object

const char* wifi_ssid = "WIFI_NAME";   // Wifi Name
const char* wifi_password = "WIFI_PASS"; //Wifi pass

void setup()
{
  thingspeakResponse = 0;
  channelID = 0;

  WiFi.mode(WIFI_STA);                                    // Set the WIfi mode as WIFI_STA

  ThingSpeak.begin(client);                               // Begin the ThingSpeak connect with the client we declared above


  Serial.begin(115200);                                   // Serial Begin

  WiFi.begin(wifi_ssid, wifi_password);                   // Connect to the WiFi using the SSID and Password provided
  int i = 0;

while (WiFi.status() != WL_CONNECTED && i<50) {   //Check Whether WIFI connected
    delay(500);  
    Serial.print(".");
  }
  pinMode(D1, OUTPUT);   // Set the D1 and D2 of Wemos as Output
 
pinMode(D2, OUTPUT);   
 I
f(WiFi.status() != WL_CONNECTED){   //Show the status of wifi connection on On-board LED
  digitalWrite(D1, HIGH);
  delay(3000);
  digitalWrite(D1, LOW);
  }

 if(WiFi.status() == WL_CONNECTED)

{   / /Show the status of wifi connection on On-board LED
   digitalWrite(D2, HIGH);
   delay(3000);
   digitalWrite(D2, LOW);
  }
}


void loop()
{
  channelID = 1312080;   // Set your Channel ID
  thingspeakResponse = (ThingSpeak.writeField(channelID,2,(analogRead(A0)),thingspeakAPIKEY));
// Put a Write Request too your ThingSpeak channel and store the response.
  if (thingspeakResponse == 200) {  // Check if the request was successful
    Serial.println("Updated Successfully"); 
} else {
    Serial.print("Error Updating HTTP Code"); // Print the HTTP Error Code if unsuccessful
    Serial.println(thingspeakResponse);
}
  Serial.print("LDR Value = ");  //Serial print LDR value
  Serial.println((analogRead(A0)));
  analogWrite(D3, (map(analogRead(A0), 0, 900, 0, 1023))); 
 // Map the output of LDR and set the output range from 0-255
  delay(15000);   //Put a delay of 15 seconds.
}
