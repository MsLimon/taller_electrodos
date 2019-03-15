 /*  
  Melody  
  Plays a melody  
  circuit:  
  * 8-ohm speaker on digital pin 8  
  created 21 Jan 2010  
  modified 30 Aug 2011  
  by Tom Igoe  
 This example code is in the public domain.  
  http://arduino.cc/en/Tutorial/Tone  
  */  
  const int sonidos = 4;  
  float frec = 0;  
  float pot = 0;  
  float freky = 0;  
  float megaVal = 0;  
 void setup() {  
  Serial.begin(9600);  
  pinMode(sonidos, OUTPUT);  
 }  
 void loop() {  
   frec = analogRead(A0);  
   pot = analogRead(A1);  
   freky = map (frec, 0, 1023, 31, 400);  
   Serial.println(frec);  
   megaVal = random(freky, pot);  
   tone(sonidos, freky);  
   tone(sonidos, megaVal);  
   //noTone(4);  
   delay(30);  
  } 
