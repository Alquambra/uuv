#include "Buttons.h"

#define LONG_CLICK_COUNT  15

Buttons::Buttons() {
    PressState = 0xFFFF;
    
    for(int i = 0; i < BUTTONS_COUNT; i++)
    {
        PressCounter[i] = 0;
        PressEvents[i] = BUTS_NONE;
    }
}

void Buttons::Setup() {
    for(int i = 0; i < BUTTONS_COUNT; i++)
    {
        pinMode(pin.buttons[i], INPUT_PULLUP);
    }
}

void Buttons::Loop() {
    if(state_check.wait(50))
    {
        for(int i = 0; i < BUTTONS_COUNT; i++)
        {
            ProcessButton(i);
        }
    }
}

// Check state of single button
void Buttons::ProcessButton(int Index)
{
    // Detect long and short clicks!
    bool State = digitalRead(pin.buttons[Index]);
    bool OldState = (PressState & (1 << Index)) != 0;

    uint16_t pressed_b = pressed_b | (1 << Index);

    if(State != OldState)
    {
        // Level changed! Active level LOW
        if(!State) // Active
        {
            PressCounter[Index] = 1;
            PressState &= ~(1 << Index);
        }
        else
        {
            if(PressCounter[Index] == LONG_CLICK_COUNT) // LONG CLICK
            {
                OnClick(Index, true);
            }
            else // SHORT CLICK
            {
                OnClick(Index, false);
            }
            PressCounter[Index] = 0;
            PressState |= (1 << Index);
        }
    }
    else
    {
        if(!State) // Active
        {
            if(PressCounter[Index] < LONG_CLICK_COUNT)
            {
                PressCounter[Index]++;
            }
        }
    }
}

void Buttons::OnClick(int Index, bool Long)
{
    PressEvents[Index] = Long ? BUTS_LONG_CLICK : BUTS_SHORT_CLICK;
}

ButtonState Buttons::GetClickState(ButtonFunc Index) 
{
    uint8_t I = Index;
    if(I < BUTTONS_COUNT)
    {
        ButtonState Res = PressEvents[I];
        PressEvents[I] = BUTS_NONE;

        return Res;
    }
    else
        return BUTS_NONE;
}

bool Buttons::GetInputLevel(ButtonFunc Index)
{
    uint8_t I = Index;
    if(I < BUTTONS_COUNT)
    {
        return (PressState & (1 << I)) != 0;
    }
    else
        return false;
}
