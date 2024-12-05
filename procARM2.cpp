float L1 = 80;
float L2 = 70;
float q1 = 70;
float q2 = 70;

void setup(){
  size(600,600);
}

void draw(){
  background(255);
  translate(width/2,height/2);
  scale(1,-1);
  strokeWeight(10);
  stroke(100);
  point(0,0);
  
  float x1 = L1*cos(radians(q1));
  float y1 = L1*sin(radians(q1));
  float x2 = L1*cos(radians(q1))+L2*cos(radians(q1+q2));
  float y2 = L1*sin(radians(q1))+L2*sin(radians(q1+q2));
  strokeWeight(5);
  line(0,0,x1,y1);
  line(x1,y1,x2,y2);
  println(q1+" : "+q2);

}

void keyPressed() {
  if(key == 'q' || key == 'Q'){  
    q1 += 5;
  }else if(key == 'w' || key == 'W'){
    q1 -= 5;
  }else if(key == 'a' || key == 'A'){
    q2 += 5;
  }else if(key == 's' || key == 'S'){
    q2 -= 5;
  }
}
