#include "Engine.cpp"
#include "../Common/Constants.cpp"
#include "hardware/pwm.h"

class RemoteControlStation
{
private:
    uint8_t constatMinForStart = 255;
    uint8_t constatMultiplicationCount = 10;

public:
    int DefaultPitch, DefaultRoll, DefaultYaw, DefaultClimb,
        MaxPitch, MaxRoll, MaxYaw, MaxSpeedClimb,
        CurrentHight, MinHight, MaxHight,
        DefaultCurrentLocationSeaLvl, DefaultCurrentLocationPressure,
        FullFlightDistanceInMeters, FullFlightTime;
    uint slice_num_motor_1_MOTOR_LEFT_UP_PIN,
        chan_motor_1_MOTOR_LEFT_UP_PIN,
        slice_num_motor_2_MOTOR_LEFT_DOWN_PIN,
        chan_motor_2_MOTOR_LEFT_DOWN_PIN,
        slice_num_motor_3_MOTOR_RIGHT_UP_PIN,
        chan_motor_3_MOTOR_RIGHT_UP_PIN,
        slice_num_motor_4_MOTOR_RIGHT_DOWN_PIN,
        chan_motor_4_MOTOR_RIGHT_DOWN_PIN;
    /*
    #define MOTOR_LEFT_UP_PIN 27
#define MOTOR_LEFT_DOWN_PIN 26
#define MOTOR_RIGHT_UP_PIN 9
#define MOTOR_RIGHT_DOWN_PIN 10
*/

    Engine engine;
    RemoteControlStation()
    {

        slice_num_motor_1_MOTOR_LEFT_UP_PIN = pwm_gpio_to_slice_num(MOTOR_LEFT_UP_PIN);
        chan_motor_1_MOTOR_LEFT_UP_PIN = pwm_gpio_to_channel(MOTOR_LEFT_UP_PIN);

        slice_num_motor_2_MOTOR_LEFT_DOWN_PIN = pwm_gpio_to_slice_num(MOTOR_LEFT_DOWN_PIN);
        chan_motor_2_MOTOR_LEFT_DOWN_PIN = pwm_gpio_to_channel(MOTOR_LEFT_DOWN_PIN);

        slice_num_motor_3_MOTOR_RIGHT_UP_PIN = pwm_gpio_to_slice_num(MOTOR_RIGHT_UP_PIN);
        chan_motor_3_MOTOR_RIGHT_UP_PIN = pwm_gpio_to_channel(MOTOR_RIGHT_UP_PIN);

        slice_num_motor_4_MOTOR_RIGHT_DOWN_PIN = pwm_gpio_to_slice_num(MOTOR_RIGHT_DOWN_PIN);
        chan_motor_4_MOTOR_RIGHT_DOWN_PIN = pwm_gpio_to_channel(MOTOR_RIGHT_DOWN_PIN);
    }
    void RunAutopilot()
    {
    }
    void CalibrateAtFlight()
    {
    }
    void CalibrateFlight()
    {
    }
    void SetStartPosition()
    {
        engine.SetEngineSpeed(slice_num_motor_1_MOTOR_LEFT_UP_PIN, chan_motor_1_MOTOR_LEFT_UP_PIN, 1);
        engine.SetEngineSpeed(slice_num_motor_2_MOTOR_LEFT_DOWN_PIN, chan_motor_2_MOTOR_LEFT_DOWN_PIN, 1);
        engine.SetEngineSpeed(slice_num_motor_3_MOTOR_RIGHT_UP_PIN, chan_motor_3_MOTOR_RIGHT_UP_PIN, 1);
        engine.SetEngineSpeed(slice_num_motor_4_MOTOR_RIGHT_DOWN_PIN, chan_motor_4_MOTOR_RIGHT_DOWN_PIN, 1);
    }
    void CalculateCurrentPosition()
    {
    }

    void ThrottleUpDown(int loadCount)
    {
        Left(loadCount);
        Right(loadCount);
    }

    void StartEngines()
    {
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN, 1);
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN, 1);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN, 1);
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN, 1);
    }
    void LoadEngine(int loadCount)
    {
        loadCount = mapOne(loadCount, 130, 255, 0, 100);
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN, loadCount);
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN, loadCount);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN, loadCount);
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN, loadCount);
    }
    void StopEngines()
    {
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN, 0);
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN, 0);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN, 0);
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN, 0);
    }
    void Forward(int loadCount)
    {
        loadCount = mapOne(loadCount, 0, 129, 0, 100);
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN, loadCount);
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN, loadCount);
    }

    void Back(int loadCount)
    {
        loadCount = mapOne(loadCount, 130, 255, 0, 100);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN, loadCount);
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN, loadCount);
    }
    void Left(int loadCount)
    {
        loadCount = mapOne(loadCount, 130, 255, 0, 100);
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN, loadCount);
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN, loadCount);
    }
    void Right(int loadCount)
    {
        loadCount = mapOne(loadCount, 0, 129, 0, 100);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN, loadCount);
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN, loadCount);
    }
};