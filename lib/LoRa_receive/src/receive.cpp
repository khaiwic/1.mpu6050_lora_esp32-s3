#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include "../../../include/pinconfig.h"
#include "receive.h"

#define BAND 433E6 

void receive::initLr(){
    SPI.begin(LoRaPin::sck, LoRaPin::miso, LoRaPin::mosi, LoRaPin::nss);
    LoRa.setPins(LoRaPin::nss, LoRaPin::rst, LoRaPin::dido);

    if(!LoRa.begin(BAND)){
        Serial.println("[LoRa] Khoi dong THAT BAI! Kiem tra lai day noi.");
        while(1){
            delay(1000); 
        }
    }
    Serial.println("[LoRa] Khoi tao phan cung thanh cong!");

    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125E3); // 125 kHz tiêu chuẩn
    LoRa.setCodingRate4(5);

    Serial.println("LoRa Rx dang lang nghe song....");
    Serial.println("...............................");
}

String receive::receive_data(){
    String receiveData = "";
    int packetSize = LoRa.parsePacket();

    // Dùng IF kiểm tra thay vì WHILE
    if(packetSize){
        while(LoRa.available()){
            receiveData += (char)LoRa.read();
        }
        
        Serial.print("Nhan duoc tu LoRa: ");
        Serial.println(receiveData);

        checking_route();
    }

    return receiveData;
}

void receive::checking_route(){
    Serial.println("Kiem tra signal___________");
    Serial.print("Suc manh tin hieu (RSSI): ");
    Serial.print(LoRa.packetRssi());
    Serial.println(" dBm");

    Serial.print("Ty so tin hieu tren nhieu (SNR): ");
    Serial.print(LoRa.packetSnr());
    Serial.println(" dB");
    Serial.println("...............................");
}