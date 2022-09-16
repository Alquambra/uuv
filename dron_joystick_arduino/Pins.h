#ifndef __PINS_H__
#define __PINS_H__

enum {
  BUTTONS_COUNT = 10,
  ANALOG_COUNT = 5
};

struct Pins {
  int led = 2;

  int sound = 6;
  int vibro = 0; // A7
  
  //                            A  B  C  Ls Rs H  LED L   R   D
  int buttons[BUTTONS_COUNT] = {3, 4, 5, 7, 8, 9, 10, 11, 12, 13 };

  // Adc channels              LX RX RY LY
  int analog[ANALOG_COUNT] = { 1, 2, 3, 6 }; // A1, A2, A3, A6

  // Battery level
  int battery = 7; // A7
};

// === Pinout ===
// UART:
// D0: RX
// D1: TX

// BUTTONS:
// D3: A
// D4: B
// D5: C
// D7: L_sw
// D8: R_sw
// D9: Hold
// D10: LED
// D11: LEFT
// D12: RIGHT
// D13: D

// INDICATIONS:
// D2: LED
// D6: Sound
// A0: Vibro

// INPUT:
// A1: LX
// A2: RX
// A3: RY
// A6: LY
// A7: VBAT

extern Pins pin;

#endif
