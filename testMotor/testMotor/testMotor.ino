const int switchPin = LOW;    // switch input
const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin1 = 9;    // H-bridge enable pin

const int motor3Pin = 5;    // H-bridge leg 1 (pin 2, 1A)
const int motor4Pin = 6;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin2 = 10;    // H-bridge enable pin

void setup() {
  // set the switch as an input:
  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin1, OUTPUT);

  pinMode(motor3Pin, OUTPUT);
  pinMode(motor4Pin, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  Serial.begin(9600);

  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
}

void loop() {
  // if the switch is high, motor will turn on one direction:
  if (Serial.available() > 0 )
  {
    int n = Serial.readStringUntil('\n').toInt();

    if (n == 1) {
      Serial.print("Forward");
      digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high

      digitalWrite(motor3Pin, HIGH);   // set leg 1 of the H-bridge low
      digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
    }
    // if the switch is low, motor will turn in the other direction:
    if (n == 2) {
      Serial.print("Backward");
      digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low

      digitalWrite(motor3Pin, LOW);  // set leg 1 of the H-bridge high
      digitalWrite(motor4Pin, HIGH);   // set leg 2 of the H-bridge low
    }
  }
}
