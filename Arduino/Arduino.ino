#include <IRremote.hpp>
#include <SPI.h>
#include "WifiControl.h"
#include "LedControl.h"
#include <FastLED.h>

#define NUM_LEDS 144
CRGB leds[NJUM_LEDS];
IRrecv IR(11);
const int ledPin = 5;
//const int redPin = 6;
//const int greenPin = 10;
//const int bluePin = 5;

int fadeDelay = 10;

long int irCode = 20000;

void(* resetFunc) (void) = 0;   //resets arduino to make sure it can connect to wifi

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS28112B, ledPin, GBR>(leds, NUM_LEDS);
  // Change colour of the lights like this...
  //leds[1] = CRGB (0, 0, 255);
  //FastLED.show();

  MyWifi::setup_wifi();
  Serial.println("Setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:

}
