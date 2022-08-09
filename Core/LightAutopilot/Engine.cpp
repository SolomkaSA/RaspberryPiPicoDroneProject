#include "../Common/InternalLib.cpp"
struct EngineInfo
{
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
    EngineInfo SetEngineSpeed(int speedUpEnginePercent)
    {
        engineInfo.CurrentEngineSpeed = map(speedUpEnginePercent, 0, 1023, 0, 180);
        if (speedUpEnginePercent == 0)
        {
            engineInfo.CurrentEngineSpeed = 0;
        }
        return engineInfo;
    }
};