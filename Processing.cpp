

import processing.serial.*;


Serial port;  // Serial port object
boolean portSelected = false;


// GUI Elements
int sliderX = 50;
int slider1Y = 100;
int slider2Y = 200;
int slider3Y = 300;
int sliderWidth = 300;
int sliderHeight = 20;


// Servo positions (0-180)
int pos1 = 90;
int pos2 = 90;
int pos3 = 90;
int Cpos1 = 90;
int Cpos2 = 90;
int Cpos3 = 90;


// For dragging sliders
boolean isDragging1 = false;
boolean isDragging2 = false;
boolean isDragging3 = false;


void setup() {
  size(400, 400);


  // List all available serial ports
  println("Available serial ports:");
  for (int i = 0; i < Serial.list().length; i++) {
  println(i + ": " + Serial.list()[i]);
  }


  // Try to connect to Arduino (change index as needed)
  try {
  port = new Serial(this, Serial.list()[0], 9600);
  portSelected = true;
  }
  catch (Exception e) {
  println("Could not open serial port. Check connection and port number.");
  }
}


void draw() {
  background(200);


  if (!portSelected) {
  textAlign(CENTER, CENTER);
  text("No serial port connected.\nCheck Arduino connection.", width/2, height/2);
  return;
  }


  // Draw sliders
  drawSlider(sliderX, slider1Y, pos1, "Servo 1: " + pos1 + "°");
  drawSlider(sliderX, slider2Y, pos2, "Servo 2: " + pos2 + "°");
  drawSlider(sliderX, slider3Y, pos3, "Servo 3: " + pos3 + "°");


  // Send data to Arduino
  sendServoPositions();
  println("Sim "+pos1+" : "+pos2+" : "+pos3);
  println("Robot "+Cpos1+" : "+Cpos2+" : "+Cpos3);
}


void drawSlider(int x, int y, int value, String label) {
  // Draw slider background
  fill(100);
  rect(x, y, sliderWidth, sliderHeight);


  // Draw slider handle
  fill(255);
  float handleX = map(value, 0, 180, x, x + sliderWidth);
  rect(handleX - 5, y - 5, 10, sliderHeight + 10);


  // Draw label
  fill(0);
  textAlign(LEFT, BOTTOM);
  text(label, x, y - 5);
}


void mousePressed() {
  // Check if mouse is over any slider handle
  float handle1X = map(pos1, 0, 180, sliderX, sliderX + sliderWidth);
  float handle2X = map(pos2, 0, 180, sliderX, sliderX + sliderWidth);
  float handle3X = map(pos3, 0, 180, sliderX, sliderX + sliderWidth);


  if (mouseX >= handle1X - 5 && mouseX <= handle1X + 5 &&
  mouseY >= slider1Y - 5 && mouseY <= slider1Y + sliderHeight + 5) {
  isDragging1 = true;
  }
  if (mouseX >= handle2X - 5 && mouseX <= handle2X + 5 &&
  mouseY >= slider2Y - 5 && mouseY <= slider2Y + sliderHeight + 5) {
  isDragging2 = true;
  }
  if (mouseX >= handle3X - 5 && mouseX <= handle3X + 5 &&
  mouseY >= slider3Y - 5 && mouseY <= slider3Y + sliderHeight + 5) {
  isDragging3 = true;
  }
}


void mouseDragged() {
  if (isDragging1) updateSlider(1);
  if (isDragging2) updateSlider(2);
  if (isDragging3) updateSlider(3);
}


void mouseReleased() {
  isDragging1 = false;
  isDragging2 = false;
  isDragging3 = false;
}


void updateSlider(int sliderNum) {
  // Calculate new position based on mouse X position
  int newPos = int(map(constrain(mouseX, sliderX, sliderX + sliderWidth),
  sliderX, sliderX + sliderWidth,
  0, 180));


  // Update appropriate slider
  switch(sliderNum) {
  case 1:
  pos1 = newPos;
  break;
  case 2:
  pos2 = newPos;
  break;
  case 3:
  pos3 = newPos;
  break;
  }
}


void sendServoPositions() {
  if (portSelected && port != null) {
  port.write(int(255));  // Header byte
  port.write(int(pos1));
  port.write(int(pos2));
  port.write(int(pos3));
  }
}


// Optional: Handle incoming confirmation from Arduino
int state = 0;
int data = 0;
void serialEvent(Serial p) {
  if (state == 0) {
  if (p.available() > 0) {
    data = p.read();
    if (data == 255) {
      state = 1;
    }
  }
  } else if (state == 1) {
  if (p.available() > 0) {
    Cpos1 = p.read();
    state = 2;
  }
  } else if (state == 2) {
  if (p.available() > 0) {
    Cpos2 = p.read();
    state = 3;
  }
  } else if (state == 3) {
  if (p.available() > 0) {
    Cpos3 = p.read();
    state = 0;
  }
  } else {
  state = 0;
  }
}
