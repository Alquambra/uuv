#include "Adc.h"

Adc::Adc()
{
    for(int i = 0; i < ANALOG_COUNT; i++)
    {
        Result[i] = 0;
//        filter[i] = new AB_Filter(0.1f, 0.05f);
    }
}

void Adc::Setup()
{
    for(int i = 0; i < ANALOG_COUNT; i++)
    {
        pinMode(pin.analog[i], INPUT);
    }
}

void Adc::Loop()
{
    if(state_check.wait(20))
    {
        for(int i = 0; i < ANALOG_COUNT; i++)
        {
//            Result[i] = filter[i]->Filter(analogRead(pin.analog[i]));
              Result[i] = Adc::filter(analogRead(pin.analog[i]), calibration[i], lower_limit, higher_limit);
        }
    }
}

static int Adc::filter(int value, float calibration_kf, int lower_limit, int higher_limit)
{
    value = (int) (value * calibration_kf);
    value = constrain(value, lower_limit, higher_limit);
    value = map(value, 96, 927, 0, 1023);
    return value;
}

uint16_t Adc::getValue(AdcChannel Channel)
{
    uint8_t Ch = Channel;

    if(Ch < ANALOG_COUNT)
    {
        return Result[Ch];
    }
    else
        return 0;
}
