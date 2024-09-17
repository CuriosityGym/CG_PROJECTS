import processing.serial.*; // imports library for serial communication

Serial myPort; // defines Object Serial
// defines variables
String angle = "";
String distance = "";
String data = "";
String noObject;
float pixsDistance;
int iAngle = 0, iDistance = 0;
PFont orcFont;

void setup() {
  size(1200, 700); // Set the size of the window
  smooth();
  myPort = new Serial(this, "COM13", 9600); // starts the serial communication
  myPort.bufferUntil('.'); // reads the data from the serial port up to the character '.'
}

void draw() {
  fill(98, 245, 31);
  // simulating motion blur and slow fade of the moving line
  noStroke();
  fill(0, 4);
  rect(0, 0, width, height - height * 0.065);

  fill(98, 245, 31); // green color
  // calls the functions for drawing the radar
  drawRadar();
  drawLine();
  drawObject();
  drawText();
}

void serialEvent(Serial myPort) { // starts reading data from the Serial Port
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('.');
  data = data.substring(0, data.length() - 1);

  int index1 = data.indexOf(","); // find the character ',' and puts it into the variable "index1"
  angle = data.substring(0, index1); // read the data from position "0" to position of the variable index1 or that's the value of the angle the Arduino Board sent into the Serial Port
  distance = data.substring(index1 + 1, data.length()); // read the data from position "index1" to the end of the data or that's the value of the distance

  // converts the String variables into Integer
  iAngle = int(angle);
  iDistance = int(distance);
}

void drawRadar() {
  pushMatrix();
  translate(width / 2, height - height * 0.074); // moves the starting coordinates to new location
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);
  // draws the arc lines
  arc(0, 0, (width - width * 0.0625), (width - width * 0.0625), PI, TWO_PI);
  arc(0, 0, (width - width * 0.27), (width - width * 0.27), PI, TWO_PI);
  arc(0, 0, (width - width * 0.479), (width - width * 0.479), PI, TWO_PI);
  arc(0, 0, (width - width * 0.687), (width - width * 0.687), PI, TWO_PI);
  // draws the angle lines
  line(-width / 2, 0, width / 2, 0);
  line(0, 0, (-width / 2) * cos(radians(30)), (-width / 2) * sin(radians(30)));
  line(0, 0, (-width / 2) * cos(radians(60)), (-width / 2) * sin(radians(60)));
  line(0, 0, (-width / 2) * cos(radians(90)), (-width / 2) * sin(radians(90)));
  line(0, 0, (-width / 2) * cos(radians(120)), (-width / 2) * sin(radians(120)));
  line(0, 0, (-width / 2) * cos(radians(150)), (-width / 2) * sin(radians(150)));
  line((-width / 2) * cos(radians(30)), 0, width / 2, 0);
  popMatrix();
}

void drawObject() {
  pushMatrix();
  translate(width / 2, height - height * 0.074); // moves the starting coordinates to new location
  strokeWeight(9);
  stroke(255, 10, 10); // red color
  pixsDistance = iDistance * ((height - height * 0.1666) * 0.025); // converts the distance from cm to pixels
  // draws the object according to the angle and the distance
  if (iDistance > 0) {
    line(pixsDistance * cos(radians(iAngle)), -pixsDistance * sin(radians(iAngle)), (width - width * 0.505) * cos(radians(iAngle)), -(width - width * 0.505) * sin(radians(iAngle)));
  }
  popMatrix();
}

void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30, 250, 60);
  translate(width / 2, height - height * 0.074); // moves the starting coordinates to new location
  line(0, 0, (height - height * 0.12) * cos(radians(iAngle)), -(height - height * 0.12) * sin(radians(iAngle))); // draws the line according to the angle
  popMatrix();
}

void drawText() { // draws the texts on the screen
  pushMatrix();
  fill(0, 0, 0);
  noStroke();
  rect(0, height - height * 0.065, width, height); // Background rectangle for text

  fill(98, 245, 31);
  textSize(25);

  // Distance labels
  text("10cm", width - width * 0.3854, height - height * 0.050);
  text("20cm", width - width * 0.281, height - height * 0.050);
  text("30cm", width - width * 0.177, height - height * 0.050);
  text("40cm", width - width * 0.0729, height - height * 0.050);

  textSize(30);
  text("Angle: " + iAngle + " °", width - width * 0.48, height - height * 0.025);
  text("Distance: " + (iDistance > 0 ? iDistance + " cm" : "Out of Range"), width - width * 0.26, height - height * 0.025);

  // Angle labels
  fill(98, 245, 60);
  textSize(20);
  float[] anglePositions = {30, 60, 90, 120, 150};
  for (float angle : anglePositions) {
    float rad = radians(angle);
    float x = width / 2 * cos(rad);
    float y = -width / 2 * sin(rad);
    text(angle + "°", width / 2 + x, height - height * 0.074 + y);
  }

  popMatrix();
}
