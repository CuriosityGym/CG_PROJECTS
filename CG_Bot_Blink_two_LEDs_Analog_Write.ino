void setup()
{
  pinMode(A4, OUTPUT);   // Set pin 4 as an output for LED1
  pinMode(A5, OUTPUT);   // Set pin 5 as an output for LED2
}

void loop()
{
  analogWrite(A4, 255);   // Set LED1 (connected to pin 4) to maximum brightness (255)
  delay(1000);            // Wait for 1000 milliseconds (1 second) with LED1 ON at full brightness
  
  analogWrite(A4, 0);     // Turn off LED1 by setting brightness to 0
  delay(1000);            // Wait for 1000 milliseconds (1 second) with LED1 OFF
  
  analogWrite(A5, 255);   // Set LED2 (connected to pin 5) to maximum brightness (255)
  delay(1000);            // Wait for 1000 milliseconds (1 second) with LED2 ON at full brightness
  
  analogWrite(A5, 0);     // Turn off LED2 by setting brightness to 0
  delay(1000);            // Wait for 1000 milliseconds (1 second) with LED2 OFF
}
