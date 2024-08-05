#include <ESP8266WiFi.h>     //Including ESP Libraries 

int buttonState;                 // Initialising Button state

const char* wifi_ssid = "DT_LAB";         // Put the WiFi Name
const char* wifi_password = "fthu@050318";            // Put the WiFi Password
WiFiClient client;

const char* host = "maker.ifttt.com";       // Write the host name
const int http_port = 80;                          // Port has to be 80,Transfer of data between Wemos and IFTTT
const char* ifttt_key = "iYihj3KyPFEwyVRuJzEb";  // IFTTT key you will receive from IFTTT applet
const char* event_name = "sos";          // Name of the project which you have mentioned in IFTTT

void setup()
{
  buttonState = 0;    // Push button state

  Serial.begin(115200);   // Serial Monitor baud rate, 

  WiFi.begin(wifi_ssid, wifi_password);
  int i=0;                  //Integer is zero, that means push button is not pressed
  while (WiFi.status() != WL_CONNECTED && i<50) {
    delay(500);
    Serial.print(".");   //Once the Wemos connected with internet wifi it will show on serial monitor
  }
  
pinMode(D1, OUTPUT);    // Red LED Is connected as output
 pinMode(D2, OUTPUT);   //Green LED is connected as output
 if(WiFi.status() != WL_CONNECTED){
  digitalWrite(D1, HIGH);
  delay(3000);
  digitalWrite(D1, LOW);  //If Wemos is not connected with with internet then Red LED will glow for 3 Seconds 
  }
 if(WiFi.status() == WL_CONNECTED){
   digitalWrite(D2, HIGH);
   delay(3000);
   digitalWrite(D2, LOW); //If Wemos is connected with internet then Green LED will glow for 3 Seconds
  }

  pinMode(D8, INPUT);      //Push button is connected at D8 as input
}



void loop()
{
  buttonState = digitalRead(D8);   //It will read the state of the push button
  if (buttonState == 1) {                  // If the state of the push button is 1 (Pressed)
    if (!client.connect(host, http_port)){
       Serial.println("connection failed");   // If event sending failed it will show massage on Serial monitor
       return;
     }
    Serial.print("Triggering Event: ");    // If event sending is done it will show massage on Serial monitor
    Serial.println(event_name);
    client.print(String("POST ") + "/trigger/" +event_name+ "/with/key/" +ifttt_key + " HTTP/1.1\r\n" +
    "Host: " + host +"\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "Content-Length: 13\r\n\r\n" +
    "value1=......\r\n");
    delay(1000);                     //It will trigger the IFTTT event and you will received the Email 

  } }
