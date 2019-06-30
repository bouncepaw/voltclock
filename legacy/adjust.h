// adjust.h: adjusting things for voltclock
#pragma once

// Some variables for adjusting mode
bool settingDial = false;
byte settingWhichDial = 1; // 1: h, 2: m, 3: s
// Macros for a more legible code
#define settingHours   (settingWhichDial == 1)
#define settingMinutes (settingWhichDial == 2)
#define settingSeconds (settingWhichDial == 3)
#define setHours()     (settingWhichDial = 1)
#define setMinutes()   (settingWhichDial = 2)
#define setSeconds()   (settingWhichDial = 3)

// Toggle setting mode state and dump time.
void toggleSettingDial() {
  // If about to turn on setting dial mode, save current values.
  if(!settingDial) {
    dumpTime();
    settingDial = true;
    Serial.println("Setting dial on. Awaiting input.");
  }
  // If about to turn off setting dial mode, save new values.
  else {
    settingDial = false;
    dedumpTime();
    Serial.println("Setting dial off");
  }

  blinkLed();
}
  
// Adjust time.
// `plusWhat` is a number added to actual time. It should be either `1` or `-1`.
// If not `settingDial` now, this function does nothing. 
void adjust(int plusWhat) {
  if(!settingDial) return;
  uint8_t _hours = timeDump.hours;
  uint8_t _minutes = timeDump.minutes;
  uint8_t _seconds = timeDump.seconds;

  if(settingHours) {
    if(_hours == 23 && plusWhat == 1) _hours = 0;
    else if(_hours == 0 && plusWhat == -1) _hours = 23;
    else _hours += plusWhat;
    Serial.println("Adjust hours.");
    timeDump.hours = _hours;
  }

  if(settingMinutes) {
    if(_minutes == 59 && plusWhat == 1) _minutes = 0;
    else if(_minutes == 0 && plusWhat == -1) _minutes = 59;
    else _minutes += plusWhat;
    Serial.println("Adjust minutes.");
    timeDump.minutes = _minutes;
  } 

  if(settingSeconds) {
    if(_seconds == 59 && plusWhat == 1) _seconds = 0;
    else if(_seconds == 0 && plusWhat == -1) _seconds = 59;
    else _seconds += plusWhat;
    Serial.println("Adjust seconds.");
    timeDump.seconds = _seconds;
  } 
  echoDump();
  voltwriteDump();
  blinkLed();
}
