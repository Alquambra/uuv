                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             // Processing buttons

#include <stdint.h>
#include <Arduino.h>
#include "NonBlockDelay.h"
#include "Pins.h"

#ifndef __BUTTONS_H_
#define __BUTTONS_H_

// A  B  C  Ls Rs H  LED L   R   D
// pins.buttons
enum ButtonFunc {
  BUT_A = 0,
  BUT_B = 1,
  BUT_C = 2,
  BUT_LSW = 3,
  BUT_RSW = 4,
  BUT_HOLD = 5,
  BUT_LED = 6,
  BUT_LEFT = 7,
  BUT_RIGHT = 8,
  BUT_D = 9
};

enum ButtonState {
  BUTS_NONE,
  BUTS_SHORT_CLICK,
  BUTS_LONG_CLICK
};

class Buttons {
private:
  NonBlockDelay state_check;
    
  uint16_t PressState;
  uint8_t  PressCounter[BUTTONS_COUNT];
	ButtonState PressEvents[BUTTONS_COUNT];
	
private:
	// Check state of single button
  void ProcessButton(int Index);
	void OnClick(int Index, bool Long);
  
public:
	Buttons();
	
	void Setup();
	void Loop();
	
	ButtonState GetClickState(ButtonFunc Index);

  // Получить состояние кнопки как true:нажата/false:не нажата
  bool GetInputLevel(ButtonFunc Index);

};


#endif
