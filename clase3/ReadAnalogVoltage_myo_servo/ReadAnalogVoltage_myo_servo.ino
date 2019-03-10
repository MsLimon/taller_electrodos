/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

#define led 9
#include <Servo.h>

int posiciones[] = {10,  30,  50,  70,  
                    90, 120,  140,  170};

Servo servoUno;

int pos1 = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  servoUno.attach(11);  // este el brazo largo

  pos1 = 90;

  servoUno.write(pos1);

  delay(2000);
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
  pos1 = map(sensorValue, 0, 1023, 0, 7);
  // print out the value you read:
  analogWrite(led, brillo);
  servoUno.write(posiciones[pos1]);
  Serial.print(sensorValue, DEC);
  Serial.print(",");
  Serial.print(sensorRaw, DEC);
  Serial.println();

  delay(10);
}
