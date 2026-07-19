#include <Arduino.h>
#include <Wire.h>
#include <MPU.h>
#include <cmath>
#include "PinConfig.h"

data_mpu dt;

int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;
int16_t temperature;

float accelX_calib = 0, accelY_calib = 0, accelZ_calib = 0;
float gyroX_calib = 0, gyroY_calib = 0, gyroZ_calib= 0;
struct kalman{
    float Q_angle = 0.001f;
    float Q_bias = 0.003f;
    float R_measure = 0.03f;

    float angle = 0.0f;
    float bias = 0.0f;
    float rate = 0.0f;

    float P[2][2] = {{0, 0}, {0, 0}};
    float getAngle(float newAngle, float newRate, float dt){

        //Predict
        rate = newRate - bias;
        angle += dt * rate;

        P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
        P[0][1] -= dt * P[1][1];
        P[1][0] -= dt * P[1][1];
        P[1][1] += Q_bias * dt;   
        
        //Update 
        float S = P[0][0] + R_measure;
        float K[2];
        K[0] = P[0][0] / S;
        K[1] = P[1][0] / S;

        float y = newAngle - angle;
        angle += K[0] *  y;
        bias += K[1] * y;

        float P00_temp = P[0][0];
        float P01_temp = P[0][1];

        P[0][0] -= K[0] * P00_temp;
        P[0][1] -= K[0] * P01_temp;
        P[1][0] -= K[1] * P00_temp;
        P[1][1] -= K[1] * P01_temp;

        return angle;
    }
};

kalman kalmanRoll;
kalman kalmanPitch;

unsigned long timer;

mpu_6050::mpu_6050(uint8_t sda_pin, uint8_t scl_pin) {
    _sda = sda_pin;
    _sck = scl_pin;
}

void mpu_6050::init_mpu_6050(){

    Wire.begin(_sda, _sck);

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission(true);

    Serial.println("-----MPU_6050 San sang hoat dong ngay bay gio"); delay(500);
}

data_mpu mpu_6050::read_data(){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(ACCEL_XOUT_H);
    Wire.endTransmission(false);
    
    Wire.requestFrom(MPU_ADDR, 14, true);

    accelX = Wire.read() << 8 | Wire.read();
    accelY = Wire.read() << 8 | Wire.read();
    accelZ = Wire.read() << 8 | Wire.read();

    temperature = Wire.read() << 8 | Wire.read();

    gyroX = Wire.read() << 8 | Wire.read();
    gyroY = Wire.read() << 8 | Wire.read();
    gyroZ = Wire.read() << 8 | Wire.read();

//     // Mặc định thang đo Gia tốc là +/- 2g -> Chia cho hệ số 16384
//     dt.accel_x = (accelX - dt.calib_ax) / 16384.0;
//     dt.accel_y = (accelY - dt.calib_ay) / 16384.0;
//     dt.accel_z = (accelZ - dt.calib_az) / 16384.0;

//   // Công thức đổi nhiệt độ chuẩn từ Datasheet của MPU-6050
//     dt.tempt_sensor = (temperature / 340.00) + 36.53;

//   // Mặc định thang đo Gyro là +/- 250 độ/giây -> Chia cho hệ số 131
//     dt.gyro_x = (gyroX - dt.calib_gx) / 131.0;
//     dt.gyro_y = (gyroY - dt.calib_gy) / 131.0;
//     dt.gyro_z = (gyroZ - dt.calib_gz) / 131.0;
}
data_mpu mpu_6050::handle_data(){

}
void mpu_6050::calibration(){
    int16_t a, b, c, d, e, f;
    float roll_sum = 0.0f;
    float pitch_sum = 0.0f;
    for(int i = 0; i < samples; i++){
        Wire.beginTransmission(MPU_ADDR);
        Wire.write(ACCEL_XOUT_H);
        Wire.endTransmission(false);

        Wire.requestFrom(MPU_ADDR, 14, true);
        a = Wire.read() << 8 | Wire.read();
        b = Wire.read() << 8 | Wire.read();
        c = Wire.read() << 8 | Wire.read();

        Wire.read() << 8 | Wire.read();

        d = Wire.read() << 8 | Wire.read();
        e = Wire.read() << 8 | Wire.read();
        f = Wire.read() << 8 | Wire.read();

        // Mặc định thang đo Gia tốc là +/- 2g -> Chia cho hệ số 16384
        accelX_calib += a / 16384.0;
        accelY_calib += b / 16384.0;
        accelZ_calib += c / 16384.0;

        gyroX_calib += d / 16384.0;
        gyroY_calib += e / 16384.0;
        gyroZ_calib += f / 16384.0;

        roll_sum += atan2(accelY_calib, accelZ_calib) * 180.0 / M_PI;
        pitch_sum += atan2(-accelX_calib, sqrt(accelY_calib * accelY_calib + accelZ_calib * accelZ_calib))  * 180.0 / M_PI;
    }

    dt.calib_ax = accelX_calib / samples;
    dt.calib_ay = accelY_calib / samples;
    dt.calib_az = accelZ_calib / samples;

    dt.calib_gx = gyroX_calib / samples;
    dt.calib_gy = gyroY_calib / samples;
    dt.calib_gz = gyroZ_calib / samples;

    kalmanRoll.angle = roll_sum / samples;
    kalmanPitch.angle = pitch_sum / samples;
    timer = micros();
}


