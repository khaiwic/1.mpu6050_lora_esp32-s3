#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <Arduino.h>

namespace Pin_LoRa
{
    constexpr uint8_t sclk = 9;
    constexpr uint8_t miso = 10;
    constexpr uint8_t mosi = 11;
    constexpr uint8_t cs = 12;
    constexpr uint8_t dido = 14;
    constexpr uint8_t rst = 13;
} // namespace Pin_LoRa

namespace mpu
{
   constexpr uint8_t sda = 16;
   constexpr uint8_t sck = 17; 
} // namespace mpu

#endif // PINCONFIG_H
