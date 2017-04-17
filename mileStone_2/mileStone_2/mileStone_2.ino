#include <Servo.h>
Servo myservo1;
Servo myservo2;
volatile int MIDDLE_whiteLine;
int sensorVal;
const int pinQTIsensor = 2;


void goForward()
{
  Serial.println("Forward");
  myservo1.write(0);
  myservo2.write(190);
}

void goBackward()
{
  Serial.println("Backward");
  myservo1.write(190);
  myservo2.write(0);
}

void goLeft()
{
  Serial.println("Left");
  myservo1.write(0);
  myservo2.write(0);
}

void goRight()
{
  Serial.println("Right");
  myservo1.write(190);
  myservo2.write(190);
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

  attachInterrupt(0, MIDDLE_whiteLineISR, LOW);

  // we need to call this to enable interrupts
  interrupts();
  MIDDLE_whiteLine = 1;
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

  if (MIDDLE_whiteLine > 0)
  {

  }
  goForward();
  delay(2000);
  goLeft();
  delay(450);
  goForward();
  delay(2000);
  goLeft();
  delay(450);
}
