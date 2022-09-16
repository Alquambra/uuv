#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Protocol.h"
#include "NonBlockDelay.h"

unsigned int signalLost = 0;

WiFiUDP Udp;
SimplePack sPack;
unsigned int localUdpPort = 1234;
char badPacket[] = "bad_pack";
char noSignal[] = "lost";

char ipSend[] = "192.168.88.1";

bool Connected = false;
uint32_t lasttime = 0;

NonBlockDelay state_check;
  
void SendResponse()
{
    PackFrame packet;
    WifiPacket data;

    packet.num = WIFI_TO_JOYSTICK;
    data.status = 0;
   // data.wifistatus = WiFi.status();
    if (Connected) data.status |= (1 << 0);

    PackPacket(&packet, (uint8_t*)&data, sizeof(WifiPacket));

    // Packet ok! Send
    Serial.write((uint8_t*)&packet, sizeof(WifiPacket) + 5);
}

void setup(){
    Udp.begin(localUdpPort);
    Serial.begin(115200);

    Connected = false;
    WiFi.begin("oceanika000", "12345678");
//    WiFi.begin("FilF", "murmansk13");
    //while (WiFi.status() != WL_CONNECTED){
    //    Serial.println("cant connect");
    //    delay(500);
    //    SendResponse();
    //}
    delay(500);
    SendResponse();
   // Serial.println(WiFi.localIP());
}

void SendErr(char* msg){
  Udp.beginPacket(ipSend, localUdpPort);
  Udp.write(msg);
  Udp.endPacket();
}

void SendPacket(PackFrame* frame) {
    int len = 5 + frame->len;
    
    Udp.beginPacket(ipSend, localUdpPort);
    Udp.write((char*)frame, len);
    Udp.endPacket();
}

void ParseInputPacket(PackFrame * frame)
{
    switch(frame->num)
    {
    case DRONE_TO_JOYSTICK:
        // Wifi status packet
        {
            DTJPacket * dtj = (DTJPacket *)&frame->data[0];

            // Send to arduino
            Serial.write((uint8_t*)frame, frame->len + 5);
        }
        break;
    }
}

void CheckInPackets(){
    int packetSize = Udp.parsePacket();
    if(packetSize)
    {
        uint8_t packet[255];
        
        int len = Udp.read(packet, packetSize);
        if (len > 0)
        {
            sPack.Reset();

            for(int i = 0; i < len; i++)
            {
                if(sPack.Parse(packet[i]) > 0)
                {
                    ParseInputPacket(&sPack.packFrameIn);
                }
            }
        }
    }
}

void loop() {
    if(state_check.wait(500))
    {
        SendResponse();
    }
    if(WiFi.status() == WL_CONNECTED)
    {
        Connected = true;
        CheckInPackets();
        if(Serial.available())
        {
            lasttime = millis();
            signalLost = 0;
            while(Serial.available())
            {
                int ret = sPack.Parse(Serial.read());
                if(ret == 1)
                    SendPacket(&sPack.packFrameIn);
                if(ret == -1)
                    SendErr(badPacket);
//                    SendPacket(&sPack.packFrameIn);
            }            
        }
        else
        {
          SendErr("else");
            if ( signalLost++ > 2000){
                SendErr(noSignal);
                signalLost = 0;
            }
            if(millis() - lasttime > 10)
                sPack.Reset();
        }
    }
    else
    {
        Connected = false;
        int countdown = 100;
        while(Serial.available() && countdown--)
        {
            Serial.read();
        }
        delay(25);
    }
    delay(1);
}
