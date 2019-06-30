#pragma once

enum VoltclockButton {
              secondUp = 2,
              secondDown,
              hourUp,
              minuteUp,
              hourDown,
              minuteDown,
              EOL};
#define iterateButtons for(byte btn = 2; btn < EOL; btn++)

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

VoltclockButton getButtonPress() {
  static byte prevPIND;
  byte currPIND = PIND & 0b11111100, // get buttons but not RX and TX
    res = 0;
  iterateButtons {
    //          v  check if anything is different
    //   check if the btn is pressed now  v
    if((currPIND != prevPIND) && (currPIND & (1 << btn))) {
      Serial.print("Pressed button ");
      Serial.print(getStringButton(1 << btn));
      Serial.println(".");
      res = btn;
    }
  }
  prevPIND = currPIND;
  return res;
}
