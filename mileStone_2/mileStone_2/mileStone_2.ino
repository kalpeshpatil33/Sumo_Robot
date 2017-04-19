#include <Servo.h>
Servo myservo1;
Servo myservo2;
volatile int MIDDLE_whiteLine;

int sensorVal;
const int pinQTIsensor = 2;
const int LED = 22;


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

void setup() {

  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);
  Serial.begin(9600);
  pinMode(pinQTIsensor, INPUT); //set as input so we can perform a read on the pin
  digitalWrite(pinQTIsensor, HIGH);
  pinMode(22, OUTPUT);

  attachInterrupt(0, MIDDLE_whiteLineISR, LOW);

  // we need to call this to enable interrupts
  interrupts();
  MIDDLE_whiteLine = 1;
}

void MIDDLE_whiteLineISR() {
  goStop();
  Serial.println(sensorVal);
  Serial.println("Interrupt stop");
  MIDDLE_whiteLine = 0;
}

void loop() {
  sensorVal = analogRead(pinQTIsensor);
  Serial.println(sensorVal);

  if (MIDDLE_whiteLine == 1)
  {
    goForward();
    delay(2000);
    goLeft();
    delay(450);
    goForward();
    delay(2000);
    goLeft();
    delay(450);
  }
  else
  {
    goStop();
    Serial.println(sensorVal);
    Serial.println("Interrupt stop");
    MIDDLE_whiteLine = 0;
  }
}
