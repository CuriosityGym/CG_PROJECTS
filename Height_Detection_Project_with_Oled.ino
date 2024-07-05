#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int trigPin = 12;   // Trig pin of the ultrasonic sensor
const int echoPin = 13;  // Echo pin of the ultrasonic sensor
const int referenceHeight = 200;  // Reference height from the sensor to the ground in cm

long duration;
int distance;
int height;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize OLED display with I2C address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  height = referenceHeight - distance; // Calculate the height of the person

  // Prints the height on the Serial Monitor
  Serial.print("Height: ");
  Serial.print(height);
  Serial.println(" cm");

  // Clear the display
  display.clearDisplay();

  // Display the height on the OLED screen
  display.setTextSize(2);       // Set text size to 2
  display.setTextColor(SSD1306_WHITE); // Set text color to white
  display.setCursor(0, 28);     // Set cursor position
  display.print("Height: ");
  display.print(height);        // Print the height
  display.print(" cm");         // Print the unit
  display.display();            // Update the display

  delay(1000); // Delay for 1 second before taking another measurement
}
