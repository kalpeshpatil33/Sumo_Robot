
#include <Servo.h>
Servo myservo1;// create servo object to control a servo
Servo myservo2;
volatile int whiteLine;
int sensorVal;
const int sensor = A4;

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
  pinMode(sensor, INPUT); //set as input so we can perform a read on the pin
  Serial.begin(9600);
  digitalWrite(sensor, HIGH);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);

  attachInterrupt(0, whiteLineISR, LOW);

  // we need to call this to enable interrupts
  interrupts();

  // start moving
  whiteLine = 0;
  goForward();
  delay(1000);
  goBackward();
  delay(1000);
  goLeft();
  delay(1000);
  goRight();
  delay(1000);

}

void whiteLineISR() {
  goStop();
  Serial.println("Interrupt stop");
  whiteLine = 0;
}

void loop() {
  sensorVal = analogRead(sensor);
    if (whiteLine > 0) {
  //    goStop();
  ////    whiteLine = 0;
  goForward();
  delay(1000);
  goBackward();
  delay(1000);
  goLeft();
  delay(1000);
  goRight();
  delay(1000);
    }
}
