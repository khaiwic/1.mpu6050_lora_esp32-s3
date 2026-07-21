#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "../../../include/pinconfig.h"
#include "WF.h"
#include "mqtt.h"

const char* mqtt_server = "aa9d8788a7654eb88cb3246e1e8b4e6e.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "khaideptrai13907@gmail.com";
const char* mqtt_pass = "Khai@123";

PubSubClient client(espClient);

void MQTT::setup_routes(){
    client.setServer(mqtt_server, mqtt_port);
}
void MQTT::connect_brocker(){
    while(!client.connected()){
        Serial.print("Dang ket noi MQTT...");
        delay(1000);
        
        String ClientID = "ESP32_receive";
        ClientID += String(random(0, 0xffff), HEX);

        if(client.connect(ClientID.c_str(), mqtt_user, mqtt_pass)){
            Serial.println("Da ket noi thanh cong voi HIVEMQ");
            delay(500);

        }
        else{
            Serial.print("Loi ket noi, rc=");
            Serial.print(client.state());
            Serial.println(" Thử lại sau 5 giây...");
            delay(5000);
        }
    }
}
void MQTT::send(){

}