#include "../Common/InternalLib.cpp"
#include "hardware/pwm.h"

struct EngineInfo
{
    /// minimum speed 1000us
    int CurrentEngineSpeed, CurrentPercentageEngineSpeed,
        maxEngineSpeed;
};

class Engine
{
public:
    EngineInfo engineInfo;
    uint32_t wrap;
    Engine()
    {
        engineInfo.maxEngineSpeed = 1100;
    }
    Engine(int maxEngineSpeed, bool runWithChek = true)
    {
        engineInfo.maxEngineSpeed = maxEngineSpeed;
    }

    EngineInfo SetEngineSpeed(uint slice_num, uint chan, int speedUpEnginePercent)
    {
        engineInfo.CurrentEngineSpeed = mapOne(speedUpEnginePercent, 0, 100, 0, 100);
        if (speedUpEnginePercent == 0)
        {
            engineInfo.CurrentEngineSpeed = 0;
        }
        wrap = pwm_set_freq_duty(slice_num, chan, 50, speedUpEnginePercent);

        printf("wrap %0.d engineInfo.CurrentEngineSpeed %0.d speedUpEnginePercent: %0.d\r\n", wrap, engineInfo.CurrentEngineSpeed, speedUpEnginePercent);
        return engineInfo;
    }
    void EngineSpeed(uint Engine_PIN_GPO, int speedUpEnginePercent)
    {
        // pwm_set_gpio_level(Engine_PIN_GPO, wrap * speedUpEnginePercent / 100);
        // printf("wrap %0.d wrap * speedUpEnginePercent / 100: %0.d  speedUpEnginePercent:%d\r\n", wrap, wrap * speedUpEnginePercent / 100, speedUpEnginePercent);

        long returnedSpeedMotor = mapOne(speedUpEnginePercent, 0, 100, 3600, 6400);
        pwm_set_gpio_level(Engine_PIN_GPO, returnedSpeedMotor);
        printf("wrap %0.d returnedSpeedMotor: %0.d  speedUpEnginePercent:%d\r\n", wrap, returnedSpeedMotor, speedUpEnginePercent);
    }
};