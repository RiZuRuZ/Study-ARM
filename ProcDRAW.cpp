
int mouseXo ;
int mouseYo ;
boolean isDrawing = false;
void setup() {
  size(600, 600);  // Set canvas size
  background(255);  // Set background color to white
  stroke(200);  // Set line color to light gray
  noFill();  // No fill for the grid lines
  textAlign(CENTER, CENTER);  // Center the text for better placement
  textSize(12);  // Set text size for the numbers
  fill(0);  // Set text color to black for better visibility

  int gridSize = 20;  // Size of each grid cell
  int cols = width / gridSize;  // Number of columns
  int rows = height / gridSize;  // Number of rows

  // Draw vertical grid lines and numbers
  for (int i = 0; i <= cols; i++) {
    float x = i * gridSize;
    line(x, 0, x, height);  // Vertical lines
    text(i*20, x, height - 10);  // Numbers on the bottom of each vertical line
  }

  // Draw horizontal grid lines and numbers
  for (int i = 0; i <= rows; i++) {
    float y = i * gridSize;
    line(0, y, width, y);  // Horizontal lines
    text(i*20, 10, y);  // Numbers on the left of each horizontal line
  }
}

void draw() {
  //ellipse(280,140,200,200);
  //rect(180,140,10*20,340);
  //ellipse(140,520,200,200);
  //ellipse(420,520,200,200);
  stroke(200,100,100);
  if (isDrawing) {
    // Draw line from previous mouse position to current mouse position
    line(mouseXo, mouseYo, mouseX, mouseY);  // Draw a line from the previous position to the current one
    mouseXo = mouseX;  // Update the previous mouse position
    mouseYo = mouseY;
  }

  
  //line(150,25,mouseX,mouseY);

}

void mousePressed() {
  
  //if(mouseButton == LEFT) {
  //  background(2,125,240);
  //}else{
  //  background(255,125,240);
  //}
  
  if (mouseButton == LEFT) {
    mouseXo = mouseX;
    mouseYo = mouseY;
    isDrawing = true;
  }
}

void mouseReleased() {
  if (mouseButton == LEFT) {
    isDrawing = false;
  }
}



void keyPressed() {
  if(key == 'q' || key == 'Q'){
    background(0);
  }
}
