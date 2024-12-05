float L1 = 80;
float L2 = 70;
float q1 = 70;
float q2 = 70;

ArrayList<PVector> drawpoint = new ArrayList<PVector>();

void setup(){
  size(500,500);
}

void draw(){
  background(162,5,35);
  translate(width/2,height/2);
  scale(1,-1);
  strokeWeight(10);
  stroke(30);
  point(0,0);
  ellipse(0,0,(L1+L2)*2,(L1+L2)*2);
  
  for(int i=0;i<drawpoint.size();i++){
    stroke(255,0,0);
    strokeWeight(10);
    PVector p = drawpoint.get(i);
    point(p.x,p.y);
  }
  
  stroke(30);
  
  
  println((mouseX-width/2)+" : "+(height/2-mouseY));
  IK(mouseX-width/2,height/2-mouseY);
  
  float x1 = L1*cos(radians(q1));
  float y1 = L1*sin(radians(q1));
  float x2 = L1*cos(radians(q1))+L2*cos(radians(q1+q2));
  float y2 = L1*sin(radians(q1))+L2*sin(radians(q1+q2));
  strokeWeight(5);
  ellipse(0,0,20,20);
  line(0,0,x1,y1); 
  ellipse(x1,y1,20,20);
  line(x1,y1,x2,y2);
  println(q1+" : "+q2);
 
  
  scale(1,-1);
  textSize(20);
  text("x : y ="+x2+" : "+y2,-150,-150);
}

void IK(float x ,float y){
  float theta2 = acos(((y*y)+(x*x)-(L1*L1)-(L2*L2))/(2*L1*L2));
  float theta1 = atan2(y,x)-atan2(L2*sin(theta2),L1+L2*cos(theta2));
  q1 = degrees(theta1);
  q2 = degrees(theta2);
}

void keyPressed(){
  if (key == 'q' || key == 'Q'){
    q1-=5;
  }
  if (key == 'w' || key == 'W'){
    q1+=5;
  }
  if (key == 'e' || key == 'E'){
    q2-=5;
  }
  if (key == 'r' || key == 'R'){
    q2+=5;
  }
}
boolean isDrawing = false;
void mousePressed(){
  isDrawing = true;
}

void mouseReleased() {
  isDrawing = false;
}

void mouseDragged() {
  if(isDrawing == true && calculateWorkspace(mouseX-width/2,height/2-mouseY)){
    drawpoint.add(new PVector(mouseX-width/2,height/2-mouseY));
  }
}

boolean calculateWorkspace(float x,float y){
  float r = sqrt(sq(x)+sq(y));
  if(r>(L1+L2)){
    return false;
  }
  return true;
}
