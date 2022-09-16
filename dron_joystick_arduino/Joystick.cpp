#include "Joystick.h"
#include "Pins.h"
#include "Protocol.h"

Joystick::Joystick()
{
    LedState = false;
    AfkTimer = millis();
    
    for(int i = 0; i < sizeof(Short)/sizeof(Short[0]); i++) Short[i] = 0;
    for(int i = 0; i < sizeof(Long)/sizeof(Long[0]); i++) Long[i] = 0;
}

void Joystick::Setup()
{
    pinMode(pin.led,  OUTPUT);

    indication.Setup();
    buttons.Setup();
    adc.Setup();
    battery.Setup();
    wifi.Setup();

    wifi.SetStateObject(&state);
#if (ENABLE_DISPLAY == 1)
//    display.Setup();
//    display.SetStateObject(&state);
#endif
   
    delay(100);
    indication.Beep(10, 0xFFFFu, true, true);
}

void Joystick::ProcessButton(ButtonFunc Button, bool Long)
{
    AfkTimer = millis();

#if (OLD_PROTO == 0)
    drone.OnButton(Button, Long);
    switch(Button)
    {
        case BUT_B:
            // Vibro without sound
			if(!Long)
				indication.Beep(5, 0xFFFFu, false, true);
            break;
    }
#endif
}

void Joystick::ProcessButtons()
{
    for(int i = 0; i < BUTTONS_COUNT; i++)
    {
        ButtonFunc Button = (ButtonFunc)i;
        uint8_t State = buttons.GetClickState(Button);
           
        if(State != BUTS_NONE)
        {
            if(State == BUTS_LONG_CLICK)
                Long[i]++;
            else
                Short[i]++;
                
            ProcessButton(Button, State == BUTS_LONG_CLICK);
        }
    }
}


#if (OLD_PROTO == 1)
void Joystick::Send()
{
    PackFrame packet;

    OldPacket data;
    data.analog[0] = adc.getValue(ADC_LY);
    data.analog[1] = adc.getValue(ADC_LX);
    data.analog[2] = adc.getValue(ADC_RX);
    data.analog[3] = adc.getValue(ADC_RY);
    data.analog[4] = 0;
    data.analog[5] = 0;
    data.analog[6] = 0;
    data.analog[7] = battery.GetLevel();
    data.digital = 0xFFFF;
    if(!buttons.GetInputLevel(BUT_A)) data.digital &= ~(1u << 4);
    if(!buttons.GetInputLevel(BUT_B)) data.digital &= ~(1u << 2);
    if(!buttons.GetInputLevel(BUT_C)) data.digital &= ~(1u << 3);
    if(!buttons.GetInputLevel(BUT_D)) data.digital &= ~(1u << 1);
    if(!buttons.GetInputLevel(BUT_LEFT)) data.digital &= ~(1u << 5);
    if(!buttons.GetInputLevel(BUT_RIGHT)) data.digital &= ~(1u << 6);
    
    PackPacket(&packet, (uint8_t*)&data, sizeof(OldPacket));

    // Packet ok! Send
    wifi.Send((uint8_t*)&packet, sizeof(OldPacket) + 5);
}
#else
void Joystick::Send()
{
    const ButtonFunc Order[10] = { BUT_A, BUT_B, BUT_C, BUT_D, BUT_LSW, BUT_RSW, BUT_HOLD, BUT_LED, BUT_LEFT, BUT_RIGHT };
    
    PackFrame packet;
    packet.num = JOYSTICK_TO_DRONE; // JTD
    
    JTDPacket data;
    data.LX = adc.getValue(ADC_LX);
    data.LY = adc.getValue(ADC_LY);
    data.RX = adc.getValue(ADC_RX);
    data.RY = adc.getValue(ADC_RY);

    data.Battery = battery.GetLevel();

    for(int i = 0; i < sizeof(Order)/sizeof(Order[0]); i++)
    {
        uint8_t OID = (uint8_t)Order[i];
        data.Short[i] = Short[OID];
        data.Long[i] = Long[OID];
    }

    uint16_t raw = 0;
    for (int i = 0; i < BUTTONS_COUNT; i++)
    {
      uint8_t OID = (uint8_t)Order[i];
      uint16_t Val = buttons.GetInputLevel(OID) ? 1 : 0;
      raw |= (Val << i);
    }


    data.pressed_buttons = ~raw & 0b0000001111111111;


    // 0: Stabilization on 1: Motor unlocked 2: Photo mode 
    data.State = 0;
    if(drone.getStabilization()) data.State |= (1 << 0); 
    if(drone.getMotorUnlock()) data.State |= (1 << 1); 
    if(drone.getPhotoMode()) data.State |= (1 << 2);
    if(drone.getYawControl()) data.State |= (1 << 3);  
    if(drone.getTangageControl()) data.State |= (1 << 4);

    data.SpeedMode = drone.getSpeedMode();
    data.LightMode = drone.getLightMode();
    
    PackPacket(&packet, (uint8_t*)&data, sizeof(JTDPacket));

    // Packet ok! Send
    wifi.Send((uint8_t*)&packet, sizeof(JTDPacket) + 5);

//    Serial.print(data.RX); Serial.print("\t"); Serial.print(data.RY); Serial.print("\t"); Serial.print(data.LX); Serial.print("\t"); Serial.print(data.LY);
//    Serial.print("\t");
//    Serial.print(data.SpeedMode); Serial.print("\t"); Serial.println(data.LightMode);
}
#endif

void Joystick::CheckBattery()
{
    uint32_t Timer = millis();

    state.JoystickBattery = battery.GetPercent();
    
    // Vibro on low battery
    if(!battery.CheckLevel())
    {
        if(BatteryBeep.wait(20000))
        {
            indication.Beep(24, 0x0F0Fu, true, true);
        }
    }
}

void Joystick::CheckAfk()
{
    uint32_t Timer = millis();

    int32_t Diff = (Timer - AfkTimer) >> 12; // 1024
    if(Diff > TIMER_BEEP_AFK)
    {
        if(AfkBeep.wait(10000))
        {
            indication.Beep(16*4, 0x0FFFu, true, true);
        }
    }
}

void Joystick::Loop()
{
    indication.Loop();
    buttons.Loop();
    adc.Loop();
    battery.Loop();
    wifi.Loop();
    state.Loop();
    Serial.println("Joystick loop");
#if (ENABLE_DISPLAY == 1)
//    display.Loop();
#endif

    if(ProcessingTimer.wait(50))
    {
        ProcessButtons();
        Send();
    }

    if(LedBlink.wait(500))
    {
        // Blink if not connected
        digitalWrite(pin.led, wifi.IsConnected() || LedState);
        LedState = !LedState;
    }
    
    // Check battery level
    CheckBattery();
    // Check afk
    CheckAfk();
}
