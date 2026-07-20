#ifndef MPU_H
#define MPU_H
#include <Arduino.h>
#include <Wire.h>

#define MPU_ADDR 0x68
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

//sample to calib 
#define samples 1000

struct kalman{
    float Q_angle = 0.001f;
    float Q_bias = 0.003f;
    float R_measure = 0.03f;

    float angle = 0.0f;
    float bias = 0.0f;
    float rate = 0.0f;

    float P[2][2] = {{0, 0}, {0, 0}};
    float getAngle(float newAngle, float newRate, float dt);
};

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
    //gyro after calib
    float calib_gx;
    float calib_gy;
    float calib_gz;
    //angle data
    float roll;
    float pitch;
};

class mpu_6050{
private:
    uint8_t _sda;
    uint8_t _sck;
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
    int16_t temperature;

    float accelX_calib;
    float accelY_calib;
    float accelZ_calib;
    float gyroX_calib;
    float gyroY_calib;
    float gyroZ_calib;

    data_mpu dt;
    kalman kalmanRoll;
    kalman kalmanPitch;
    unsigned long timer;
public:
    mpu_6050(uint8_t sda_pin, uint8_t scl_pin);
    bool init_mpu_6050();
    data_mpu handle_data();
    data_mpu read_data();
    void calibration();
};
#endif