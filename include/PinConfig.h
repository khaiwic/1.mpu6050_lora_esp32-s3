#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <Arduino.h>

namespace Pin_LoRa
{
    // ESP32-C3-Mini mapping requested by the user
    constexpr uint8_t sclk = 4;
    constexpr uint8_t miso = 5;
    constexpr uint8_t mosi = 6;
    constexpr uint8_t cs = 7;
    constexpr uint8_t dido = 2;
    constexpr uint8_t rst = 1;
} // namespace Pin_LoRa

namespace mpu
{
   constexpr uint8_t sda = 8;
   constexpr uint8_t scl = 9;
} // namespace mpu

#endif // PINCONFIG_H
