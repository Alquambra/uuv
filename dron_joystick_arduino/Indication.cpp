#include "Indication.h"
#include "Pins.h"

Indication::Indication()
{
    SoundState = false;
    VibroState = false;
    OnIterations = 0;
    MaskBit = 0;
    SoundMask = 0;
}

void Indication::Setup()
{
    pinMode(pin.vibro, OUTPUT);
    pinMode(pin.sound, OUTPUT);

    // Default state
    noTone(pin.sound);
    analogWrite(pin.vibro, 0);
}

void Indication::Loop()
{
    if(state_check.wait(20))
    {
        if(OnIterations > 0)
        {
            bool State = ((SoundMask >> MaskBit) & 0x01) != 0;
          
            OnIterations--;
            MaskBit = (MaskBit + 1) & 0x0F;
            
            SetVibroState(VibroEnable && State);
            SetSoundState(SoundEnable && State);
        }
        else
        {
            SetVibroState(false);
            SetSoundState(false);
        }
    }
}

void Indication::SetSoundState(bool State)
{
    if(SoundState != State)
    {
        if(State)
            tone(pin.sound, 250);
        else
            noTone(pin.sound);
        
        SoundState = State;
    }
}

void Indication::SetVibroState(bool State)
{
    if(VibroState != State)
    {
        if(State)
            analogWrite(pin.vibro, 200);
        else
            analogWrite(pin.vibro, 0);

        VibroState = State;
    }
}

void Indication::Beep(uint8_t Length, uint16_t Mask, bool Sound, bool Vibro)
{
    SoundEnable = Sound;
    VibroEnable = Vibro;

    SoundMask = Mask;
    MaskBit = 0;
    
    OnIterations = Length;
}
