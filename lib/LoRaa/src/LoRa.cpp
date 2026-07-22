#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "../../../include/PinConfig.h"
#include "MPU.h"
#include "LoRa_d.h"

unsigned long LoraTxDriver::packetCounter = 0;

LoraTxDriver::LoraTxDriver(int16_t sck, int16_t mosi, int16_t miso, int16_t dido, int16_t rst, int16_t nss){
    _sck = sck;
    _mosi = mosi;
    _miso = miso;
    _nss = nss;
    _dido = dido;
    _rst = rst;
}

void LoraTxDriver::init_sx1278(){
    SPI.begin(_sck, _miso, _mosi, _nss);
    LoRa.setPins(_nss, _rst, _dido);

    if(!LoRa.begin(BRAND)){
        Serial.println("False.....!");
        delay(100);
        while(1);
    }

    Serial.println("___Start Successfully___");

    LoRa.setTxPower(20); //20dBm
    Serial.println("Set Tx(max): 20dBm"); delay(100);

    LoRa.setSignalBandwidth(125E3); // 125MHz
    Serial.println("Config successfully BrandWidth: 125 kHz");

    LoRa.setCodingRate4(5);
    Serial.println("Config coding Rate: 4/5");

    Serial.println(".........................................");
    Serial.println("Perfect!");
    delay(200);
}

void LoraTxDriver::Transmission(const data_mpu& data){
    Serial.println(packetCounter);

    LoRa.beginPacket();
    LoRa.print("pkt=");
    LoRa.print(packetCounter);
    LoRa.print(",roll=");
    LoRa.print(data.roll, 2);
    LoRa.print(",pitch=");
    LoRa.print(data.pitch, 2);
    LoRa.print(",ax=");
    LoRa.print(data.accel_x, 3);
    LoRa.print(",ay=");
    LoRa.print(data.accel_y, 3);
    LoRa.print(",az=");
    LoRa.print(data.accel_z, 3);
    LoRa.print(",gx=");
    LoRa.print(data.gyro_x, 3);
    LoRa.print(",gy=");
    LoRa.print(data.gyro_y, 3);
    LoRa.print(",gz=");
    LoRa.print(data.gyro_z, 3);
    LoRa.print(",temp=");
    LoRa.print(data.tempt_sensor, 2);
    LoRa.endPacket();
    packetCounter++;
}