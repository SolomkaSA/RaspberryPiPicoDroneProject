#include "MPU6050Handler.cpp"
#include "BMP280.cpp"
#include "Buzzer-HW508.cpp"
#include "../../Core/FileSystem/SDCard.cpp"
#include "../../Core/DataAndVideo/CommunicationWIFI.cpp"

class HandlerSensorsData
{
public:
    float GyroXRoll, GyroYPitch, GyroZYaw;
    float AccelX, AccelY, AccelZ;
    float GyroAccelTemperature, EnviromentTemperature, Pressure;
    float PWMMotor1, PWMMotor2, PWMMotor3, PWMMotor4;
    bool RCEnabled = false;
    struct bmp280_calib_param params;
    CommunicationWIFI connection;
    SDCard sdCard;
    void Calibrate()
    {
        bmp280_get_calib_params(&params);
    }
    void Reset()
    {
    }
    void Init()
    {
        sdCard.InitSDInstance();
        sdCard.CreateEmptyFile("test.txt");
        sdCard.CreateEmptyFile("test2.txt");
        sdCard.CreateEmptyFile("Solomka.txt");
        MPU6050_Init();
        bmp280_init();
        while (!RCEnabled)
        {
            RCEnabled = connection.setup();
        }
    }
    void LoadData()
    {
    }
    void StartHandling()
    {
        // rem commenting block below if you afraid about endless loop
        // when RC in some time would broken maybe
        // connection.loop();
        // and commented below block between RCEnable and Setup
        if (RCEnabled)
            connection.loop();
        else
            RCEnabled = connection.setup();
        MPU6050_YawPitchRoll(&GyroZYaw, &GyroYPitch, &GyroXRoll, &GyroAccelTemperature);
        Run_BMP280(1002.58, &EnviromentTemperature, &Pressure, &params);

        char array[5000];
        sprintf(array, "GyroZYaw %.3f, &GyroYPitch %.3f, GyroXRoll %.3f, &GyroAccelTemperature %.3f, &EnviromentTemperature %.3f, &Pressure %.3f \r\n", GyroZYaw, GyroYPitch, GyroXRoll, GyroAccelTemperature, EnviromentTemperature, Pressure);
        printf(array);

        sdCard.WriteIntoFile("test.txt", array);
    }
    void StopHandling(bool force = false)
    {
    }
};