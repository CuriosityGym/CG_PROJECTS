#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(D1, D2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#ifdef __AVR__
#include <avr/power.h>                                              // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        2
#define NUMPIXELS 28
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50                                                 // Time (in milliseconds) to pause between pixels

const long utcOffsetInSeconds = 19800;                             // 19800000;   //3600
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

long T;

const char ssid[] = "Nikhil";                     // your network SSID (name)
const char pass[] = "NNK12345";                   // your network password
WiFiClient  client;

//---------Channel Details---------//
unsigned long Channel_ID = 1672831;               // Channel ID
const char * ReadAPIKey = "D4I5XK85BI75TPBZ";     // Read API Key
const char * WriteAPIKey = "BXWD5SWW2X3G5IVS";    // Write API Key
const int FieldNumber1 = 1;                       // The field you wish to read

//int Buzzer = 4;

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.clear();

  //  pinMode(Buzzer, OUTPUT);

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
  for (int i = 0; i < NUMPIXELS; i++)                                 // For each pixel...
  {
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();                                                    // Send the updated pixel colors to the hardware.
    delay(DELAYVAL);                                                  // Pause before next pass through loop
  }
  delay(DELAYVAL);
  for (int i = NUMPIXELS; i >= 0; i--)                                // For each pixel...
  {
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();                                                    // Send the updated pixel colors to the hardware.
    delay(DELAYVAL);                                                  // Pause before next pass through loop
  }
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(29);
}

void loop()
{
  timeClient.update();
  String d = daysOfTheWeek[timeClient.getDay()];
  Serial.println(d);
  int hours = (timeClient.getHours());
  int minutes = timeClient.getMinutes();
  Serial.print("Hours: ");
  Serial.println(hours);
  Serial.print("Mintues: ");
  Serial.println(minutes);
  delay(1000);

  long Data = ThingSpeak.readLongField(Channel_ID, FieldNumber1, ReadAPIKey); // Read data
  Serial.println(Data);

  if (Data == 1 and d == "Monday" )
  {
    Serial.println(Data);
    Serial.println("Time to take Monday Morning pill");
    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(1);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 2 and d == "Monday")
  {
    Serial.println(Data);
    Serial.println("Time to take Monday Afternoon pill");
    pixels.setPixelColor(13, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(2);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 3 and d == "Monday")
  {
    Serial.println(Data);
    Serial.println("Time to take Monday Evening pill");
    pixels.setPixelColor(14, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(3);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 4 and d == "Monday")
  {
    Serial.println(Data);
    Serial.println("Time to take Monday Night pill");
    pixels.setPixelColor(27, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(4);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }

  if (Data == 1 and d == "Tuesday" )
  {
    Serial.println(Data);
    Serial.println("Time to take Tuesday Morning pill");
    pixels.setPixelColor(1, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(5);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 2 and d == "Tuesday")
  {
    Serial.println(Data);
    Serial.println("Time to take Tuesday Afternoon pill");
    pixels.setPixelColor(12, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(6);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 3 and d == "Tuesday")
  {
    Serial.println(Data);
    Serial.println("Time to take Tuesday Evening pill");
    pixels.setPixelColor(15, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(7);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 4 and d == "Tuesday")
  {
    Serial.println(Data);
    Serial.println("Time to take Tuesday Night pill");
    pixels.setPixelColor(26, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(8);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }

  if (Data == 1 and d == "Wednesday" )
  {
    Serial.println(Data);
    Serial.println("Time to take Wednesday Morning pill");
    pixels.setPixelColor(2, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(9);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 2 and d == "Wednesday")
  {
    Serial.println(Data);
    Serial.println("Time to take Wednesday Afternoon pill");
    pixels.setPixelColor(11, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(10);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 3 and d == "Wednesday")
  {
    Serial.println(Data);
    Serial.println("Time to take Wednesday Evening pill");
    pixels.setPixelColor(16, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(11);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 4 and d == "Wednesday")
  {
    Serial.println(Data);
    Serial.println("Time to take Wednesday Night pill");
    pixels.setPixelColor(25, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(12);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }

  if (Data == 1 and d == "Thursday" )
  {
    Serial.println(Data);
    Serial.println("Time to take Thursday Morning pill");
    pixels.setPixelColor(3, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(13);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 2 and d == "Thursday")
  {
    Serial.println(Data);
    Serial.println("Time to take Thursday Afternoon pill");
    pixels.setPixelColor(10, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(14);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 3 and d == "Thursday")
  {
    Serial.println(Data);
    Serial.println("Time to take Thursday Evening pill");
    pixels.setPixelColor(17, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(15);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 4 and d == "Thursday")
  {
    Serial.println(Data);
    Serial.println("Time to take Thursday Night pill");
    pixels.setPixelColor(24, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(16);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }

  if (Data == 1 and d == "Friday" )
  {
    Serial.println(Data);
    Serial.println("Time to take Friday Morning pill");
    pixels.setPixelColor(4, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(17);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 2 and d == "Friday")
  {
    Serial.println(Data);
    Serial.println("Time to take Friday Afternoon pill");
    pixels.setPixelColor(9, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(18);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 3 and d == "Friday")
  {
    Serial.println(Data);
    Serial.println("Time to take Friday Evening pill");
    pixels.setPixelColor(18, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(19);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 4 and d == "Friday")
  {
    Serial.println(Data);
    Serial.println("Time to take Friday Night pill");
    pixels.setPixelColor(23, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(20);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }

  if (Data == 1 and d == "Saturday" )
  {
    Serial.println(Data);
    Serial.println("Time to take Saturday Morning pill");
    pixels.setPixelColor(5, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(21);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 2 and d == "Saturday")
  {
    Serial.println(Data);
    Serial.println("Time to take Saturday Afternoon pill");
    pixels.setPixelColor(8, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(22);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 3 and d == "Saturday")
  {
    Serial.println(Data);
    Serial.println("Time to take Saturday Evening pill");
    pixels.setPixelColor(19, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(23);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 4 and d == "Saturday")
  {
    Serial.println(Data);
    Serial.println("Time to take Saturday Night pill");
    pixels.setPixelColor(22, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(24);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }

  if (Data == 1 and d == "Sunday" )
  {
    Serial.println(Data);
    Serial.println("Time to take Sunday Morning pill");
    pixels.setPixelColor(6, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(25);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 2 and d == "Sunday")
  {
    Serial.println(Data);
    Serial.println("Time to take Sunday Afternoon pill");
    pixels.setPixelColor(7, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(26);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 3 and d == "Sunday")
  {
    Serial.println(Data);
    Serial.println("Time to take Sunday Evening pill");
    pixels.setPixelColor(20, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(27);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  if (Data == 4 and d == "Sunday")
  {
    Serial.println(Data);
    Serial.println("Time to take Sunday Night pill");
    pixels.setPixelColor(21, pixels.Color(0, 150, 0));
    pixels.show();
    myDFPlayer.play(28);
    delay(3000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    //    digitalWrite(Buzzer, HIGH);
    //    delay (1000);
    //    digitalWrite(Buzzer, LOW);
    //    delay (1000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    ThingSpeak.writeField(Channel_ID, FieldNumber1, 0, WriteAPIKey);          // Write data
    delay (5000);
    pixels.clear();
    pixels.show();
  }
  else
  {
    pixels.clear();
    pixels.show();
  }
}
