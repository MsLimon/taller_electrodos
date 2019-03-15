const int ledPin = 13; // LED connected to digital pin 13
const int sensorPin = 0; // connect sensor to analog input 0
void setup()
{
pinMode(ledPin, OUTPUT); // enable output on the led pin
}
void loop()
{
int rate = analogRead(sensorPin); // read the analog input
digitalWrite(ledPin, HIGH); // set the LED on

delay(rate); // wait duration dependent on light level
digitalWrite(ledPin, LOW); // set the LED off
delay(rate);
}
