#include <Servo.h>  //Including Servo motor Library

int lightValue;   // Declaring Variable.

Servo servo_D7;   // Servo Motor connected pin

void setup()
{
  Serial.begin(115200);  // For Serial monitor  

  servo_D7.attach(D7);  

}


void loop()
{
  lightValue = (analogRead(A0));  //Storing analog value in Variable
  Serial.print("Light Value: ");       // Printing Variable values on serial monitor
  Serial.println(lightValue);
  if (lightValue > 800) {                 // If variable value is more than 800
    servo_D7.write(120);               // Servo motor will move 120 degree

  } else {
    servo_D7.write(0);               // It will remain at zero position

  }
  delay(250);                 

}
