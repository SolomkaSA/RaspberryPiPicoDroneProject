class AutopilotFollows
{
public:
    bool AmIInFlight = false, EnginesIsRun = false,
         ReturnToStartPoint = false, ReturnToSavePoint = false, ReturnToNearestSavePoint = false,
         MissionInProcess = false, DetectionFoesMission = false,
         NightmareMode = false, FindingMode = false, PatrolMode = false;
    int DefaultTilt, DefaultPitch, DefaultRoll, DefaultYaw, DefaultClimb,
        MaxTilt, MaxPitch, MaxRoll, MaxYaw, MaxClimb,
        CurrentHight, MinHight, MaxHight,
        DefaultCurrentLocationSeaLvl, DefaultCurrentLocationPressure,
        FullFlightDistanceInMeters, FullFlightTime;

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
    void Forward()
    {
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