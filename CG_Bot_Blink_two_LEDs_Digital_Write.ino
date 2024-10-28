void setup()
{
  pinMode(10, OUTPUT);   // Set digital pin 10 as output for LED1
  pinMode(9, OUTPUT);    // Set digital pin 9 as output for LED2
}

void loop()
{
  digitalWrite(10, HIGH);    // Turn LED1 ON by setting pin 10 to HIGH
  delay(1000);               // Wait for 1000 milliseconds (1 second) with LED1 ON
  digitalWrite(10, LOW);     // Turn LED1 OFF by setting pin 10 to LOW
  delay(1000);               // Wait for 1000 milliseconds (1 second) with LED1 OFF
  
  digitalWrite(9, HIGH);     // Turn LED2 ON by setting pin 9 to HIGH
  delay(1000);               // Wait for 1000 milliseconds (1 second) with LED2 ON
  digitalWrite(9, LOW);      // Turn LED2 OFF by setting pin 9 to LOW
  delay(1000);               // Wait for 1000 milliseconds (1 second) with LED2 OFF
}
