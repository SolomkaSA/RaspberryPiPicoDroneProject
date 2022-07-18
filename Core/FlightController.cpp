#include "ChipRP2040/HandlerPicoOne.cpp"
#include "Sensors/HandlerSensorsData.cpp"

class FlightController
{
private:
    HandlerPicoOne Board;
    HandlerSensorsData Sensors;

public:
    bool RunAutoPilot, ForeAttack, SearchingTargets, InFlight;
    // int16_t[] SelectedAutopilot;
    int16_t Pitch, Yaw, Roll;
    int16_t CurrentHight, MinimumHight, MaximumHight, AvgHight;

    void Init()
    {
    }
    void Run()
    {
    }
};