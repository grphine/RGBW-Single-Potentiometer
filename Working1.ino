#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_RGBW + NEO_KHZ800);

int potPin= A4;  //Declare potPin to be analog pin A0
int readValue;  // Use this variable to read Potentiometer
int val = 0;
 

void setup() {
  strip.begin();
  strip.show(); //resets all pixels to 0
  strip.setBrightness(255);
  
  pinMode(potPin, INPUT);  //set potPin to be an input
  Serial.begin(9600);      // turn on Serial Port
}
 
void loop() {
  
 readValue = analogRead(potPin);  //Read the voltage on the Potentiometer

 if (readValue < 2 or readValue > 1022){
  setAll(0,0,0,0);
 }
 else if (readValue == 2){
  setAll(255,0,0,0);
  Serial.println("max red");
 }
 else if (2 < readValue and readValue < 255){
  val = readValue;
  setAll((-val + 257), val, 0,0);
  Serial.println("RdGu");
 }

 else if (readValue == 256){
  setAll(0,255,0,0);
  Serial.println("max green");
 }
 else if(256 < readValue and readValue < 510){
  val = readValue - 255;
  setAll(0,(-val + 257), val, 0);
  Serial.println("GdBu");
 }
 else if (readValue == 511){
  setAll(0,0,255,0);
  Serial.println("max blue");
 }
 else if(510 < readValue and readValue < 765){
  val = readValue - 510;
  setAll(val,0,(-val + 257), 0);
  Serial.println("BdRu");
 }
 else if (readValue == 766){
  setAll(0,0,0,255);
  Serial.println("max white");
 }
 else if(765 < readValue and readValue < 1022){
  val = readValue - 765;
  setAll(0,0,0,(-val + 257));
  Serial.println("white");
 }


 
 Serial.println(readValue);
 
}

int setAll(int R, int G, int B, int W){
  int i = 0;
   for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, G, R, B, W);
    
  }
  strip.show();
}


