
//Change Blynk Authenticaation Details
#define BLYNK_TEMPLATE_ID "ABPLmPQCdrMg"
#define BLYNK_DEVICE_NAME "Gas Detection Alert"
#define BLYNK_AUTH_TOKEN "fRiTEoa3v1QV9UDShh4gtfgbs34oM81i"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Wifi Name";  // Enter your wifi name
char pass[] = "Wifi Password";  // Enter your wifi password
int smoke = A0;
int data = 0;
int sensorThres = 100;


BlynkTimer timer;

void sendSensor(){
 
 int data = analogRead(smoke);
 Blynk.virtualWrite(V0, data);
  Serial.print("Pin A0: ");
  Serial.println(data);


  if(data > 999)     // Change the Trashold value
  {
    Blynk.email("test@gmail.com", "Alert", "Gas Leakage Detected!");
    Blynk.logEvent("gas_alert","Gas Leakage Detected");
  }
}

void setup(){
  pinMode(smoke, INPUT);
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  //dht.begin();
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
