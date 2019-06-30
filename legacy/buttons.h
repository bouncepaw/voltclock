// buttons.h: button processing for voltclock
#pragma once

enum VoltclockButton { 
              secondUp = 2,
              secondDown,
              hourUp,
              minuteUp,
              hourDown,
              minuteDown,
              EOL};
#define iterateButtons for(byte btn = secondDown; btn < EOL; btn++)

VoltclockButton getButtonPress() {
  static byte prevPIND;
  byte currPIND = PIND & 0b11111100, // get buttons but not RX and TX
    res = 0;
  iterateButtons {
    //          v  check if anything is different
    //   check if the btn is pressed now  v
    if((currPIND != prevPIND) && (currPIND & (1 << btn)) {
        Serial.print("Pressed button " + getStringButton(1 << btn) + ".");
        res = btn;
    }
  }
  prevPIND = currPIND;
  return res;
}

void setup() {
  Serial.begin(9600);
  DDRD |= 0; // set button pins as inputs
}

char* getStringButton(byte bitmask) {
  switch(bitmask) {
  case 1 << secondUp:
    return "second up";
  case 1 << secondDown:
    return "second down";
  case 1 << hourUp:
    return "hour up";
  case 1 << hourDown:
    return "hour down";
  case 1 << minuteUp:
    return "minute up";
  case 1 << minuteDown:
    return "minute down";
  default:
    return "unknown :(";
  }
}
