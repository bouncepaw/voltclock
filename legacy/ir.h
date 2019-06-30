// ir.h: IR processing code for voltclock
#pragma once

// Keys used by voltclock.
#define button1     0xC101E57B
#define button2     0x97483BFB
#define button3     0xF0C41643
#define button_ok   0xD7E84B1B
#define button_up   0x511DBB
#define button_down 0xA3c8EDDB
// Handle IR input.
void decodeIR() {
  if(irrecv.decode(&results)) {
    // All used keys are in range 0xFD0000..0xFE0000 or kinda like that. Let's
    // ignore others.
    if(results.value > 0xFD0000 || results.value < 0xFE0000) {

      // Otherwise, continue processing.
      Serial.print("Press button ");
      Serial.println(results.value, HEX);

      switch(results.value) {
      case button1:
        Serial.println("Set hour dial.");
        blinkLed();
        setHours();
        break;
      case button2:
        Serial.println("Set minute dial.");
        blinkLed();
        setMinutes();
        break;
      case button3:
        Serial.println("Set second dial.");
        blinkLed();
        setSeconds();
        break;
      case button_ok:
        toggleSettingDial();
        break;
      case button_up:
        adjust(+1);
        break;
      case button_down:
        adjust(-1);
        break;
      } // end switch
    } // end if
    irrecv.resume();
  } // end if
} // end fun
