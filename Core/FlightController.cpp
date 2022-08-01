#include "ChipRP2040/HandlerPicoOne.cpp"
#include "Sensors/HandlerSensorsData.cpp"
#include "FileSystem/SDCard.cpp"
class FlightController
{
private:
    HandlerPicoOne Board;
    HandlerSensorsData Sensors;
    SDCard sdCard;

public:
    bool RunAutoPilot, ForeAttack, SearchingTargets, InFlight;
    // int16_t[] SelectedAutopilot;
    int16_t Pitch, Yaw, Roll;
    int16_t CurrentHight, MinimumHight, MaximumHight, AvgHight;

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
        // sdCard.WriteIntoFile("test.txt", "tetet et etetetet");
        // sdCard.WriteIntoFile("test.txt", "tetet et etetetet");
        // sdCard.WriteIntoFile("test.txt", "tetet et etetetet");
        // sdCard.WriteIntoFile("test.txt", "tetet et etetetet");
        // sdCard.WriteIntoFile("test.txt", "tetet et etetetet");
        // sdCard.WriteIntoFile("test.txt", "tetet et etetetet");
    }
};