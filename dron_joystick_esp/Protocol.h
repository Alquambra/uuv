// Communication protocol

#include <stdint.h>

#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

enum PacketNumbers {
  JOYSTICK_TO_DRONE = 0x01,
  DRONE_TO_JOYSTICK = 0x02,
  WIFI_TO_JOYSTICK = 0x03,
  
  OLD_PACKET = 0xAA,
};

struct PackFrame{
  char HEAD1  = 0x77;
  char HEAD2  = 0x66;
  char num  = 0xAA;
  char len  = 0;
  char data[256];
};

struct OldPacket {
  uint16_t analog[8];
  uint16_t digital;
};

struct WifiPacket {
    // 0: connected
    uint8_t status;
   // uint8_t wifistatus;
};

struct DTJPacket {
  // Drone state:
  // 0: Stabilization on 1: Motor unlocked 2: Photo mode 3: Video record on
  uint8_t State;

  // Speed: 0-2
  uint8_t SpeedMode;
  // LED: 0-3
  uint8_t LightMode;
  
  // Drone battery
  uint8_t BatteryValue; // %
};

// Joystick To Drone packet
struct JTDPacket {
  // Joystick pos
  uint16_t LX;
  uint16_t LY;
  uint16_t RX;
  uint16_t RY;

  // Battery
  uint16_t Battery;
  
  // Buttons click state
  // Order: A B C D Lsw Rsw HOLD LED L R
  uint8_t Short[10];
  uint8_t Long[10];

  // Drone state:
  // 0: Stabilization on 1: Motor unlocked 2: Photo mode 
  uint8_t State;

  // Speed: 0-2
  uint8_t SpeedMode;
  // LED: 0-3
  uint8_t LightMode;
};


void PackPacket(PackFrame * frame, uint8_t * Src, uint8_t Length);

class SimplePack {
public:
  SimplePack();
  virtual ~SimplePack();
  int Parse(char byte);
  PackFrame packFrameIn;
  void Reset();
private:
  int state   = 0;
  int lenGet  = 0;
  char crc  = 0;
  int sanity  = 0;
  void Clear();
};

#endif
