                                                                     // Voltage measurement

#include <stdint.h>
#include <Arduino.h>

#ifndef __ADC_H_
#define __ADC_H_

#include "Pins.h"
#include "NonBlockDelay.h"
#include "ab_filter.h"

// pins.analog
enum AdcChannel {
  ADC_LX = 0,
  ADC_RX = 1,
  ADC_RY = 2,
  ADC_LY = 3
};


class Adc {
private:
  uint16_t Result[ANALOG_COUNT];
  float calibration[4] = {0.862, 0.962, 1.064, 0.980};
  int lower_limit = 97, higher_limit = 927;
//  AB_Filter *filter[ANALOG_COUNT];
  
  NonBlockDelay state_check;
    
public:
  Adc();

  void Setup();
  void Loop();
  static int filter(int value, float calibration_kf, int lower_limit, int higher_limit);

  // Прочитать фильтрованное значение с канала
  uint16_t getValue(AdcChannel Channel);
};

#endif
