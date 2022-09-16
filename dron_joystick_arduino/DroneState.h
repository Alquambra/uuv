
#ifndef __DRONE_STATE_
#define __DRONE_STATE_

#include "Buttons.h"

#define MAX_SPEED_MODE 3 // 0-slow 1-faster 2-fastest
#define MAX_LIGHT_MODE 4 // 0-off, 1-50% 2-75% 3-100%


class DroneState {
private: 
  uint8_t LightMode;
  uint8_t SpeedMode;
  bool    Stabilization;
  bool    MotorUnlock;
  bool    PhotoMode;
  bool    TangageControl;
  bool    YawControl;
  uint16_t PressedButtons;
  
public:
  DroneState();

  void OnButton(ButtonFunc Button, bool Long);

  uint8_t getLightMode();
  uint8_t getSpeedMode();
  bool    getStabilization();
  bool    getTangageControl();
  bool    getYawControl();
  bool    getMotorUnlock();
  bool    getPhotoMode();
  uint16_t getPressedButtons();
};

#endif
