#include "MPU6050Handler.cpp"
#include "BMP280.cpp"
#include "Buzzer-HW508.cpp"

class HandlerSensorsData
{

public:
    float GyroXRoll, GyroYPitch, GyroZYaw;
    float AccelX, AccelY, AccelZ;
    float GyroAccelTemperature, EnviromentTemperature, Pressure;
    float PWMMotor1, PWMMotor2, PWMMotor3, PWMMotor4;
    struct bmp280_calib_param params;
    void Calibrate()
    {
        bmp280_get_calib_params(&params);
    }
    void Reset()
    {
    }
    void Init()
    {
        MPU6050_Init();
        bmp280_init();
    }
    void LoadData()
    {
    }
    void StartHandling()
    {
        MPU6050_YawPitchRoll(&GyroZYaw, &GyroYPitch, &GyroXRoll, &GyroAccelTemperature);
        Run_BMP280(1002.58, &EnviromentTemperature, &Pressure, &params);

        printf("GyroZYaw %.3f, &GyroYPitch %.3f, GyroXRoll %.3f, &GyroAccelTemperature %.3f, &EnviromentTemperature %.3f, &Pressure %.3f",
               GyroZYaw, GyroYPitch, GyroXRoll, GyroAccelTemperature, EnviromentTemperature, Pressure);
    }
    void StopHandling(bool force = false)
    {
    }
};