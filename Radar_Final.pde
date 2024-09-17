import processing.serial.*; // Imports library for serial communication

Serial myPort; // Defines Serial Object
String angle = "";
String distance = "";
String data = "";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1 = 0;
PFont orcFont;

void setup() {
  fullScreen(); // Set canvas size to full screen
  smooth();
  myPort = new Serial(this, "COM13", 9600); // Start serial communication
  myPort.bufferUntil('.'); // Read data up to the character '.'
  orcFont = loadFont("OCRAExtended-30.vlw");
}

void draw() {
  background(0); // Clear the background
  fill(98, 245, 31);
  textFont(orcFont);
  
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

void serialEvent(Serial myPort) { // Reads data from Serial Port
  data = myPort.readStringUntil('.');
  if (data != null) {
    data = data.trim(); // Remove any extra whitespace
    index1 = data.indexOf(",");
    if (index1 != -1) {
      angle = data.substring(0, index1);
      distance = data.substring(index1 + 1);
      
      iAngle = int(angle);
      iDistance = int(distance);
    }
  }
}

void drawRadar() {
  pushMatrix();
  translate(width / 2, height / 2); // Center radar in the canvas
  noFill();
  strokeWeight(2); // Thicker lines for better visibility
  stroke(98, 245, 31);
  
  // Draw radar arcs with adjusted sizes
  arc(0, 0, 400, 400, PI, TWO_PI);
  arc(0, 0, 300, 300, PI, TWO_PI);
  arc(0, 0, 200, 200, PI, TWO_PI);
  arc(0, 0, 100, 100, PI, TWO_PI);
  
  // Draw angle lines from 0° to 180°
  for (int angle = 0; angle <= 180; angle += 30) {
    float xEnd = 200 * cos(radians(angle));
    float yEnd = 200 * sin(radians(angle));
    line(0, 0, xEnd, yEnd);
  }
  
  // Draw semicircle to show the radar field
  noFill();
  strokeWeight(2);
  arc(0, 0, 400, 400, PI, TWO_PI);
  
  popMatrix();
}

void drawObject() {
  pushMatrix();
  translate(width / 2, height / 2); // Center object in the canvas
  strokeWeight(3); // Adjust line thickness
  stroke(255, 10, 10); // Red color
  
  if (iDistance >= 0 && iDistance < 40) { // Ensure distance is within the valid range
    pixsDistance = iDistance * 10; // Adjust scaling factor for better fit
    line(pixsDistance * cos(radians(iAngle)), -pixsDistance * sin(radians(iAngle)),
         200 * cos(radians(iAngle)), -200 * sin(radians(iAngle)));
  }
  popMatrix();
}

void drawLine() {
  pushMatrix();
  strokeWeight(3); // Adjust line thickness
  stroke(30, 250, 60); // Green color
  translate(width / 2, height / 2); // Center line in the canvas
  line(0, 0, 200 * cos(radians(iAngle)), -200 * sin(radians(iAngle)));
  popMatrix();
}

void drawText() { // Draws text on the screen
  fill(0, 0, 0);
  noStroke();
  rect(0, height - 120, width, 120); // Background for text
  
  fill(98, 245, 31);
  textSize(20);
  
  // Distance scale
  text("10cm", width * 0.55, height - 90);
  text("20cm", width * 0.65, height - 90);
  text("30cm", width * 0.75, height - 90);
  text("40cm", width * 0.85, height - 90);
  
  textSize(25);
  
  // Status and measurements
  text("Object: " + (iDistance > 40 ? "Out of Range" : "In Range"), 30, height - 60);
  text("Angle: " + iAngle + " °", width * 0.55, height - 60);
  text("Distance: " + (iDistance < 40 ? iDistance + " cm" : "N/A"), width * 0.55, height - 30);
  
  textSize(20);
  fill(98, 245, 60);
  
  // Draw angle labels from 0° to 180°
  translate(width / 2, height / 2); // Center text in the canvas
  for (int angle = 0; angle <= 180; angle += 30) {
    pushMatrix();
    rotate(radians(-angle));
    text(angle + "°", 0, -220); // Adjust position for visibility
    popMatrix();
  }
}
