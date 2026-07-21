#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include "../../../include/pinconfig.h"
#include "receive.h"

#define BAND 144000000L

void receive::initLr(){
    SPI.begin(LoRaPin::sck, LoRaPin::miso, LoRaPin::mosi, LoRaPin::nss);
    LoRa.setPins(LoRaPin::nss, LoRaPin::rst, LoRaPin::dido);

    if(!LoRa.begin(BAND)){
        Serial.println("LoRa init failed");
        while(1){
        }
    }
    Serial.println("Setup successfully!");
}