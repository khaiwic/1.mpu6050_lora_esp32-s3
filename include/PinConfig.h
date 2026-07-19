#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <Arduino.h>

namespace Pin_LoRa
{
    constexpr uint8_t sclk = 0;
    constexpr uint8_t miso = 0;
    constexpr uint8_t mosi = 0;
    constexpr uint8_t cs = 0;
    constexpr uint8_t dido = 0;
    constexpr uint8_t rst = 0;
} // namespace Pin_LoRa

namespace mpu
{
   constexpr uint8_t sda = 0;
   constexpr uint8_t sck = 0; 
} // namespace mpu

#endif // PINCONFIG_H
