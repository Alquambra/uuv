#include "ActualState.h"

ActualState::ActualState()
{
    LightMode = 0; // Off
    SpeedMode = 0; // Slowest

    Depth = 0;

    Inited = true;

    Stabilization = false; // Off
    MotorUnlock = false; // Off
    PhotoMode = false; // Video
    TangageControl = false;
    VideoWriting = false;

    HasWifi = false;
    HasDrone = false;
}

void ActualState::Loop()
{
    if(state_check.wait(100))
    {
        if(DroneTimeout < 100) // 10 sec
        {
            DroneTimeout++;
        }
        else
        {
            HasDrone = false;
        }
    }
}

void ActualState::ResetDroneTimeout()
{
    HasDrone = true;
    DroneTimeout = 0;
}
