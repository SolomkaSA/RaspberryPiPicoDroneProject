#include "../FileSystem/SDCard.cpp"

struct AltiLongiPoint
{
    char NamePoint[10];
    float Altitude, Longitude;
};
struct StartPointConfig
{
    int CurrentLocationSealLvl, CurrentLocationPressure;
    AltiLongiPoint CurrentPosition;
    AltiLongiPoint SaveNearestPoints[10];
    bool TransmitVideo, SaveObjectDetection, SendCurrentLocation;
};
struct ConfigFile
{
    char StartPointFileName = 'startpointconf.txt';
};
class Configuration
{
private:
    char DefaultConfig = 'config.txt';
    StartPointConfig StartPoint;

public:
    StartPointConfig GetConfig()
    {
        throw new NotImplementedException();
        return StartPoint;
    }
};