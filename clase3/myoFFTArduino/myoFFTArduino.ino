//Aplicación de la ArduinoFFT a myoware
// Ejemplo 1
// Por Interactivas17, Marta Timon & Joaku De Sotavento

#include "arduinoFFT.h"
#include <RunningMedian.h>

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

  // mic

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  delay(2000);
}

void loop() {

    fftToServo();

  }

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

      
    }

  }

}




