// iBot 13 
#include <iBotC.h> 

int s0,s1,s2,s3; // 4 sensors
int left,right; // 2 sensors 

int speedLess = 90; //105
int speedNormal = 255; //210
int distance = 30;
bool done = false;

int state = 1; 
//speed is blue color variable but it can use but not recommend 
//find another name
 
void setup(){
  iBotC();
  waitButton(); // recommended... stop motor before upload code
  beep();
  forward(500);
}

void loop(){
  
  check();
  if (state == 1){
    trackLine1();
  }
  else if(state == 2){
    trackLine2();
  }
  else if(state == 3){
    trackLine3();
  }
  else if(state == 4){
    trackLine4(); 
  }
  else if(state == 5){
    trackLine5();
  }
  else if(state == 6){
    trackLine6();
  }
  else if(state == 7){
    ending1();
  }
  
  

}

void trackLine1(){    // Scan Distance and turnright 

  //Spcial case 
  if (done == true && (s0 == 0 && s1 == 1 && s2 == 1 && s3 == 1 || s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1)){
    beep(2);
    turnRight(700);
    state = 2;
  }

  //Normal case
  if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1){
    forward(100);
  }
  
  if (s0 == 0 && s1 == 1 && s2 == 1 && s3 == 0){
    forward(20);
  }
  else if (s0 == 0 && s1 == 0 && s2 == 1 && s3 == 0){
    forwardRight(20); 
  }
  else if (s0 == 0 && s1 == 1 && s2 == 0 && s3 == 0){
    forwardLeft(20); 
  }
  else if (s0 == 0 && s1 == 0 && s2 == 1 && s3 == 1 || s0 == 0 && s1 == 1 && s2 == 1 && s3 == 1 || s0 == 0 && s1 == 0 && s2 == 0 && s3 == 1){
    turnRight(30);
  }
  else if (s0 == 1 && s1 == 1 && s2 == 0 && s3 == 0 || s0 == 1 && s1 == 1 && s2 == 1 && s3 == 0 || s0 == 1 && s1 == 0 && s2 == 0 && s3 == 0){

    if (done == false){
      distance = ultraSonic();
    }
    
    if (distance < 20 && done == false){
      beep(1);
      forward(100);
      turnLeft(700);
      done = true;
    }
    else{
      turnLeft(30);
    }
  }
  else if (s0 == 0 && s1 == 0 && s2 == 0 && s3 == 0){
    backward(30);
  }

  
}

void trackLine2(){  // First Curve - blackline

  //Special Case
  if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1){
    beep(3);
    forward(200);
    state = 3;
  }
  
  //Normal case
  trackNormal();
}

void trackLine3(){ // Curve Maze - blackline

  //Special case
  if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1){
    beep(4);
    turnLeft(700);
    state = 4;
  } 
  //Normal case
  trackNormal();
    
}

void trackLine4(){ // Straight - blackline - turn left

  //Special case
  if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1){
    beep(5);
    turnLeft(500);
    state = 5;
  } 
  //Normal case
  trackNormal();
}

void trackLine5(){
  //Special case
  if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 0){
    beep(6);
    turnLeft(700);
    turnRight(700);
    state = 6;
  }
  
  
  //Normal case
  if (s0 == 0 && s1 == 0 && s2 == 0 && s3 == 0){
    forward(20);
  }
  else if (s0 == 0 && s1 == 0 && s2 == 0 && s3 == 1){
    forwardRight(20); 
  }
  else if (s0 == 0 && s1 == 0 && s2 == 1 && s3 == 0 || s0 == 0 && s1 == 1 && s2 == 1 && s3 == 0){
    forwardLeft(20);
  }
  
}

void trackLine6(){
  //Special case
  if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1){
    beep(7);
    state = 7;
  }
  //Normal case
  trackNormal();
}

void ending1(){
  forward(550);
  stopCar(100);
  hooray();
  
}

void trackNormal(){
  //Normal case
  if (s0 == 0 && s1 == 1 && s2 == 1 && s3 == 0){
    forward(20);
  }
  else if (s0 == 0 && s1 == 0 && s2 == 1 && s3 == 0){
    forwardRight(20); 
  }
  else if (s0 == 0 && s1 == 1 && s2 == 0 && s3 == 0){
    forwardLeft(20); 
  }
  else if (s0 == 0 && s1 == 0 && s2 == 1 && s3 == 1 || s0 == 0 && s1 == 1 && s2 == 1 && s3 == 1 || s0 == 0 && s1 == 0 && s2 == 0 && s3 == 1){
    turnRight(30);
  }
  else if (s0 == 1 && s1 == 1 && s2 == 0 && s3 == 0 || s0 == 1 && s1 == 1 && s2 == 1 && s3 == 0 || s0 == 1 && s1 == 0 && s2 == 0 && s3 == 0){
    turnLeft(30);
  }
  else if (s0 == 0 && s1 == 0 && s2 == 0 && s3 == 0){
    backward(30);
  }
}

void hooray(){
  while(1){
    led("Red");
    delay(250);
    led("Green");
    delay(250);
    led("Blue");
    delay(250);
  }
}

void check(){
  // black press 1 time 
  // white press 2 times
  // wait until light blink 4 times 

  // light on return 1 (for black)
  // light off return 0 (for white)
  
  s0 = sensor0();
  s1 = sensor1();
  s2 = sensor2();
  s3 = sensor3();

  //left = LineFollowerL();
  //right = LineFollowerR();

  //Serial.println(s0);
  //Serial.println(s1);
  //Serial.println(s2);
  //Serial.println(s3);
  
}

void stopCar(int x){
  motor(0,0,x);
}

void forward(int x){
  motor(speedNormal, speedNormal, x);
}

void backward(int x){
  motor(-speedNormal, -speedNormal, x);
}

void forwardRight(int x)
{
  motor(speedNormal, speedLess, x);
}

void forwardLeft(int x)
{
  motor(speedLess, speedNormal, x);
}

void turnRight(int x){
  motor(speedNormal, 0, x);
}

void turnLeft(int x){
  motor(0, speedNormal, x);
}
