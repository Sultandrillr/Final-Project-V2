#include <Arduino.h>
#include "WifiControl.h"
#include <SPI.h>
#include <EEPROM.h>
#include <WiFiS3.h>
#include "LedControl.h"

String htmlPage;    //String for page that user gets served
bool isWifiConnected = false;
String currentLine = "";    //Used to put responses into serial monitor

MyWifi::MyWifi(){
  //empty constructor
}

char MyWifi::ssid[MAX_CREDENTIAL_SIZE + 1] = "";
char MyWifi::password[MAX_CREDENTIAL_SIZE + 1] = "";

WiFiServer MyWifi::server(80);    //Opens port 80
WiFiClient MyWifi::client;

void MyWifi::setup_wifi(){
  load_credentials();
  if (!isSsidNull()){
    connect_to_wifi();
  }
  if (WiFi.status() != WL_CONNECTED) {    //Checks if Wifi is connected
    isWifiConnected = false;
    start_ap();   //starts access point mode
    setup_server();   //Setup server for serving client
    Serial.println(WiFi.localIP());   //prints local IP. Default is 192.168.4.1

    while(!client.connected()){   //While client is not connected attempt to connect and wait.
      client = server.available();
      delay(11);
      ;
    }
    Serial.println("Client has connected");
    serve_wifi_setup(client);   //Serves client with page to set up wifi
  }
}

void MyWifi::load_credentials(){
  EEPROM.get(SSID_ADDRESS, ssid);
  EEPROM.get(PASSWORD, password);
  EEPROM.end();
}

void MyWifi::save_credentials(const char* newSSID, const char* newPassword){

  //I forgot ts for ages. Better data integrity if i erase the previous data before I write new data. Less chance of breaking sum.
  for (int i = 0; i < MAX_CREDENTIAL_SIZE + 1; i++){
    EEPROM.write(SSID_ADDRESS + i, 0);
    EEPROM.write(PASSWORD + i, 0);
  }

  //EEPROM.begin(64);//sets the size    again allegedly I dont need this
  EEPROM.put(SSID_ADDRESS, newSSID);
  EEPROM.put(PASSWORD, newPassword);
  EEPROM.end();
}

void MyWifi::connect_to_wifi(){
  Serial.println("Attempting to connect to wifi");
  Serial.print("SSID:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 300){
    Serial.print("|");
    delay(100);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Wifi connection succesful...");
    isWifiConnected = true;
  } else {
      Serial.println("Connection failed");
  } 
}



bool MyWifi::isSsidNull(){
  if (ssid[0] == '\0'){
    return true;
  }else{return false;}
}