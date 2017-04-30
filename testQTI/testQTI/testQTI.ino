/*
 * Kalpesh Patil
 * QTI Sensor as an analog input
 * W: Ein
 * R: I/O: A4
 * B: GND
 * 
 */
int sensorVal; 
const int sensor = 20; 
unsigned long ntime;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT); //set as input so we can perform a read on the pin
}

void loop() {
  ntime = millis();
  digitalWrite(sensor, HIGH); //set it high to produce an output signal
  //it seems weird because the sensor is an input device
  
  sensorVal = digitalRead(sensor); //save the value from the analog read into sensorVal
  Serial.println(String(ntime) + " " + String(sensorVal)); //display sensorVal
  delay(100);
}
  

