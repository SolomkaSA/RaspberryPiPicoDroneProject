#include "../Common/InternalLib.cpp"
struct BatteryInfo
{
    float CurrentVoltage,
        MinVoltage,
        CurrentCapacity,
        FullCapacity;
};

class Battery
{
public:
    BatteryInfo btInfo;
    Battery(int maxEngineSpeed, bool runWithChek = true)
    {
    }

    BatteryInfo GetBatteryInfo()
    {
        return btInfo;
    }
};