#ifndef RECEIVE_H
#define RECEIVE_H

#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include "../../../include/pinconfig.h"

class receive {
public:
    static void initLr();
    static String receive_data();
    static void checking_route();
};

#endif