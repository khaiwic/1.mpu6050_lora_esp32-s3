#ifndef WF_H
#define WF_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "../../../include/pinconfig.h"

extern const char *ssid;
extern const char *password;
extern WiFiClientSecure espClient;

class WF{
public:
    static void setup_wifi();
    static void send();
};

#endif
