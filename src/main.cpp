#include <Arduino.h>

#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>
#include "PinConfig.h"



void setup(){
    Serial.begin(115200);
    delay(1000);
    Serial.println("Khoi dong thanh cong");

    Serial.println("Bat dau khoi dong chuong trinh"); 

    //Start MPU

}