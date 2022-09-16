                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              // Vibro and sound indication

#include <Arduino.h>

#ifndef __INDICATION_H_
#define __INDICATION_H_

#include "NonBlockDelay.h"

class Indication {
private:
  int OnIterations;
  
  bool SoundState;
  bool VibroState;
  
  bool SoundEnable;
  bool VibroEnable;

  uint16_t SoundMask;
  uint8_t  MaskBit;
  
  NonBlockDelay state_check;
  
private:
  // Switch sound state
  void SetSoundState(bool State);
  // Switch vibro state
  void SetVibroState(bool State);
  
public:
  Indication();

  void Setup();
  void Loop();

  // Enable signal with mask by sound or/and vibro
  void Beep(uint8_t Length, uint16_t Mask, bool Sound, bool Vibro);
};

#endif
