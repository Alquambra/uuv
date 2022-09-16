#include <stdint.h>
#include <Arduino.h>

#ifndef __BATTERY_CHECK_H_
#define __BATTERY_CHECK_H_

#include "ab_filter.h"
#include "NonBlockDelay.h"

#define MIN_BATTERY_LEVEL 180

class BatteryCheck {
private:
  uint16_t Level;
  NonBlockDelay state_check;
  AB_Filter *filter;
  
public:
  BatteryCheck();

  void Setup();
  void Loop();

  // Проверка напряжения, если ОК, то true
  bool CheckLevel();
  // Вернуть текущий уровень напряжения
  uint16_t GetLevel();
  
  // Вернуть текущий уровень заряда
  uint8_t GetPercent();
};

#endif
