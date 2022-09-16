//#include "Display.h"
//
//// Need: LiquidCrystal I2C
//// 
//#include <LiquidCrystal_I2C.h>
//
//Display::Display()
//{
//    State = 0;
//}
//
//void Display::SetStateObject(ActualState * state)
//{
//    State = state;
//}
//
//void Display::Update()
//{
//    
//}
//
//void Setup()
//{
//  
//}
//
//void Display::Loop()
//{
//    if(state_check.wait(100))
//    {
//        Update();
//    }
//}
//
//Display0805i2c::Display0805i2c()
//{
//    lcd = 0;
//}
//
//Display0805i2c::~Display0805i2c()
//{
//    if(lcd)
//    {
//        delete lcd;
//        lcd = 0;
//    }
//}
//
//void Display0805i2c::Setup()
//{
//    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
//    lcd->init();
//    lcd->backlight();
//
//    DrawLogo();
//}
//
//void Display0805i2c::DrawLogo()
//{
//    lcd->setCursor(0, 0);
//    lcd->print("   Oceanika   ");
//    lcd->setCursor(0, 1);
//    lcd->print("   Drone v1   ");
//}
//
//void Display0805i2c::Update()
//{
//    if(lcd)
//    {
//
//        if(State)
//        {
//            char Line[17];
//            // Line 1:
//            strcpy(Line, "                ");
//
//      #include "Display.h"
//
//// Need: LiquidCrystal I2C
//// 
//#include <LiquidCrystal_I2C.h>
//
//Display::Display()
//{
//    State = 0;
//}
//
//void Display::SetStateObject(ActualState * state)
//{
//    State = state;
//}
//
//void Display::Update()
//{
//    
//}
//
//void Setup()
//{
//  
//}
//
//void Display::Loop()
//{
//    if(state_check.wait(100))
//    {
//        Update();
//    }
//}
//
//Display0805i2c::Display0805i2c()
//{
//    lcd = 0;
//}
//
//Display0805i2c::~Display0805i2c()
//{
//    if(lcd)
//    {
//        delete lcd;
//        lcd = 0;
//    }
//}
//
//void Display0805i2c::Setup()
//{
//    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
//    lcd->init();
//    lcd->backlight();
//
//    DrawLogo();
//}
//
//void Display0805i2c::DrawLogo()
//{
//    lcd->setCursor(0, 0);
//    lcd->print("   Oceanika   ");
//    lcd->setCursor(0, 1);
//    lcd->print("   Drone v1   ");
//}
//
//void Display0805i2c::Update()
//{
//    if(lcd)
//    {
//
//        if(State)
//        {
//            char Line[17];
//            // Line 1:
//            strcpy(Line, "                ");
//
//            Line[0] = State->HasWifi ? 'W' : ' ';
//            Line[1] = State->HasDrone ? 'D' : ' ';
//            Line[2] = State->MotorUnlock ? 'M' : ' ';
//            Line[3] = State->Stabilization ? 'S' : ' ';
//            Line[4] = State->PhotoMode ? 'P' : ' ';
//            Line[5] = State->VideoWriting ? 'V' : ' ';
//            Line[5] = State->TangageControl ? 'T' : ' ';
//            
//            lcd->setCursor(0, 0);
//            lcd->print(Line);
//
//            // Line 2:
//            strcpy(Line, "                ");
//
//            sprintf(&Line[0], "D:%d", State->DroneBattery);
//            Line[strlen(Line)] = ' ';
//            sprintf(&Line[8], "J:%d", State->JoystickBattery);
//            Line[strlen(Line)] = ' ';
//            
//            lcd->setCursor(0, 1);
//            lcd->print(Line);
//        }
//        else
//        {
//            lcd->setCursor(0, 0);
//            lcd->print("    No data!..  ");
//            lcd->setCursor(0, 1);
//            lcd->print("                ");
//        }
//    }
//}
