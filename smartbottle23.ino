#include <Adafruit_NeoPixel.h>
#include "HX711.h"

#define LED_PIN D4 // Pin where your LED strip is connected
#define LED_COUNT 10 // Number of LEDs in your strip

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
HX711 scale;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  scale.begin(D2, D3); // Replace D2 and D3 with your DT and SCK pins
  scale.set_scale(12345); // Adjust this value to calibrate your scale
  scale.tare(); // Reset the scale to zero
  
  Serial.begin(9600);
}

void loop() {
  float weight = scale.get_units(); // Get weight reading

  // Define weight thresholds for different water levels
  float midWeight = 50.0; // Mid-level weight
  float maxWeight = 80.0; // Maximum weight
  float lowWeight = 20.0; // Low-level weight

  // Map weight reading to LED color based on water level
  uint8_t red, green, blue;
  
  if (weight >= maxWeight) {
    red = 255;
    green = 0;
    blue = 0; // Red for reminder to drink
  } else if (weight <= lowWeight) {
    red = 0;
    green = 0;
    blue = 255; // Blue for low water level
  } else {
    float percentage = map(weight, lowWeight, midWeight, 0, 100);
    red = 0;
    green = map(percentage, 0, 100, 0, 255);
    blue = 0; // Green for sufficient water intake
  }

  // Set LED color based on water level
  setColor(red, green, blue);

  delay(1000); // Delay to stabilize readings
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}
