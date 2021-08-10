#include <iBotC.h>

void setup()
{
  iBotC();
}

void loop()
{
  int LEFT = sensor1();
  int RIGHT = sensor2();

  if (!LEFT and !RIGHT)
    motor(200, 200);
  else  if (!LEFT)
    motor (0, 200);
  else if (!RIGHT)
    motor(200, 0);
  else motor(0, 0);

  if (button())
    led("Red");
  else if (ultraSonic() < 20)
    led("Green");
  else led("White");

  print("Left : ");
  println(LEFT);
  print("Right : ");
  println(RIGHT);

}
