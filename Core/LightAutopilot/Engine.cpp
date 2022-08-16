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
    Engine(int maxEngineSpeed, bool runWithChek = true)
    {
        engineInfo.maxEngineSpeed = maxEngineSpeed;
    }
    EngineInfo SetEngineSpeed(uint slice_num, uint chan, int speedUpEnginePercent)
    {
        engineInfo.CurrentEngineSpeed = map(speedUpEnginePercent, 0, 1023, 0, 180);
        if (speedUpEnginePercent == 0)
        {
            engineInfo.CurrentEngineSpeed = 0;
        }
        pwm_set_freq_duty(slice_num, chan, 50, 75);
        pwm_set_enabled(slice_num, true);
        return engineInfo;
    }
};