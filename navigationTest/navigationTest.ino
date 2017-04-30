//********** Wheels Variable **********
#include <Servo.h>
Servo myservo1;
Servo myservo2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    String x = Serial.readStringUntil('\n');
    if (x == "w")
    {
      goForward();
    }
    if (x == "s")
    {
      goBackward();
    }
    if (x == "a")
    {
      goLeft();
    }
    if (x == "d")
    {
      goRight();
    }
  }
  delay(100);
}
void goForward()
{
  digitalWrite(22, LOW);
  Serial.println("Forward");
  myservo1.write(0);
  myservo2.write(190);
}

void goBackward()
{
  digitalWrite(22, LOW);
  Serial.println("Backward");
  myservo1.write(190);
  myservo2.write(0);
}

void goLeft()
{
  digitalWrite(22, LOW);
  Serial.println("Left");
  myservo1.write(0);
  myservo2.write(0);
}

void goRight()
{
  digitalWrite(22, LOW);
  Serial.println("Right");
  myservo1.write(190);
  myservo2.write(190);
}

void goStop()
{
  digitalWrite(22, HIGH);
  Serial.println("Stop");
  myservo1.write(95);
  myservo2.write(95);
}
