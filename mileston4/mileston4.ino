int flag_Found;
int flag_Right = 0;
int flag_Left = 0;

int count = 0;
int left_count = 0;

//********** Wheels Variable **********
#include <Servo.h>
Servo myservo1;
Servo myservo2;
#define LEFT_servo 4
#define RIGHT_servo 5
#define HCdistance 50

//********** QTI MIDDLE Variable **********
// BLACK == 1
volatile int MIDDLE_whiteLine;
int MIDDLE_sensorVal;
#define MIDDLE_pinQTIsensor 2

//********** QTI LEFT Variable **********
volatile int LEFT_whiteLine;
int LEFT_sensorVal;
#define LEFT_pinQTIsensor 21

//********** QTI RIGHT Variable **********
volatile int RIGHT_whiteLine;
int RIGHT_sensorVal;
#define RIGHT_pinQTIsensor 3

//********** HC-SR04 FRONT Variable **********
#define FRONT_trigPin 22
#define FRONT_echoPin 23
long FRONT_duration, FRONT_distance;

//********** HC-SR04 BACK Variable **********
#define BACK_trigPin 9
#define BACK_echoPin 8
long BACK_duration, BACK_distance;

//********** HC-SR04 LEFT Variable **********
#define LEFT_trigPin 11
#define LEFT_echoPin 10
long LEFT_duration, LEFT_distance;

//********** HC-SR04 RIGHT Variable **********
#define RIGHT_trigPin 13
#define RIGHT_echoPin 12
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
  myservo2.write(0);
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
  Serial.println("Searching");

  LEFT_HC(); RIGHT_HC();

  if (LEFT_distance < HCdistance && RIGHT_distance < HCdistance && flag_Found == 0 )
  {
    Serial.println("Front Detected");
    Serial.println(String(LEFT_distance) + " " + String(RIGHT_distance));
    flag_Found = 1;
    flag_Right = 0;
    flag_Left = 0;
  }

  if (LEFT_distance < HCdistance && RIGHT_distance > HCdistance && flag_Found == 0)
  {
    Serial.println("LEFT Detected");
    Serial.println(LEFT_distance);
    flag_Found = 1;
    flag_Right = 0;
    flag_Left = 1;
  }

  if (RIGHT_distance < HCdistance && LEFT_distance > HCdistance && flag_Found == 0)
  {
    Serial.println("RIGHT Detected");
    Serial.println(RIGHT_distance);
    flag_Found = 1;
    flag_Right = 1;
    flag_Left = 0;
  }
}

void setup() {

  Serial.begin(115200);

  myservo1.attach(LEFT_servo);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(RIGHT_servo);

  pinMode(LEFT_pinQTIsensor, INPUT);
  digitalWrite(LEFT_pinQTIsensor, HIGH);

  pinMode(MIDDLE_pinQTIsensor, INPUT);
  digitalWrite(MIDDLE_pinQTIsensor, HIGH);

  pinMode(RIGHT_pinQTIsensor, INPUT);
  digitalWrite(RIGHT_pinQTIsensor, HIGH);

  attachInterrupt(digitalPinToInterrupt(MIDDLE_pinQTIsensor), MIDDLE_whiteLineISR, LOW);
  attachInterrupt(digitalPinToInterrupt(RIGHT_pinQTIsensor), RIGHT_whiteLineISR, LOW);
  //  attachInterrupt(digitalPinToInterrupt(LEFT_pinQTIsensor), LEFT_whiteLineISR, LOW);

  // we need to call this to enable interrupts
  interrupts();
  MIDDLE_whiteLine = 1;
  RIGHT_whiteLine = 1;

  pinMode(FRONT_trigPin, OUTPUT);
  pinMode(FRONT_echoPin, INPUT);

  pinMode(RIGHT_trigPin, OUTPUT);
  pinMode(RIGHT_echoPin, INPUT);

  pinMode(BACK_trigPin, OUTPUT);
  pinMode(BACK_echoPin, INPUT);

  pinMode(LEFT_trigPin, OUTPUT);
  pinMode(LEFT_echoPin, INPUT);

  flag_Found = 0;
  goStop();
  Serial.println("Initializing all sensors");
  delay(2000);
  goStop();
}

void MIDDLE_whiteLineISR() {
  goStop();
  //Serial.println(MIDDLE_sensorVal);
  //Serial.println("STOP Interrupt");
  MIDDLE_whiteLine = 0;
}

void RIGHT_whiteLineISR() {
  Serial.println(RIGHT_sensorVal);
  Serial.println("RIGHT Interrupt");
  RIGHT_whiteLine = 0;
}

void loop()
{
  flag_Found = 0;
  flag_Left = 0;
  flag_Right = 0;
  Serial.println("Starts reading....");
  MIDDLE_sensorVal = digitalRead(MIDDLE_pinQTIsensor);
  LEFT_sensorVal = digitalRead(LEFT_pinQTIsensor);
  RIGHT_sensorVal = digitalRead(RIGHT_pinQTIsensor);

  //    Serial.println("MIDDLE_sensorVal: " + String(MIDDLE_sensorVal));
  //    Serial.println("LEFT_sensorVal: " + String(LEFT_sensorVal));
  //    Serial.println("RIGHT_sensorVal: " + String(RIGHT_sensorVal));
  //      RIGHT_HC();
  //      Serial.print("\t RIGHT \t" + String(RIGHT_distance));
  //      LEFT_HC();
  //      Serial.println(" \tLEFT \t" + String(LEFT_distance));
  //  goForward();
  //  delay(500);
  //  goBackward();
  //  delay(500);
  //  goLeft();
  //  delay(500);
  //  goRight();
  //  delay(500);

  //  if (  RIGHT_whiteLine == 0)
  //  {
  //    goBackward();
  //    delay(2000);
  //    RIGHT_whiteLine = 1;
  //  }

  if (MIDDLE_whiteLine == 1)
  {
    Serial.println("No White Line");

    if (flag_Found == 0)
    {
      searchBot();
    }

    if (flag_Found == 1 && flag_Right == 0 && flag_Left == 0)
    {
      goForward();
    }

    else if (flag_Found == 1 && flag_Right == 1 && flag_Left == 0)
    {
      goRight();
    }

    else if (flag_Found == 1 && flag_Right == 0 && flag_Left == 1)
    {
      goLeft();
    }
    else
    {
      goU();
    }
    delay(25);
  }
}
