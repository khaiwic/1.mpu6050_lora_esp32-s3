#ifndef LORA_TX_DRIVER_H
#define LORA_TX_DRIVER_H

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "../../../include/PinConfig.h"
#include <MPU.h>

#define BRAND 433E6

class LoraTxDriver{
private:
    static unsigned long packetCounter;
    int16_t _sck;
    int16_t _mosi;
    int16_t _miso;
    int16_t _dido;
    int16_t _rst;
    int16_t _nss;
public:
    LoraTxDriver(int16_t sck, int16_t mosi, int16_t miso, int16_t dido, int16_t rst, int16_t nss);

    void init_sx1278();
    void Transmission(const data_mpu& data);
};
#endif