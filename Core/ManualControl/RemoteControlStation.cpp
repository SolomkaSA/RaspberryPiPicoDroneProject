#include "Engine.cpp"
#include "../Common/Constants.cpp"
#include "hardware/pwm.h"

class RemoteControlStation
{
public:
    int DefaultPitch, DefaultRoll, DefaultYaw, DefaultClimb,
        MaxPitch, MaxRoll, MaxYaw, MaxSpeedClimb,
        CurrentHight, MinHight, MaxHight,
        DefaultCurrentLocationSeaLvl, DefaultCurrentLocationPressure,
        FullFlightDistanceInMeters, FullFlightTime;
    /*
    #define MOTOR_LEFT_UP_PIN 27
#define MOTOR_LEFT_DOWN_PIN 26
#define MOTOR_RIGHT_UP_PIN 9
#define MOTOR_RIGHT_DOWN_PIN 10
*/

    Engine engine ;
RemoteControlStation()
{

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
    }
    void CalculateCurrentPosition()
    {
    }

    void ThrottleUp()
    {
        Left();
        Right();
    }

    void ThrottleDown()
    {
    }

    void Forward()
    {
        uint slice_num_motor_1 = pwm_gpio_to_slice_num(MOTOR_LEFT_UP_PIN);
        uint chan_motor_1 = pwm_gpio_to_channel(MOTOR_LEFT_UP_PIN);

        uint slice_num_motor_2 = pwm_gpio_to_slice_num(MOTOR_LEFT_DOWN_PIN);
        uint chan_motor_2 = pwm_gpio_to_channel(MOTOR_LEFT_DOWN_PIN);

        engine.SetEngineSpeed(slice_num_motor_1, chan_motor_1, 70);

        engine.SetEngineSpeed(slice_num_motor_2, chan_motor_2, 70);

        sleep_ms(30);
    }

    void Back()
    {
        uint slice_num_motor_1 = pwm_gpio_to_slice_num(MOTOR_LEFT_UP_PIN);
        uint chan_motor_1 = pwm_gpio_to_channel(MOTOR_LEFT_UP_PIN);

        uint slice_num_motor_2 = pwm_gpio_to_slice_num(MOTOR_RIGHT_UP_PIN);
        uint chan_motor_2 = pwm_gpio_to_channel(MOTOR_RIGHT_UP_PIN);

        engine.SetEngineSpeed(slice_num_motor_1, chan_motor_1, 10);

        engine.SetEngineSpeed(slice_num_motor_2, chan_motor_2, 10);

        sleep_ms(30);
    }
    void Left()
    {
        uint slice_num_motor_1 = pwm_gpio_to_slice_num(MOTOR_LEFT_UP_PIN);
        uint chan_motor_1 = pwm_gpio_to_channel(MOTOR_LEFT_UP_PIN);

        uint slice_num_motor_2 = pwm_gpio_to_slice_num(MOTOR_LEFT_DOWN_PIN);
        uint chan_motor_2 = pwm_gpio_to_channel(MOTOR_LEFT_DOWN_PIN);

        engine.SetEngineSpeed(slice_num_motor_1, chan_motor_1, 10);

        engine.SetEngineSpeed(slice_num_motor_2, chan_motor_2, 10);
        sleep_ms(30);
        Right();
    }
    void Right()
    {
        uint slice_num_motor_1 = pwm_gpio_to_slice_num(MOTOR_RIGHT_UP_PIN);
        uint chan_motor_1 = pwm_gpio_to_channel(MOTOR_RIGHT_UP_PIN);

        uint slice_num_motor_2 = pwm_gpio_to_slice_num(MOTOR_RIGHT_DOWN_PIN);
        uint chan_motor_2 = pwm_gpio_to_channel(MOTOR_RIGHT_DOWN_PIN);

        engine.SetEngineSpeed(slice_num_motor_1, chan_motor_1, 10);

        engine.SetEngineSpeed(slice_num_motor_2, chan_motor_2, 10);

        sleep_ms(30);
        Left();
    }
};