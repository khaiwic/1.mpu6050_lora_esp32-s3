#ifndef MPU_H

#define MP_H
#include <Arduino.h>
#include <Wire.h>
#include "PinConfig.h"

#define MPU_ADDR 0x68
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B

//sample to calib 
#define samples 1000

struct data_mpu{
    //accel data
    float accel_x;
    float accel_y;
    float accel_z;
    //tempt sensor
    float tempt_sensor;
    //gyro data
    float gyro_x;
    float gyro_y;
    float gyro_z;
    //accel after calib
    float calib_ax;
    float calib_ay;
    float calib_az;
    //acccel after calib
    float calib_gx;
    float calib_gy;
    float calib_gz;

};

class mpu_6050{
private:
    uint8_t _sda;
    uint8_t _sck;
public:
    mpu_6050(uint8_t sda_pin, uint8_t scl_pin);
    void init_mpu_6050();
    data_mpu handle_data();
    data_mpu read_data();
    void calibration();
};
#endif