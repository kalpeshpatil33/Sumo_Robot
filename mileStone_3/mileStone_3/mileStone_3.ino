
int flag_Found;


//********** Wheels Variable **********
#include <Servo.h>
Servo myservo1;
Servo myservo2;

//********** QTI MIDDLE Variable **********
volatile int MIDDLE_whiteLine;
int MIDDLE_sensorVal;
#define MIDDLE_pinQTIsensor 2

//********** QTI LEFT Variable **********
volatile int LEFT_whiteLine;
int LEFT_sensorVal;
#define LEFT_pinQTIsensor 3

//********** QTI RIGHT Variable **********
volatile int RIGHT_whiteLine;
int RIGHT_sensorVal;
#define RIGHT_pinQTIsensor 18

//********** HC-SR04 FRONT Variable **********
#define FRONT_trigPin 13
#define FRONT_echoPin 12
long FRONT_duration, FRONT_distance;

//********** HC-SR04 BACK Variable **********
#define BACK_trigPin 21
#define BACK_echoPin 22
long BACK_duration, BACK_distance;

//********** HC-SR04 LEFT Variable **********
#define LEFT_trigPin 21
#define LEFT_echoPin 22
long LEFT_duration, LEFT_distance;

//********** HC-SR04 RIGHT Variable **********
#define RIGHT_trigPin 21
#define RIGHT_echoPin 22
long RIGHT_duration, RIGHT_distance;


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

void goU()
{
  Serial.println("U");
  myservo1.write(0);
  myservo2.write(190);
}

void setup() {

  Serial.begin(9600);

  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);

  pinMode(MIDDLE_pinQTIsensor, INPUT);
  digitalWrite(MIDDLE_pinQTIsensor, HIGH);

  pinMode(RIGHT_pinQTIsensor, INPUT);
  digitalWrite(RIGHT_pinQTIsensor, HIGH);

  pinMode(LEFT_pinQTIsensor, INPUT);
  digitalWrite(LEFT_pinQTIsensor, HIGH);

  attachInterrupt(digitalPinToInterrupt(MIDDLE_pinQTIsensor), MIDDLE_whiteLineISR, LOW);
  attachInterrupt(digitalPinToInterrupt(RIGHT_pinQTIsensor), RIGHT_whiteLineISR, LOW);
  attachInterrupt(digitalPinToInterrupt(LEFT_pinQTIsensor), LEFT_whiteLineISR, LOW);

  // we need to call this to enable interrupts
  interrupts();
  MIDDLE_whiteLine = 1;
  LEFT_whiteLine = 0;
  RIGHT_whiteLine = 0;


  pinMode(FRONT_trigPin, OUTPUT);
  pinMode(FRONT_echoPin, INPUT);

flag_Found = 0;


}

void MIDDLE_whiteLineISR() {
  goStop();
  Serial.println(MIDDLE_sensorVal);
  Serial.println("STOP Interrupt");
  MIDDLE_whiteLine = 0;
}

void RIGHT_whiteLineISR() {
  RIGHT_whiteLine = 1;
  Serial.println("RIGHT  Interrupt");
}

void LEFT_whiteLineISR() {
  LEFT_whiteLine = 1;
  Serial.println("LEFT Interrupt");
}




void loop() {
  MIDDLE_sensorVal = digitalRead(MIDDLE_pinQTIsensor);
  LEFT_sensorVal = digitalRead(LEFT_pinQTIsensor);
  RIGHT_sensorVal = digitalRead(RIGHT_pinQTIsensor);

  Serial.println("Starts reading....");
  //FRONT_HC();
  //  Serial.println(FRONT_distance);

    if (MIDDLE_whiteLine == 1)
    {
      Serial.println("No White Line");
      if (flag_Found == 0)
      {
        goU();
        delay(100);
        searchBot();
        delay(1000);
      }
    }
    else
    {
      goStop();
      Serial.println(MIDDLE_sensorVal);
      Serial.println("Interrupt stop");
      MIDDLE_whiteLine = 0;
    }
  
    if (RIGHT_whiteLine == 1)
    {
      Serial.println("Right");
      RIGHT_whiteLine = 0;
    }
  
    if (LEFT_whiteLine == 1)
    {
      Serial.println("Left");
      LEFT_whiteLine = 0;
    }
    flag_Found = 0;
}

void FRONT_HC()
{
  digitalWrite(FRONT_trigPin, LOW);
  digitalWrite(FRONT_trigPin, HIGH);
  delay(100);
  digitalWrite(FRONT_trigPin, LOW);
  FRONT_duration = pulseIn(FRONT_echoPin, HIGH);
  FRONT_distance = (FRONT_duration / 2) / 29.1;
}

void BACK_HC()
{
  digitalWrite(BACK_trigPin, LOW);
  digitalWrite(BACK_trigPin, HIGH);
  digitalWrite(BACK_trigPin, LOW);
  BACK_duration = pulseIn(BACK_echoPin, HIGH);
  BACK_distance = (BACK_duration / 2) / 29.1;
}

void LEFT_HC()
{
  digitalWrite(LEFT_trigPin, LOW);
  digitalWrite(LEFT_trigPin, HIGH);
  digitalWrite(LEFT_trigPin, LOW);
  LEFT_duration = pulseIn(LEFT_echoPin, HIGH);
  LEFT_distance = (LEFT_duration / 2) / 29.1;
}

void RIGHT_HC()
{
  digitalWrite(RIGHT_trigPin, LOW);
  digitalWrite(RIGHT_trigPin, HIGH);
  digitalWrite(RIGHT_trigPin, LOW);
  RIGHT_duration = pulseIn(RIGHT_echoPin, HIGH);
  RIGHT_distance = (RIGHT_duration / 2) / 29.1;
}

void searchBot ()
{
  delay(1000);

  FRONT_HC();
  if (FRONT_distance < 30 && flag_Found == 0 )
  {
    Serial.println("Front Detected");
    Serial.println(FRONT_distance);
    goForward();
    delay(450);
    goStop();
    flag_Found = 1;
  }
  else
  {
    goStop();
  }

  BACK_HC();
  if (BACK_distance < 30 && flag_Found == 0 )
  {
    goU();
    delay(450);
    goStop();
    flag_Found = 1;
  }
  else
  {
    goStop();
  }

  RIGHT_HC();
  if (RIGHT_distance < 30 && flag_Found == 0 )
  {
    goRight();
    delay(450);
    goStop();
    flag_Found = 1;
  }
  else
  {
    goStop();
  }

  LEFT_HC();
  if (LEFT_distance < 30 && flag_Found == 0 )
  {
    goLeft();
    delay(450);
    goStop();
    flag_Found = 1;
  }
  else
  {
    goStop();
  }
}

