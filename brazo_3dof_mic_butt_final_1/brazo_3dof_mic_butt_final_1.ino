
/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include "arduinoFFT.h"
#include <RunningMedian.h>

Servo servoUno, servoDos, servoTres;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos1 = 0;    // variable to store the servo position
int pos2 = 0;
int pos3 = 0;

/// las variables buenas

//int posBraTres[270];



///// las variables del boton

#define boton 5
int signal1 = 0;
int signal2 = 0;


///// las variables del microfono

#define mic A0

#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 1000 //Hz, must be less than 10000 due to ADC

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

RunningMedian samples = RunningMedian(5);
int x;
long l, a, m, h;



void setup() {
  Serial.begin(115200);


  servoUno.attach(7);  // este es el brazo mas largo
  servoDos.attach(9);  // este es el brazo  de en medio
  servoTres.attach(10);  // este es el brazo del final

  pos1 = 90; // posicion inicial de los servos
  pos2 = 90;
  pos3 = 90;
  servoUno.write(pos1);
  servoDos.write(pos2);
  servoTres.write(pos3);

  // boton
  pinMode(boton, INPUT);


  // mic

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  delay(2000);
}

void loop() {


  int valBoton = digitalRead(boton);
  //botonIsPressed(valBoton)
  if (valBoton) {

    int trazos = random(1, 15);

    fftToServo();

    servoUno.attach(7);  // este es el brazo mas largo
    servoDos.attach(9);  // este es el brazo  de en medio
    servoTres.attach(10);  // este es el brazo del final

    pos1 = 90; // posicion inicial de los servos
    pos2 = 90;
    pos3 = 90;

    servoUno.write(pos1);
    servoDos.write(pos2);
    servoTres.write(pos3);
    delay(500);

    for (int i = 0; i < trazos; i++) {

      pos1 = random(80, 100);
      pos2 = random(70, 120);
      pos3 = random(0, l);

      //if (pos1 >= 120 || pos1 <= 60)periodo1Rand *= -1;
      //pos1 += periodo1Rand;
      servoUno.write(pos1);
      servoDos.write(pos2);
      servoTres.write(pos3);
      delay(1000);
    }

    servoUno.write(90);
    servoDos.write(90);
    servoTres.write(90);
    delay(500);


  }



  servoUno.detach();  // este es el brazo mas largo
  servoDos.detach();  // este es el brazo  de en medio
  servoTres.detach();  // este es el brazo del final
  /*Esta parte haceun recorrido completo en el brazo largo y uno aleatorio en el brazo pequeño */

  delay(10);


}

void fftToServo() {

  for (int i = 0; i < 5; i++) {

    /*SAMPLING*/
    for (int j = 0; j < SAMPLES; j++)
    {
      microseconds = micros();    //Overflows after around 70 minutes!

      vReal[j] = analogRead(mic);
      vImag[j] = 0;

      while (micros() < (microseconds + sampling_period_us)) {
      }
    }

    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

    /*PRINT RESULTS*/
    //Serial.println(peak);     //Print out what frequency is the most dominant.

    for (int k = 10; k < (SAMPLES / 2); k++)
    {
      /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
      //Serial.print(millis());
      //      Serial.print("\t");
      //      Serial.print((k * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
      //      Serial.print("\t");
      //      Serial.print(vReal[k], 1);    //View only this line in serial plotter to visualize the bins


      x = vReal[k];

      samples.add(x);
      l = samples.getLowest();
      a = samples.getAverage();
      m = samples.getMedian();
      h = samples.getHighest();


      //      Serial.print("\t");
      //      Serial.print(x);
      //      Serial.print("\t");
      //      Serial.print(l);
      //      Serial.print("\t");
      //      Serial.print(h);
      //      Serial.print("\t");
      //      Serial.print(m);
      //      Serial.print("\t");
      //      Serial.println(a);
      //delay(100);

      //posBraTres[i + k * SAMPLES / 2] = l;

    }

  }

}




