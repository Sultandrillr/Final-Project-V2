#include <WiFi.h>
#include <HTTPClient.h>
#include "Connectivity.h"
#include <ArduinoJson.h>
#include <FastLED.h>

//const char* WIFI_SSID = "BT-2JCPFQ";
//const char* WIFI_PASSWORD = "LondonDublin";
const char* API_BASE = "https://qocfzpp98l.execute-api.eu-west-2.amazonaws.com/prod";

#define DATA_PIN 27
#define NUM_LEDS 72
CRGB leds[NUM_LEDS];
int hue;
int saturation;
int value;
bool isOn;

void setup() {
  
  Serial.begin(115200);
  delay(1000);//does not like when its not there before WiFi.begin
  Connectivity::setup_wifi();

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  delay(1000);
  HTTPClient http;
  http.begin(String(API_BASE) + "/rooms/1/state");
  int httpcode = http.GET();
  if (httpcode == 200) {
    String payload = http.getString();
    //still needs to parse the Json response from the API 
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (error){
      Serial.println("Json Could not be parsed");
      Serial.println(error.f_str());
      return;
    }
    

    if (hue != doc["hue"]){
      hue = doc["hue"];
    }
    if(saturation != doc["saturation"]){
      saturation = doc["saturation"];
    }
    if(value != doc["value"]){
      value = doc["value"];
    }
    if(isOn != doc["is_on"]){
      isOn = doc["is_on"];
    }
    Serial.printf("H:%d S:%d V:%d On:%d\n", hue, saturation, value, isOn);

    if(isOn == true){
      //FastLED expects hue to be 0-255 instead of 0-360 so it needs some conversion
      int hue_255 = (int)((hue/360.0) * 255);
      CHSV hsvColor(hue_255, saturation, value);
      CRGB rgbColor;
      hsv2rgb_rainbow(hsvColor, rgbColor);
      Serial.printf("RGB: R=%d G=%d B=%d\n", rgbColor.r, rgbColor.g, rgbColor.b);
      fill_solid(leds, NUM_LEDS, rgbColor);
      FastLED.show();
      delay(50);
    }else{
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
    }


  }else{
    Serial.printf("HTTP %d\n", httpcode);

  }
  http.end();
}
