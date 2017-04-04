#include <Servo.h>
Servo myservo1;// create servo object to control a servo
Servo myservo2;

void goForward()
{
  Serial.println("Forward");
  myservo1.write(0);
  myservo2.write(0);
}

void goBackward()
{
  Serial.println("Backward");
  myservo1.write(180);
  myservo2.write(180);
}

void goLeft()
{
  Serial.println("Left");
  myservo1.write(0);
  myservo2.write(180);
}

void goRight()
{
  Serial.println("Right");
  myservo1.write(180);
  myservo2.write(0);
}

void goStop()
{
  Serial.println("Stop");
  myservo1.write(95);
  myservo2.write(95);
}

void setup()
{
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);

  Serial.begin(9600);
  goStop();
}

void loop()
{
  goForward();
  delay(5000);
  goBackward();
  delay(5000);
  goLeft();
  delay(5000);
  goRight();
  delay(5000);
  goStop();
  delay(5000); 
}
