#include "MPU6050Handler.cpp"
#include "BMP280.cpp"
#include "Buzzer-HW508.cpp"

class HandlerSensorsData
{

public:
    int16_t GyroX, GyroY, GyroZ;
    int16_t AccelX, AccelY, AccelZ;
    int16_t GyroAccelTemperature, BMPEnviromentTemperature;
    int16_t PWMMotor1, PWMMotor2, PWMMotor3, PWMMotor4;
    struct bmp280_calib_param params;
    AccellGyroStruct AccellGyro;
    void Calibrate()
    {
        bmp280_get_calib_params(&params);
    }
    void Reset()
    {
        mpu6050_reset();
    }
    void Init()
    {
        bmp280_init();
    }
    void LoadData()
    {
    }
    void StartHandling()
    {
        Run_MPU5060(&AccellGyro);
        float Temperature = 0, Pressure = 0;
        Run_BMP280(1002.58, &Temperature, &Pressure, &params);
    }
    void StopHandling(bool force = false)
    {
    }
};