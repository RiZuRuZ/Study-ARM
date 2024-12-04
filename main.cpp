  #include <ESP32Servo.h>
  static const int servoPin1 = 32;
  static const int servoPin2 = 33;
  static const int servoPin3 = 12;

  int state = 0;
  int data = 0;

  Servo servo1;
  Servo servo2;
  Servo servo3;
  float q1 = 0;
  float q2 = 0;
  float x = 0;
  float y = 0;
  float theta1 = 0;
  float theta2 = 0;
  #define L1 80
  #define L2 70
  void u(){
    if(Serial.available() > 0){
      data = Serial.read();
    }
  }
  void setup() {
    Serial.begin(9600);
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    Serial.onReceive(&u);

  }

  void FK(float theta1,float theta2){
    x = L1*cos(radians(theta1))+L2*cos(radians(theta1+theta2));
    y = L1*sin(radians(theta1))+L2*sin(radians(theta1+theta2));
    q1 = map(theta1,-90,90,0,180);
    q2 = map(theta2,0,180,180,0);
    Serial.print(x);
    Serial.print(" : ");
    Serial.println(y);
    Serial.print(q1);
    Serial.print(" : ");
    Serial.println(q2);
  }

  void loop() {Q
    if (data == -1) {
      return;
    }
    if (state == 0 ){
      if(data == 255){
        state = state+1;
        data=-1;
      }  
    }else if(state == 1){
      state = state+1;
      servo1.write(data);
        data=-1;
      
    }else if(state == 2){
      state = state+1;
      servo2.write(data);
        data=-1;
    }else if(state == 3){
      state = 0;
      servo3.write(data);
          data=-1;
    }


    // FK(0,0);

    // servo3.write(90); //penDown
    // delay(1000);
    // servo1.write(180);
    // delay(1000);
    // servo2.wrtie(180);
    // delay(1000);
    // servo1.write(0);
  }

