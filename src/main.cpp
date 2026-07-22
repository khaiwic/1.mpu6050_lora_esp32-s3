#include <Arduino.h>

#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>
#include "../include/PinConfig.h"
#include <MPU.h>
#include "LoRa_d.h"

mpu_6050 mpuSensor(mpu::sda, mpu::scl);
LoraTxDriver lora(Pin_LoRa::sclk, Pin_LoRa::mosi, Pin_LoRa::miso, Pin_LoRa::dido, Pin_LoRa::rst, Pin_LoRa::cs);

void setup(){
    Serial.begin(115200);
    delay(1000);
    Serial.println("Khoi dong thanh cong");

    Serial.println("Bat dau khoi dong chuong trinh");
    Serial.printf("Using MPU6050 I2C pins: SDA=%u, SCL=%u\n", mpu::sda, mpu::scl);

    if (!mpuSensor.init_mpu_6050()) {
        Serial.println("MPU6050 init failed. Check wiring and I2C pins.");
        while (true) {
            delay(1000);
        }
    }

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