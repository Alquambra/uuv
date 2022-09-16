
#include "BatteryCheck.h"
#include "Pins.h"

BatteryCheck::BatteryCheck()
{
    Level = 0;
    filter = new AB_Filter(0.1f, 0.05f);
}

void BatteryCheck::Setup()
{
    pinMode(pin.battery, INPUT);
}

void BatteryCheck::Loop()
{
    if(state_check.wait(20))
    {
        Level = filter->Filter(analogRead(pin.battery));
    }
}

// Проверка напряжения, если ОК, то true
bool BatteryCheck::CheckLevel()
{
    return  (Level > MIN_BATTERY_LEVEL);
}

// Вернуть текущий уровень напряжения
uint16_t BatteryCheck::GetLevel()
{
    return Level;
}

// Вернуть текущий уровень заряда
uint8_t BatteryCheck::GetPercent()
{
    return Level;
}
