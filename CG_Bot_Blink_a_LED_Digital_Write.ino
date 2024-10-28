// Function to initialize settings, runs once when the program starts
void setup()
{
  pinMode(10, OUTPUT);      // Set digital pin 10 as an output pin to control the LED
}

void loop()
{
  digitalWrite(10, HIGH);   // Turn the LED ON by setting pin 10 to HIGH
  delay(1000);              // Wait for 1000 milliseconds (1 second) while LED is ON

  digitalWrite(10, LOW);    // Turn the LED OFF by setting pin 10 to LOW
  delay(1000);              // Wait for 1000 milliseconds (1 second) while LED is OFF
}
