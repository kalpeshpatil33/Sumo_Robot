/*
   Kalpesh Patil
   Motor Testing Code
   Motor1 +: 1Y -:2Y (motor1Pin,motor2Pin)
   Motor2 +: 4Y -:3Y (motor3Pin,motor4Pin)


*/

const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin1 = 9;    // H-bridge enable pin

const int motor3Pin = 5;    // H-bridge leg 1 (pin 10, 3A)
const int motor4Pin = 6;    // H-bridge leg 2 (pin 15, 4A)
const int enablePin2 = 10;    // H-bridge enable pin

unsigned long ntime;

void goForward()
{
  Serial.println("Forward");
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high

  digitalWrite(motor3Pin, HIGH);   // set leg 1 of the H-bridge low
  digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
}

void goBackward()
{
  Serial.println("Backward");
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
  digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low

  digitalWrite(motor3Pin, LOW);  // set leg 1 of the H-bridge high
  digitalWrite(motor4Pin, HIGH);
}

void goLeft()
{
  Serial.println("LEFT");
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high

  digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor4Pin, HIGH);  // set leg 2 of the H-bridge high
}
void goRight()
{
  Serial.println("RIGHT");
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motor1Pin, HIGH);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high

  digitalWrite(motor3Pin, HIGH);   // set leg 1 of the H-bridge low
  digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
}

void goStop()
{
  Serial.println("STOP");
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);
}

void setup() {

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin1, OUTPUT);

  pinMode(motor3Pin, OUTPUT);
  pinMode(motor4Pin, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  Serial.begin(9600);

  goForward();
  delay(1000);
  goBackward();
  delay(1000);
  goLeft();
  delay(1000);
  goRight();
  delay(1000);
  goStop();

}

void loop() {

  ntime = millis();

    if (Serial.available() > 0 )
  {
    int n = Serial.readStringUntil('\n').toInt();

    if (n == 1)
    {
    }
    if (n == 2)
    {
    }
    if (n == 3)
    {
    }
    if (n == 4)
    {
    }

    if (n == 5)
    {
    }
  }
}
