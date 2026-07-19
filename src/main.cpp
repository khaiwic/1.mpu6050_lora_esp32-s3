#include <Arduino.h>

#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>
#include "PinConfig.h"
#include <MPU.h>

mpu_6050 mpuSensor(mpu::sda, mpu::sck);

void setup(){
    Serial.begin(115200);
    delay(1000);
    Serial.println("Khoi dong thanh cong");

    Serial.println("Bat dau khoi dong chuong trinh"); 

    mpuSensor.init_mpu_6050();
    mpuSensor.calibration();
}

void loop(){
    data_mpu data = mpuSensor.handle_data();
    Serial.print("Roll: ");
    Serial.print(data.roll);
    Serial.print("  Pitch: ");
    Serial.println(data.pitch);
    delay(100);
}