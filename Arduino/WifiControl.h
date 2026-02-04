#ifndef WifiControl_H
#define WifiControl_H
#include <WiFiS3.h>//just for the errors

#define SSID_ADDRESS 0
#define PASSWORD 32
#define MAX_CREDENTIAL_SIZE 31

class MyWifi{
  public:
  static char ssid[MAX_CREDENTIAL_SIZE + 1];
  static char password[MAX_CREDENTIAL_SIZE + 1];
  static WiFiServer server;
  static WiFiClient client;
  static void setup_wifi();
  static void load_credentials();
  static void save_credentials(const char *, const char *);
  static void connect_to_wifi();
  static void start_ap();
  static void setup_server();
  static void serve_wifi_setup(WiFiClient &client);//needs to have a loop and exit on \POST + when exit save new credentials
  static String HTMLPage();

  private:
  bool IsSsidNull();
};

#endif