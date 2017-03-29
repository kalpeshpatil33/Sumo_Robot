/*
 * Kalpesh Patil
 * QTI Sensor as an analog input
 * W: Ein
 * R: I/O
 * B: GND
 * 
 */
int sensorVal; 
const int sensor = A4; 

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT); //set as input so we can perform a read on the pin
}

void loop() {
  digitalWrite(sensor, HIGH); //set it high to produce an output signal
  //it seems weird because the sensor is an input device
  
  sensorVal = analogRead(sensor); //save the value from the analog read into sensorVal
  Serial.println(sensorVal); //display sensorVal
  delay(100);
}
  
