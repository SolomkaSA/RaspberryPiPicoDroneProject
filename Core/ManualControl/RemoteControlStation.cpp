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
           uint slice_num_motor_1_MOTOR_LEFT_UP_PIN, 
                chan_motor_1_MOTOR_LEFT_UP_PIN ,
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

    Engine engine ;
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
        engine.SetEngineSpeed(slice_num_motor_1_MOTOR_LEFT_UP_PIN, chan_motor_1_MOTOR_LEFT_UP_PIN, 3);
        engine.SetEngineSpeed(slice_num_motor_2_MOTOR_LEFT_DOWN_PIN, chan_motor_2_MOTOR_LEFT_DOWN_PIN, 3);  
        engine.SetEngineSpeed(slice_num_motor_3_MOTOR_RIGHT_UP_PIN, chan_motor_3_MOTOR_RIGHT_UP_PIN, 3);
        engine.SetEngineSpeed(slice_num_motor_4_MOTOR_RIGHT_DOWN_PIN, chan_motor_4_MOTOR_RIGHT_DOWN_PIN, 3);  
      
    }
    void CalculateCurrentPosition()
    {
    }

    void ThrottleUp()
    {
        Left();
        Right();
    }

    void StartEngines()
    {   
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN,1);  
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN,1);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN,1);  
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN,1);
    }
      void LoadEngine(int l)
    {
        int loadCount = 1*l;
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN,loadCount); 
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN,loadCount);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN,loadCount);  
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN,loadCount);
    }
    void StopEngines()
    {
        engine.EngineSpeed(MOTOR_LEFT_UP_PIN,0);  
        engine.EngineSpeed(MOTOR_LEFT_DOWN_PIN,0);
        engine.EngineSpeed(MOTOR_RIGHT_UP_PIN,0);  
        engine.EngineSpeed(MOTOR_RIGHT_DOWN_PIN,0);
    }
    
  void ThrottleDown()
    {
         
    }
    void Forward()
    { 
       engine.EngineSpeed(MOTOR_LEFT_UP_PIN,6);
    }

    void Back()
    { 
    }
    void Left()
    {  
    }
    void Right()
    { 
    }
};