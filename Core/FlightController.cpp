#include "ChipRP2040/HandlerPicoOne.cpp"
#include "Sensors/HandlerSensorsData.cpp"
#include "ManualControl/RemoteControlStation.cpp"
#include "FileSystem/SDCard.cpp"

class FlightController
{
private:
    HandlerPicoOne Board;
    HandlerSensorsData Sensors;
    SDCard sdCard;
    RemoteControlStation RCStation;

public:
    bool RunAutoPilot,
        ForeAttack,
        SearchingTargets,
        InFlight;
    // int16_t[] SelectedAutopilot;
    int16_t Pitch, Yaw, Roll;
    int16_t CurrentHight, MinimumHight, MaximumHight, AvgHight;
    int16_t Motor1, Motor2, Motor3, Motor4;
    FlightController()
    {
    }
    void Init()
    {
        printf("Start InitBoard!\r\n");
        Board.InitBoard();
        printf("Start Reset!\r\n");
        Sensors.Reset();
        printf("Start Init!\r\n");
        Sensors.Init();
        printf("Start Calibrate!\r\n");
        Sensors.Calibrate();
        printf("END Init!\r\n");
    }
    void Run()
    {
        Sensors.StartHandling();
    }
};