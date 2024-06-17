#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 0  // GPIO0
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         
#include <EEPROM.h>
int sensorPin = D0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int Buzzer = 14; 
String IFTTT_KEY = "mJXR6NpdwgCGNDss5W46MxzxkhwYhzddiJdTeF9gfX-"; //replace this with your IFTTT applet key
int a=0;
const char* eventName  = "CarWarning";
//const char* IFTTT_URL = "maker.ifttt.com";
const char* host = "maker.ifttt.com";
const char* ssid     = "DT_LAB";  // WiFi User Name
const char* password = "fthu@050318";  //WiFi Passwords
Adafruit_SSD1306 OLED(OLED_RESET);

const int buttonPin = D3;
int i=0,m=0;
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0,j=0,h=0,Currenttime,fun=0;
unsigned long debounceDelay = 50;
int firsttime = 1;
unsigned long startTime;
unsigned long pressTime;
int count = 0;
float Time;
int x = 0, y = 0, z = 0;
const char* door_state = "closed";
void setup() {
  pinMode(Buzzer,OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
    sensorValue = !(digitalRead(sensorPin)); //PUC
  //Serial.println(sensorValue);

  if (sensorValue ==HIGH && m==0){
      OLED.begin();
      OLED.clearDisplay();
      OLED.setTextSize(1);
      OLED.setTextColor(WHITE);
      OLED.setCursor(0, 0);
      OLED.println("Noise check");
      OLED.display();
      if (fun==fun){
      Currenttime=millis();
      fun=(!fun);
      m=1;
      }
  }

  if(sensorValue ==LOW){
    
    m=0;
    }
    
   if ((millis()- Currenttime) >= 9000){
      OLED.begin();
      OLED.clearDisplay();
      OLED.setTextSize(1);
      OLED.setTextColor(WHITE);
      OLED.setCursor(0, 0);
      OLED.println("");
      OLED.display();
      fun=fun;
  }
      
  if(i==1 && (millis()-j) >5000){
      OLED.begin();
      OLED.clearDisplay();
      OLED.setTextSize(1);
      OLED.setTextColor(WHITE);
      OLED.setCursor(0, 0);
      OLED.println("");
      OLED.display();
        i=0;
    }
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
    
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        digitalWrite(Buzzer,HIGH);// add
        a += 1;
      }
    }
  }
  lastButtonState = reading;




  if (digitalRead(buttonPin) == LOW) {
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
      z += 1;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 1) {
      Time = pressTime / 1000.0;
      Serial.println(Time);


    }
  }
  else if (firsttime == 0) {
    if (Time >= 2.0)
    {
      count += 1;
      if (count > 5) {
        Serial.println("Warning !!!!! Don't press Horn beyond 2 secs");
        OLED.begin();
        OLED.clearDisplay();
        OLED.setTextSize(1);
        OLED.setTextColor(WHITE);
        OLED.setCursor(0, 0);
        OLED.println("Decrease Honk Time");
        OLED.display();
        delay(500);
        j=millis();
        i=1;
        x += 1;
        count = 0;
      }
    }
    if (x > 2) {
      Serial.println("URL");
       Serial.print("connecting to ");
          Serial.println(host);
          
          WiFiClient client;
          const int httpPort = 80;
          if (!client.connect(host, httpPort)) {
            Serial.println("connection failed");
            return;
          }
    
          String url = "/trigger/CarWarning/with/key/";
          url += IFTTT_KEY;
          
          Serial.print("Requesting URL: ");
          Serial.println(url);
          client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                       "Host: " + host + "\r\n" + 
                       "Content-Type: application/x-www-form-urlencoded\r\n" + 
                       "Content-Length: 13\r\n\r\n" +
                       "value1=" + door_state + "\r\n");
      fine();
      x = 0;
    }
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(count);
    Serial.print("\t");
    Serial.print("\t");
    Serial.println(a);
    if (a > 10) {
      Serial.println("Warning !!!!! You have excedded your honking limit");
      delay(200);
          OLED.begin();
          OLED.clearDisplay();
          OLED.setTextSize(1);
          OLED.setTextColor(WHITE);
          OLED.setCursor(0,5);
          OLED.println("Decrease Honking");
          delay(500);
          OLED.display();
          j=millis();
          i=1;
      y += 1;
      a = 0;
    }
    if (y > 2) {
      Serial.println("URL");
       Serial.println("URL");
       Serial.print("connecting to ");
          Serial.println(host);
          
          WiFiClient client;
          const int httpPort = 80;
          if (!client.connect(host, httpPort)) {
            Serial.println("connection failed");
            return;
          }
    
          String url = "/trigger/CarWarning/with/key/";
          url += IFTTT_KEY;
          
          Serial.print("Requesting URL: ");
          Serial.println(url);
          client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                       "Host: " + host + "\r\n" + 
                       "Content-Type: application/x-www-form-urlencoded\r\n" + 
                       "Content-Length: 13\r\n\r\n" +
                       "value1=" + door_state + "\r\n");
      //wifi();
      fine();
      y = 0;
    }
    firsttime = 1;

  }

}

void fine(){
          OLED.begin();
          OLED.clearDisplay();
          OLED.setTextSize(1);
          OLED.setTextColor(WHITE);
          OLED.setCursor(0,5);
          OLED.println("You are fined");
          OLED.display();
          delay(500);
          j=millis();
          i=1;
  }
/*
void wifi(){
  // Define the WiFi Client
       WiFiClient client;
       // Set the http Port
       const int httpPort = 80;

       // Make sure we can connect
       if (!client.connect(IFTTT_URL, httpPort))
          {
            return;
          }

       // We now create a URI for the request
       // String url = "/trigger/" + String(eventName) + "-"+String(eventCount)+ "/with/key/" + String(IFTTT_KEY);
       String url = "/trigger/" + String(eventName) + "/with/key/" + String(IFTTT_KEY);

       // Set some values for the JSON data depending on which event has been triggered
       IPAddress ip = WiFi.localIP();
       String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
       //String value_1 = "MH 37T 5770";
       //String value_2 = String(h);
       //String value_3 = "";
       


        // Build JSON data string
        String data = "";
        //data = data + "\n" + "{\"value1\":\"" + value_1 + "\"}"; //,"value2\":\""+ value_2 +"\"}";

        // Post the button press to IFTTT
        if (client.connect(IFTTT_URL, httpPort))
           {
              String url = "/trigger/CarWarning/with/key/";
          url += IFTTT_KEY;
          
          Serial.print("Requesting URL: ");
          Serial.println(url);
            client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                       "Host: " + IFTTT_URL + "\r\n" + 
                       "Content-Type: application/x-www-form-urlencoded\r\n" + 
                       "Content-Length: 13\r\n\r\n" +
                       "value1=" + door_state + "\r\n");

          
           }
  }*/
