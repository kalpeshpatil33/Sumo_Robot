int int_lcd = 0;
int int_lcd_prev = 0;
int t_delay = 200;

#define LEDPIN 22  // LED

// Wheel Variables
#include <Servo.h>
Servo leftServo;
Servo rightServo;
Servo attackServo;
#define LEFT_servo 4
#define RIGHT_servo 5
#define ATTACK_servo 7

// Sonar distances
#define HCdistance 50
#define AttackHCdistance 8

// QTI MIDDLE Variable
volatile int MIDDLE_whiteLine = 1;
int MIDDLE_sensorVal;
#define MIDDLE_pinQTIsensor 2

// QTI LEFT Variable
volatile int LEFT_whiteLine;
int LEFT_sensorVal;
#define LEFT_pinQTIsensor 6

// QTI RIGHT Variable
volatile int RIGHT_whiteLine;
int RIGHT_sensorVal;
#define RIGHT_pinQTIsensor 3

// HC-SR04 FRONT LEFT Variable
#define FRONT_LEFT_trigPin 27
#define FRONT_LEFT_echoPin 28
long FRONT_LEFT_duration, FRONT_LEFT_distance;

// HC-SR04 FRONT RIGHT Variable
#define FRONT_RIGHT_trigPin 29
#define FRONT_RIGHT_echoPin 30
long FRONT_RIGHT_duration, FRONT_RIGHT_distance;

// HC-SR04 BACK Variable
#define BACK_trigPin 9
#define BACK_echoPin 8
long BACK_duration, BACK_distance;

// HC-SR04 LEFT Variable
#define LEFT_trigPin 11
#define LEFT_echoPin 10
long LEFT_duration, LEFT_distance;

// HC-SR04 RIGHT Variable
#define RIGHT_trigPin 13
#define RIGHT_echoPin 12
long RIGHT_duration, RIGHT_distance;


void goForward() {
  // moves robot forward
  leftServo.write(0);
  rightServo.write(190);
  int_lcd = 1;
}

void goBackward() {
  // moves robot backward
  leftServo.write(190);
  rightServo.write(0);
  int_lcd = 2;
}

void goLeft() {
  // moves robot left
  leftServo.write(0);
  rightServo.write(0);
  int_lcd = 3;
}

void goRight() {
  // moves robot right
  leftServo.write(190);
  rightServo.write(190);
  int_lcd = 4;
}

void goStop() {
  // stops robot
  digitalWrite(22, HIGH);
  leftServo.write(90);
  rightServo.write(90);
  attackServo.write(90);
  int_lcd = 5;
}

void goAttack() {
  // starts flipping
  attackServo.write(0);
  int_lcd = 6;
}

void goU() {
  // turn 180
  leftServo.write(0);
  rightServo.write(0);
  int_lcd = 7;
}

void FRONT_LEFT_HC() {
  digitalWrite(FRONT_LEFT_trigPin, LOW);
  digitalWrite(FRONT_LEFT_trigPin, HIGH);
  delay(100);
  digitalWrite(FRONT_LEFT_trigPin, LOW);
  FRONT_LEFT_duration = pulseIn(FRONT_LEFT_echoPin, HIGH);
  FRONT_LEFT_distance = (FRONT_LEFT_duration / 2) * 0.034;
}

void FRONT_RIGHT_HC() {
  digitalWrite(FRONT_RIGHT_trigPin, LOW);
  digitalWrite(FRONT_RIGHT_trigPin, HIGH);
  delay(100);
  digitalWrite(FRONT_RIGHT_trigPin, LOW);
  FRONT_RIGHT_duration = pulseIn(FRONT_RIGHT_echoPin, HIGH);
  FRONT_RIGHT_distance = (FRONT_RIGHT_duration / 2) * 0.034;
}

void BACK_HC() {
  digitalWrite(BACK_trigPin, LOW);
  digitalWrite(BACK_trigPin, HIGH);
  digitalWrite(BACK_trigPin, LOW);
  BACK_duration = pulseIn(BACK_echoPin, HIGH);
  BACK_distance = (BACK_duration / 2) * 0.034;
}

void LEFT_HC() {
  digitalWrite(LEFT_trigPin, LOW);
  digitalWrite(LEFT_trigPin, HIGH);
  digitalWrite(LEFT_trigPin, LOW);
  LEFT_duration = pulseIn(LEFT_echoPin, HIGH);
  LEFT_distance = (LEFT_duration / 2) * 0.034;
}

