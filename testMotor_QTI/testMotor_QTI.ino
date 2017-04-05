

#include <Servo.h>
Servo myservo1;// create servo object to control a servo
Servo myservo2;
int sensorVal;
const int sensor = A4;

byte interruptPin = 0;  // your interrupt pin
volatile boolean ISRRan = 0;  // this variable is set in your ISR to trigger a break in the while loop
byte C = 0;  // this is just the counter var for the while loop


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
  pinMode(sensor, INPUT);

  attachInterrupt(interruptPin, myISR, RISING);

}

void myISR() {
  ISRRan = 1;
  // do other things in the ISR
}

void loop() {
  digitalWrite(sensor, HIGH);
  sensorVal = analogRead(sensor);
  Serial.println(sensorVal);
  while (sensorVal > 60) {
    if ( ISRRan ) {
      break;
    }
    Serial.println(sensorVal);
    goForward();
    delay(5000);
    goBackward();
    delay(5000);
    goLeft();
    delay(5000);
    goRight();
    delay(5000);
  }
  Serial.println(sensorVal);
  goStop();
  ISRRan = 0;  // Reset for whatever reason
}



