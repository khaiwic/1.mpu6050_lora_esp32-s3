#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "../../../include/pinconfig.h"
#include "WF.h"

const char *ssid = "TP-Link p301";
const char *password = "p301p301p301";

WiFiClientSecure espClient;

void WF::setup_wifi(){
    delay(10);
    Serial.print("\n Dang ket noi vao WiFi: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED){
        Serial.print("..");
        delay(500);
    }
    Serial.println("\n da ket noi thanh cong voi WiFi");

    espClient.setInsecure();
}

