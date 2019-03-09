/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

#define led 11


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {


  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorRaw = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  int brillo = map(sensorValue, 0, 1023, 0, 255);
  int brillo2 = map(sensorRaw, 0, 1023, 0, 255);
  float voltage = (sensorValue * (5.0 / 1023.0) * 100);
  // print out the value you read:
  analogWrite(led, brillo2);
  Serial.print(sensorRaw, DEC);
  Serial.print(",");
  Serial.print(voltage, DEC);
  Serial.println();
}
