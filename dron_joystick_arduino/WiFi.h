#include "ActualState.h"

#include <Arduino.h>

#ifndef __WIFI_H_
#define __WIFI_H

#include "Protocol.h"

class WiFi {
private:
  bool Connected;
  SimplePack parser;
  ActualState * State;
  
  uint32_t lasttime = 0;
  
private:
  void ProcessFrame(PackFrame * frame);
  void ProcessIndication(DTJPacket * dtj);
  
public:
  WiFi();

  void Setup();
  void Loop();

  void SetStateObject(ActualState * state);

  void Send(uint8_t * Data, uint8_t Length);

  bool IsConnected();
};

#endif
