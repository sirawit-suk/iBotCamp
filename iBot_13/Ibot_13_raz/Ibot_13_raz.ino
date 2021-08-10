#include <iBotC.h>
#define speedLess 105
#define speedMore 210

int s[4];

void setup() {
  // put your setup code here, to run once:
  iBotC();
  waitButton();
  beep();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  check();

  if ( s[0] == 1 and s[1] == 1 and s[2] == 1) {
    beep();
    stopCar();
    forward(500);
    spinLeft(450);
  } else if ( s[0] == 0 and s[1]== 1 and s[2] == 1 and (s[3] or not s[3])) {
    forward(50);
  } else if ( (s[0] or s[1]) )
    forwardLeft(50);

  else if ( (s[2] or s[3]))
    forwardRight(50);

  else if ( not( s[0] or s[1] or s[2] or s[3]) )
    backward(50);
  
}

void check() {

  s[0] = sensor0();
  s[1] = sensor1();
  s[2] = sensor2();
  s[3] = sensor3();

  for (int i= 0; i < 4; ++i) {
    Serial.print("S["+ String(i) + "] : ");
    Serial.println(s[i]);
  }
//
//  waitButton();
//  delay(500);
}
void stopCar(){
  motor(0,0,500);
}

void forward(int x){
  motor(speedLess, speedLess, x);
}

void backward(int x){
  motor(-speedLess, -speedLess, x);
}

void forwardRight(int x)
{
  motor(speedMore, speedLess, x);
}
void forwardLeft(int x)
{
  motor(speedLess, speedMore, x);
}
void spinLeft(int x)
{
  motor(-speedMore, speedMore, x);
}
