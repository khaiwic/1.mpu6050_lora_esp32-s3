#ifndef MPU_H

#define MP_H
#include <Arduino.h>
#include <Wire.h>
#include "PinConfig.h"

struct data_mpu{
    int8_t accel_x;
    int8_t accel_y;
    int8_t accel_z;
    int8_t tempt_sensor;
    int8_t gyro_x;
    int8_t gyro_y;
    int8_t gyro_z;

    void hanlde_accel();
    void handle_gyro();
    int8_t filter_accel(int8_t accel_x, int8_t accel_y, int8_t accel_z);
    int8_t filter_gyro(int8_t gyro_x, int8_t gyro_y, int8_t gyro_z);
};
class mpu_6050{
private:
    uint8_t _sda = mpu::sda;
    uint8_t _sck = mpu::sck;
public:
    mpu_6050();
    void init_mpu_6050();
    void hanlde_data();
    void read_data();
};
#endif