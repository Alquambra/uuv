#include "WiFi.h"
#include "Pins.h"

#include <Wire.h> 

WiFi::WiFi()
{
    Wire.begin();
    
    Connected = false;

    State = 0;
}

void WiFi::Setup()
{
    Serial.begin(115200);
}

void WiFi::ProcessIndication(DTJPacket * dtj) {
  uint8_t Raw[10];
  
  // TEST RECEIVE
  bool StabEnabled = (dtj->State & 0x01) != 0;
  bool MotorEnabled = (dtj->State & 0x02) != 0;
  bool PhotoMode = (dtj->State & 0x04) != 0;
  bool VideoWriting = (dtj->State & 0x08) != 0;
  bool TangageControl = (dtj->State & 0x10) != 0;

  if(State)
  {
      State->Stabilization = StabEnabled;
      State->MotorUnlock = MotorEnabled;
      
      State->PhotoMode = PhotoMode;
      State->LightMode = dtj->LightMode;
      State->SpeedMode = dtj->SpeedMode;
      State->VideoWriting = VideoWriting;
      State->TangageControl = TangageControl;
      
      State->DroneBattery = dtj->BatteryValue;

      State->ResetDroneTimeout();
  }
  /*
  memset(Raw, 0, sizeof(Raw));

  Raw[0] = MotorEnabled;
  Raw[1] = StabEnabled;

  Wire.beginTransmission(0x12);  // начинаем процедуру передачи устройству с адресом #44 (0x2c)
                                 // адрес устройства указан в даташите
  Wire.write(Raw, sizeof(Raw));  // отправляем байт данных
  Wire.endTransmission();        // завершаем процедуру передачи
  */
}

void WiFi::SetStateObject(ActualState * state)
{
    State = state;
}

void WiFi::ProcessFrame(PackFrame * frame)
{
    switch(frame->num)
    {
    case WIFI_TO_JOYSTICK:
        // Wifi status packet
        {
            WifiPacket * wifi = (WifiPacket *)&frame->data[0];

            Connected = (wifi->status & 0x01) != 0;

            if(State)
                State->HasWifi = Connected;

            /*{
                uint8_t Raw[10];
                memset(Raw, 0, sizeof(Raw));

                Raw[0] = 0; // Address
                Raw[1] = Connected ? 255 : 0;
                Wire.beginTransmission(0x12);  // начинаем процедуру передачи устройству с адресом #44 (0x2c)
                                               // адрес устройства указан в даташите
                Wire.write(Raw, sizeof(Raw));  // отправляем байт данных
                Wire.endTransmission();        // завершаем процедуру передачи
            }*/
        }
        break;
    case DRONE_TO_JOYSTICK:
        // Drone to joystick
        {
            DTJPacket * dtj = (DTJPacket *)&frame->data[0];

            // Send to i2c-status viewer
            ProcessIndication(dtj);
        }
        break;
    }
}

void WiFi::Loop()
{
    while (Serial.available() > 0) {
        lasttime = millis();
        int ret = parser.Parse(Serial.read());
        if(ret == 1)
        {
            ProcessFrame(&parser.packFrameIn);
        }
    }

    if(millis() - lasttime > 10)
        parser.Reset();
}

bool WiFi::IsConnected()
{
    return Connected;
}

void WiFi::Send(uint8_t * Data, uint8_t Length)
{

//    JTDPacket packet;
//    memcpy(&packet, Data, sizeof(packet));
//    Serial.print(packet.RX); Serial.print("\t"); Serial.print(packet.RY); Serial.print("\t"); Serial.print(packet.LX); Serial.print("\t"); Serial.print(packet.LY);
//    Serial.print("\t");
//    Serial.print(packet.SpeedMode); Serial.print("\t"); Serial.println(packet.LightMode);
    
    Serial.write((char*)Data, Length);
}
