#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "../../../include/pinconfig.h"
#include "WF.h"


class MQTT{
public:
    static void setup_routes();
    static void connect_brocker();
    static void send();
};

#endif