void RIGHT_HC() {
  digitalWrite(RIGHT_trigPin, LOW);
  digitalWrite(RIGHT_trigPin, HIGH);
  digitalWrite(RIGHT_trigPin, LOW);
  RIGHT_duration = pulseIn(RIGHT_echoPin, HIGH);
  RIGHT_distance = (RIGHT_duration / 2) * 0.034;
}

void setup() {

  Serial.begin(115200);  // XBee serial port
  pinMode(LEDPIN, OUTPUT);  // LED is off at the beginning

  // attach sevos
  leftServo.attach(LEFT_servo);
  rightServo.attach(RIGHT_servo);
  attackServo.attach(ATTACK_servo);

  // initialize QTIs
  pinMode(LEFT_pinQTIsensor, INPUT);
  pinMode(MIDDLE_pinQTIsensor, INPUT);
  pinMode(RIGHT_pinQTIsensor, INPUT);

  digitalWrite(LEFT_pinQTIsensor, HIGH);
  digitalWrite(MIDDLE_pinQTIsensor, HIGH);
  digitalWrite(RIGHT_pinQTIsensor, HIGH);

  // attach interrupt
  attachInterrupt(digitalPinToInterrupt(MIDDLE_pinQTIsensor), MIDDLE_whiteLineISR, LOW);
  interrupts(); // enable interrupts

  // configure sonar sensor pins
  pinMode(FRONT_LEFT_trigPin, OUTPUT);
  pinMode(FRONT_LEFT_echoPin, INPUT);
  pinMode(FRONT_RIGHT_trigPin, OUTPUT);
  pinMode(FRONT_RIGHT_echoPin, INPUT);
  pinMode(BACK_trigPin, OUTPUT);
  pinMode(BACK_echoPin, INPUT);
  pinMode(LEFT_trigPin, OUTPUT);
  pinMode(LEFT_echoPin, INPUT);
  pinMode(RIGHT_trigPin, OUTPUT);
  pinMode(RIGHT_echoPin, INPUT);

  // do not move at the beginning
  goStop();
  delay(500);
}

// interrupt for the middle QTI
void MIDDLE_whiteLineISR() {
  goStop();
  MIDDLE_whiteLine = 0;
  int_lcd = 10;
}

void loop() {
  // read from sonar sensors
  FRONT_LEFT_HC();
  FRONT_RIGHT_HC();
  LEFT_HC();
  RIGHT_HC();
  BACK_HC();

  // read QTI sensors
  LEFT_sensorVal = digitalRead(LEFT_pinQTIsensor);
  RIGHT_sensorVal = digitalRead(RIGHT_pinQTIsensor);

  // if front right QTI is on
  if (  RIGHT_sensorVal == 0 ) {
    goBackward();
    delay(500);
    goLeft();
    delay(t_delay);
  }

  // if front left QTI is on
  if (  LEFT_sensorVal == 0 ) {
    goBackward();
    delay(500);
    goRight();
    delay(t_delay);
  }

  // do if middle QTI is not detecting line
  if (MIDDLE_whiteLine == 1) {

    // if opponent is closer, attack
    if (FRONT_LEFT_distance < AttackHCdistance && FRONT_RIGHT_distance < AttackHCdistance ) {
      goAttack();
      delay(t_delay);
    }

    // if opponent is forward, go push
    if (FRONT_LEFT_distance < HCdistance && FRONT_RIGHT_distance < HCdistance) {
      goForward();
      delay(t_delay);
    }

    // if opponent is forward left, go left
    if (FRONT_LEFT_distance < HCdistance && FRONT_RIGHT_distance > HCdistance) {
      goForward();
      delay(t_delay);
    }

    // if opponent is forward right, go right
    if (FRONT_LEFT_distance > HCdistance && FRONT_RIGHT_distance < HCdistance) {
      goForward();
      delay(t_delay);
    }

    // if opponent is on left, go left
    if (LEFT_distance < HCdistance ) {
      goLeft();
      delay(t_delay);
    }

    // if opponent is on right, go right
    if (RIGHT_distance < HCdistance ) {
      goRight();
      delay(t_delay);
    }

    // if opponent is on back, rotate 180
    if (BACK_distance < HCdistance) {
      goU();
      delay(2 * t_delay);
    }
  }
  else {
    goStop();
    digitalWrite(LEDPIN, HIGH);
    while (1);
  }


  if (int_lcd_prev != int_lcd) {
    Serial.println(int_lcd_prev);
  }
  int_lcd_prev = int_lcd;
}
