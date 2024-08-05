#include "thingProperties.h"
#include "DHT.h"
#define DHTpin 12                  //D6 on the nodemcu ESP8266
#define DHTTYPE DHT11
DHT dht(DHTpin,DHTTYPE);


void setup() {
  
  Serial.begin(9600);   // Initialize serial and wait for port to open
  delay(1500);           // This delay gives the chance to wait for a Serial Monitor            without blocking if none is found


 initProperties();    // Defined in thingProperties.h

 ArduinoCloud.begin(ArduinoIoTPreferredConnection);    // Connect to Arduino IoT   Cloud

setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  dht_sensor_getdata();
}

void onHumidityChange() {
  // Do something

}

void onMsgChange() {
  // Do something
}
 
void dht_sensor_getdata()
  {
    float hm= dht.readHumidity();
    Serial.print("Humidity ");
    Serial.println(hm);
    float temp=dht.readTemperature();
      Serial.print("Temperature ");
    Serial.println(temp);
    humidity=hm;
    temperature=temp;
    msg="Temperature = " + String (temperature)+"  Humidity = " + String(humidity);
  }
