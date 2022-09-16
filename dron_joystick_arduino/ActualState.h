
#include <Arduino.h>
#include "NonBlockDelay.h"

#ifndef __ACTUAL_STATE_
#define __ACTUAL_STATE_

class ActualState {
private: 
  int DroneTimeout;
  
  NonBlockDelay state_check;
  
public:
  ActualState();

  bool    Inited;
  bool    HasWifi;
  bool    HasDrone;

  int     Depth;
  
  uint8_t LightMode;
  uint8_t SpeedMode;
  bool    Stabilization;
  bool    MotorUnlock;
  bool    TangageControl;
  bool    PhotoMode;
  bool    VideoWriting;
  
  uint8_t DroneBattery; // %
  uint8_t JoystickBattery; // %

  void Loop();
  void ResetDroneTimeout();
};

#endif
