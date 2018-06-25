#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_RGBW + NEO_KHZ800); //Light strip declared: (strip width, output pin, strip type)

int potPin= A4;  //potentiometer input pin
int readValue;  //value read off potentiometer
int val = 0; //brings read value into pixel range (potentiometer output 0-1023, strip takes 0-255)
 

void setup() {
  strip.begin(); //Initialises strip
  strip.show(); //Resets all pixels to 0, turns all lights off
  strip.setBrightness(255);
  
  pinMode(potPin, INPUT);  //set potPin to be an input
  Serial.begin(9600);      // turn on Serial Port
}
 
void loop() {
  
 readValue = analogRead(potPin);  //Read the voltage on the Potentiometer

 if (readValue < 2 or readValue > 1022){
  setAll(0,0,0,0); //turn all off if pot value near either end
 }
 else if (readValue == 2){
  setAll(255,0,0,0);
  Serial.println("max red"); //max red output before fade. Required to cover gaps where lights will turn off, giving blinking effect - not smooth
 }
 else if (2 < readValue and readValue < 255){ //first quarter turn of potentiometer
  val = readValue;
  setAll((-val + 257), val, 0,0); //red intensity decreases linearly (y=-x+257), green intensity increases linearly (y=x)
  Serial.println("RdGu"); //"Red down, Green up                   //when graphing above, y is intensity, x is value between 0-255 read from potentiometer
 }

 else if (readValue == 256){
  setAll(0,255,0,0);
  Serial.println("max green");
 }
 else if(256 < readValue and readValue < 510){ //second quarter turn
  val = readValue - 255;    //potentiometer outputs value between 256-510. -255 brings value back between 1-255 (valid range of pixel input)
  setAll(0,(-val + 257), val, 0);
  Serial.println("GdBu"); //Green down, Blue up
 }
 else if (readValue == 511){
  setAll(0,0,255,0);
  Serial.println("max blue");
 }
 else if(510 < readValue and readValue < 765){
  val = readValue - 510;
  setAll(val,0,(-val + 257), 0);
  Serial.println("BdRu");  //Blue down, Red up
 }
 else if (readValue == 766){ //after going through all 2 colour mixes possible, last quarter controls white LED intensity
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

int setAll(int R, int G, int B, int W){ //setAll takes RGBW values
  int i = 0;
   for(i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, G, R, B, W); //Iterate through every pixel, set pixel LED intensities to values input to function
    
  }
  strip.show(); //Displays colours to strip
}



