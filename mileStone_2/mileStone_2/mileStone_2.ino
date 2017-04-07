#include <Servo.h>
Servo myservo1;// create servo object to control a servo
Servo myservo2;
volatile int LEFT_whiteLine;
volatile int RIGHT_whiteLine;
volatile int MIDDLE_whiteLine;
int sensorVal;
int Left_sensorVal;
int Right_sensorVal;
const int pinQTIsensor = 2;
const int pinLeft_QTIsensor = 22;
const int pinRight_QTIsensor = 23;

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

void setup() {

  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);
  Serial.begin(9600);
  pinMode(pinQTIsensor, INPUT); //set as input so we can perform a read on the pin
  Serial.begin(9600);

  pinMode(pinQTIsensor, INPUT);
  digitalWrite(pinQTIsensor, HIGH);

  pinMode(pinLeft_QTIsensor, INPUT);
  digitalWrite(pinLeft_QTIsensor, HIGH);

  pinMode(pinRight_QTIsensor, INPUT);
  digitalWrite(pinRight_QTIsensor, HIGH);

  attachInterrupt(0, MIDDLE_whiteLineISR, LOW);

  // we need to call this to enable interrupts
  interrupts();
  MIDDLE_whiteLine = 1;
  LEFT_whiteLine = 1;
  RIGHT_whiteLine = 1;
}

void MIDDLE_whiteLineISR() {
  goStop();
  Serial.println("Interrupt stop");
  MIDDLE_whiteLine = 0;
}

void loop() {
  sensorVal = digitalRead(pinQTIsensor);
  Left_sensorVal = digitalRead(pinLeft_QTIsensor);
  LEFT_whiteLine = Left_sensorVal;
  Right_sensorVal = digitalRead(pinRight_QTIsensor);
  RIGHT_whiteLine = Right_sensorVal;
  //Serial.println(Left_sensorVal);
  //Serial.println(Right_sensorVal);

  if (MIDDLE_whiteLine > 0) {

  }

//  if (LEFT_whiteLine == 1 & RIGHT_whiteLine == 1)
//  {
//    goForward();
//  }
//  else
//  {
//    goStop();
//    delay(1000);
//    goBackward();
//    delay(5000);
//    goLeft();
//    delay(3000);
//  }

  if (LEFT_whiteLine == 0)
  {
    goRight();
    delay(500);
    goForward();
    delay(500);
  }
  else
  {
    goForward();
  }

  if (RIGHT_whiteLine == 0)
  {
    goLeft();
    delay(500);
    goForward();
    delay(500);
  }
  else
  {
    goForward();
  }

}
