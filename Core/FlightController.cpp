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
    bool isCalibrateMotors = false;
    // int16_t[] SelectedAutopilot;
    int16_t Pitch, Yaw, Roll;
    int16_t CurrentHight, MinimumHight, MaximumHight, AvgHight;
    int16_t Motor1, Motor2, Motor3, Motor4;
    FlightController()
    {
    }
    void Init()
    {
        isCalibrateMotors = false;
        printf("Start InitBoard!\r\n");
        Board.InitBoard();
        printf("Start Reset!\r\n");
        Sensors.Reset();
        printf("Start Init!\r\n");
        Sensors.Init();
        printf("Start Calibrate!\r\n");
        Sensors.Calibrate();
        printf("Start Calibrate Motors!\r\n");
        RCStation.SetStartPosition();
        printf("END Init!\r\n");
    }
    void Run()
    {
        Sensors.StartHandling();
        // if (Sensors.connection.payload.RightJoystickX == 255 && RCStation.engine.wrap == 0)
        //     RCStation.SetStartPosition(Sensors.connection.payload.RightJoystickX);
        // else if (Sensors.connection.payload.RightJoystickX == 0 && RCStation.engine.wrap == 0)
        //     RCStation.SetStartPosition(Sensors.connection.payload.RightJoystickX);

        if (Sensors.connection.payload.RightJoystickX > 129)
        {
            RCStation.LoadEngine(Sensors.connection.payload.RightJoystickX);
        }
        else if (Sensors.connection.payload.RightJoystickX == 0)
        {
            RCStation.StopEngines();
        }
    }
    void StartMotors()
    {
    }
};