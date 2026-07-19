#include <Arduino.h>

#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>
#include "../include/PinConfig.h"
#include <MPU.h>
#include "LoRa_d.h"

mpu_6050 mpuSensor(mpu::sda, mpu::sck);
LoraTxDriver lora(Pin_LoRa::sclk, Pin_LoRa::mosi, Pin_LoRa::miso, Pin_LoRa::dido, Pin_LoRa::rst, Pin_LoRa::cs);

void setup(){
    Serial.begin(115200);
    delay(1000);
    Serial.println("Khoi dong thanh cong");

    Serial.println("Bat dau khoi dong chuong trinh");

    mpuSensor.init_mpu_6050();
    mpuSensor.calibration();
    lora.init_sx1278();
}

void loop(){
    data_mpu data = mpuSensor.handle_data();
    Serial.print("Roll: ");
    Serial.print(data.roll);
    Serial.print("  Pitch: ");
    Serial.println(data.pitch);

    lora.Transmission(data);
    delay(100);
}