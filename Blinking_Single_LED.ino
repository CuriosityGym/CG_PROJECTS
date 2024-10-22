void setup()
{
  pinMode(10,OUTPUT); // Set pin No, 10 to output
}


void loop()
{
  digitalWrite(10,HIGH); //LED1 turns ON
  delay(1000);           // Delay of 1000 milliseconds
  digitalWrite(10,LOW);  // LED1 tuns OFF
  delay(1000);           // Delay of 1000 milliseconds
  
}
