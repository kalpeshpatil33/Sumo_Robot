/*
   Kalpesh Patil
   Motor Testing Code with QTI Sensor
   Motor1 +: 1Y -:2Y (motor1Pin,motor2Pin)
   Motor2 +: 4Y -:3Y (motor3Pin,motor4Pin)
  QTI Sensor as an analog input
   W: Ein
   R: I/O: A4
   B: GND

*/

const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin1 = 9;    // H-bridge enable pin

const int motor3Pin = 5;    // H-bridge leg 1 (pin 10, 3A)
const int motor4Pin = 6;    // H-bridge leg 2 (pin 15, 4A)
const int enablePin2 = 10;    // H-bridge enable pin

int sensorVal; //
const int sensor = A4; //

void setup() {

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin1, OUTPUT);

  pinMode(motor3Pin, OUTPUT);
  pinMode(motor4Pin, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  pinMode(sensor, INPUT); //set as input so we can perform a read on the pin

  Serial.begin(9600);
  digitalWrite(sensor, HIGH);
}
void rotateLeft()
{
  Serial.println("LEFT");
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high

  digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor4Pin, HIGH);  // set leg 2 of the H-bridge high
}

void rotateStop()
{
  Serial.println("STOP");
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);
}
void loop() {
  // if the switch is high, motor will turn on one direction:


  sensorVal = analogRead(sensor); //save the value from the analog read into sensorVal
  Serial.println(sensorVal); //display sensorVal

  if (sensorVal < 100)
  {
    Serial.println("Rotating left; START");
    rotateLeft();
    delay(500);
  }
  else
  {
    rotateStop();
    Serial.println("Finished Rotating left; STOP");
  }
}
