#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "receive.h"
#include "WF.h"
#include "mqtt.h"

void setup(){
    Serial.begin(115200);
    delay(115200);

    Serial.println("Khoi dong thanh cong Serial.");

    WF::setup_wifi();
    Serial.println("Cau hinh thanh cong WiFi");
    MQTT::setup_routes();
    Serial.println("Cau hinh thanh cong MQTT");
    MQTT::connect_brocker();
    Serial.println("ket noi thanh cong voi Brocker");
    receive::initLr();

    receive::checking_route();

    
}

void loop(){
    receive::receive_data();
    delay(10);
}