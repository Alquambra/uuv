#include "DroneState.h"

DroneState::DroneState()
{
    LightMode = 0; // Off
    SpeedMode = 0; // Slowest

    Stabilization = false; // Off
    MotorUnlock = false; // Off
    PhotoMode = false; // Video
    TangageControl = true; // Tangage control
    YawControl = true; // Yaw control
}

void DroneState::OnButton(ButtonFunc Button, bool Long)
{
    PressedButtons |= (1 << Button);
    
    switch(Button)
    {
    case BUT_B:
		if(!Long)
			Stabilization = !Stabilization;
        break;
        
    case BUT_C:
        if(SpeedMode < MAX_SPEED_MODE - 1)
            SpeedMode++;
        else
            SpeedMode = 0;
        break;
        
    case BUT_HOLD:
        MotorUnlock = !MotorUnlock;
        break;
        
    case BUT_LED:
        if(LightMode < MAX_LIGHT_MODE - 1)
            LightMode++;
        else
            LightMode = 0;
        break;
        
    case BUT_RIGHT:
        PhotoMode = !PhotoMode;
        break;

    // Robohand control (long and short clicks)
    case BUT_A:
    case BUT_D:
        break;
    // Start/stop video, take photo (long click)
    case BUT_LEFT:
        break;
    // Unused
    case BUT_LSW:
        TangageControl = !TangageControl;
        break;
    case BUT_RSW:
        YawControl = !YawControl;
        break;
    default:
        break;
    }
}

uint8_t DroneState::getLightMode()
{
    return LightMode;
}

uint8_t DroneState::getSpeedMode()
{
    return SpeedMode;
}

bool    DroneState::getTangageControl()
{
    return TangageControl;
}

bool    DroneState::getYawControl()
{
    return YawControl;
}

bool    DroneState::getStabilization()
{
    return Stabilization;
}

bool    DroneState::getMotorUnlock()
{
    return MotorUnlock;
}

bool    DroneState::getPhotoMode()
{
    return PhotoMode;
}

uint16_t DroneState::getPressedButtons()
{
  return PressedButtons;
}
