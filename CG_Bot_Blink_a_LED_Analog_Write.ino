void setup()
{
  pinMode(A4, OUTPUT);   // Set analog pin A4 as an output for LED1
}

void loop()
{
  analogWrite(A4, 255);  // Set LED1 connected to A4 to maximum brightness (255)
  delay(1000);            // Wait for 1000 milliseconds (1 second) with LED1 ON at full brightness
  
  analogWrite(A4, 0);    // Set LED1 connected to A4 to 0 brightness (OFF)
  delay(1000);            // Wait for 1000 milliseconds (1 second) with LED1 OFF
}
