#include <iBotC.h>

int s0,s1,s2,s3;

int speed_MORE = 210;
int speed_LESS = 105; 

int state = 0;

String color = "";

void setup() 
{
  iBotC();
  waitButton();
  beep();
}

void loop() 
{
  Check();
  
  if(Mission() && state == 0)    //STATE 0 -> 1
  {
    Stop();
    state = 1;
    Forward(300);
    TurnRight(800);
  }
  else if(Mission() && state == 1) //STATE 1 -> 2  
  {
    Stop();
    state = 2;
    Forward(300);
    TurnLeft(800);
  }
  else if(Mission() && state == 2) //STATE 2 -> 3
  {
    Stop();
    state = 3;
    Forward(400);
  }
  else if(Mission() && state == 3) //STATE 3 -> 4 // HIT BALL
  {
    Stop();
    state = 4;
    Forward(1000);
    Backward(700);
    TurnRight(800);
  }
  else if(Mission() && state == 4) //STATE 4 -> 5 // Check Color
  {
    Stop();
    state = 5;
    Forward(400);
    CheckColor();
    TurnLeft(800);
  }
  else if(CheckTurnLeft() && (state == 5 || state == 7)) //STATE 5 -> 6 _ 7 -> 8// Turn1/3
  {
    Stop();
    if(state == 5) state = 6;
    else if(state == 7) state = 8;
    Forward(400);
    TurnLeft(850);
  }
  else if(CheckTurnRight() && (state == 6 || state == 8)) //STATE 6 -> 7 _ 8 -> 9 // Turn2/4
  {
    Stop();
    if(state == 6) state = 7;
    else if(state == 8) state = 9;
    Forward(400);
    TurnRight(850);
  }
  else if(Mission() && state == 9) //STATE 9 -> 10 // Check Color1
  {
    Stop();
    state = 10;
    Forward(1000);
    CheckColor();
    Backward(700);
    TurnRight(800);
  }
  else if(Mission() && state == 10) //STATE 10 -> 11 // Intersection
  {
    Stop();
    state = 10;
    Forward(400);
    TurnRight(800);
  }
  else if(s0 == 0 && s1 == 0 && s2 == 1 && s3 == 0)
  {
    motor(speed_MORE,speed_LESS,10);
  }
  else if(s0 == 0 && s1 == 1 && s2 == 0 && s3 == 0)
  {
    motor(speed_LESS,speed_MORE,10);
  }
  else if(s0 == 0 && s1 == 1 && s2 == 1 && s3 == 0)
  {
    Forward(100);
  }
  else
  {
    Backward(100);
  }


}
void Check()
{
  s0 = sensor0();   //1
  s1 = sensor1();   //2
  s2 = sensor2();   //3
  s3 = sensor3();   //4
}
void CheckColor()
{
  color = readColor();
  if(color == "Red"){
    led("Red");
  }
  else if(color == "White"){
    led("White");
  }
  else if(color == "Blue"){
    led("Blue");
  }
  else if(color == "Green"){
    led("Green");
  }
}
void Stop()
{
  motor(0,0,100);
}
void Forward(int x)
{
  motor(speed_LESS,speed_LESS,x);
}
void Backward(int x)
{
  motor(-speed_LESS,-speed_LESS,x);
}
void TurnRight(int x)
{
  motor(speed_MORE,0,x);
}
void TurnLeft(int x)
{
  motor(0,speed_MORE,x);
}
bool Mission()
{
  if(s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1)
       return true;
  else return false;
}
bool CheckTurnLeft()
{
  if(s0 == 1 && s1 == 1 && s2 == 1 && s3 == 0)
       return true;
  else return false;
}
bool CheckTurnRight()
{
  if(s0 == 0 && s1 == 1 && s2 == 1 && s3 == 1)
       return true;
  else return false;
}
