#include <Arduino.h>
#include <Wire.h>
#include <MPU.h>
#include <cmath>

mpu_6050::mpu_6050(uint8_t sda_pin, uint8_t scl_pin)
    : _sda(sda_pin),
      _sck(scl_pin),
      accelX(0),
      accelY(0),
      accelZ(0),
      gyroX(0),
      gyroY(0),
      gyroZ(0),
      temperature(0),
      accelX_calib(0),
      accelY_calib(0),
      accelZ_calib(0),
      gyroX_calib(0),
      gyroY_calib(0),
      gyroZ_calib(0),
      timer(0) {
}

bool mpu_6050::init_mpu_6050(){
    Wire.begin(_sda, _sck);
    Wire.setClock(400000L);
    delay(100);

    Wire.beginTransmission(MPU_ADDR);
    uint8_t error = Wire.endTransmission();
    if (error != 0) {
        Serial.printf("MPU6050 not detected at 0x%02X on SDA=%u/SCL=%u (error=%u)\n", MPU_ADDR, _sda, _sck, error);
        return false;
    }

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    error = Wire.endTransmission();
    if (error != 0) {
        Serial.printf("MPU6050 wake-up failed (error=%u)\n", error);
        return false;
    }

    Serial.printf("MPU6050 ready on SDA=%u/SCL=%u\n", _sda, _sck);
    delay(500);
    return true;
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

    dt.accel_x = (accelX / 16384.0f) - dt.calib_ax;
    dt.accel_y = (accelY / 16384.0f) - dt.calib_ay;
    dt.accel_z = (accelZ / 16384.0f) - dt.calib_az;
    dt.tempt_sensor = (temperature / 340.0f) + 36.53f;
    dt.gyro_x = (gyroX / 131.0f) - dt.calib_gx;
    dt.gyro_y = (gyroY / 131.0f) - dt.calib_gy;
    dt.gyro_z = (gyroZ / 131.0f) - dt.calib_gz;

    return dt;
}

data_mpu mpu_6050::handle_data(){
    data_mpu data = read_data();
    unsigned long now = micros();
    float dt_sec = 0.001f;
    if (timer != 0) {
        dt_sec = (now - timer) / 1000000.0f;
    }
    timer = now;

    data.roll = atan2(data.accel_y, data.accel_z) * 180.0f / M_PI;
    data.pitch = atan2(-data.accel_x, sqrt(data.accel_y * data.accel_y + data.accel_z * data.accel_z)) * 180.0f / M_PI;
    data.roll = kalmanRoll.getAngle(data.roll, data.gyro_x, dt_sec);
    data.pitch = kalmanPitch.getAngle(data.pitch, data.gyro_y, dt_sec);

    return data;
}

float kalman::getAngle(float newAngle, float newRate, float dt){
    //Predict
    rate = newRate - bias;
    angle += dt * rate;

    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    //Update
    float S = P[0][0] + R_measure;
    float K[2] = {P[0][0] / S, P[1][0] / S};
    float y = newAngle - angle;
    angle += K[0] * y;
    bias += K[1] * y;

    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;

    return angle;
}

void mpu_6050::calibration(){
    int16_t a, b, c, d, e, f;
    float roll_sum = 0.0f;
    float pitch_sum = 0.0f;

    for(int i = 0; i < samples; i++){
        Wire.beginTransmission(MPU_ADDR);
        Wire.write(ACCEL_XOUT_H);
        Wire.endTransmission(false);
        Wire.requestFrom(static_cast<uint8_t>(MPU_ADDR), static_cast<uint8_t>(14), true);

        a = Wire.read() << 8 | Wire.read();
        b = Wire.read() << 8 | Wire.read();
        c = Wire.read() << 8 | Wire.read();
        Wire.read() << 8 | Wire.read();
        d = Wire.read() << 8 | Wire.read();
        e = Wire.read() << 8 | Wire.read();
        f = Wire.read() << 8 | Wire.read();

        float ax = a / 16384.0f;
        float ay = b / 16384.0f;
        float az = c / 16384.0f;
        float gx = d / 131.0f;
        float gy = e / 131.0f;
        float gz = f / 131.0f;

        accelX_calib += ax;
        accelY_calib += ay;
        accelZ_calib += az;
        gyroX_calib += gx;
        gyroY_calib += gy;
        gyroZ_calib += gz;

        roll_sum += atan2(ay, az) * 180.0f / M_PI;
        pitch_sum += atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / M_PI;
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


