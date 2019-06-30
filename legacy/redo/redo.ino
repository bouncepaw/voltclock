#include <Wire.h>
#include <iarduino_RTC.h>
#include "buttons.h"

// Pins 2..7 are used for buttons. Six of them.
#define RTC_VCC    A3
#define RTC_GND    A2
#define hoursPin   11
#define minutesPin 10
#define secondsPin 9

iarduino_RTC time(RTC_DS1307);

struct triplet {
  byte hours, minutes, seconds;
} currPWM, nextPWM;

void setup(){
  Serial.begin(9600);
  Serial.println("Initing voltclock");
  pinMode(hoursPin,   OUTPUT);
  pinMode(minutesPin, OUTPUT);
  pinMode(secondsPin, OUTPUT);
  DDRD |= 0; // set button pins to input at once

  digitalWrite(RTC_VCC, HIGH);
  digitalWrite(RTC_GND, LOW);

  time.begin();
  Serial.println("Init voltclock");
}

#define ring(val, incrementor, low, high)                \
  ((val) == (low) && (incrementor) == -1) ? (high)\
  : ((val) == (high) && (incrementor) == 1) ? (low)\
  : (val) + (incrementor)


// Take the difference between nextPWM and currPWM. If it is > 0, it means there
// is still place to go right, so increment. If < 0, it means hand has to go
// left, so decrement. If there is no difference, just return 0.
#define incdec(val)\
  (val) > 0 ? 1 \
  : (val) < 1 ? -1 \
  : 0
#define runEvery_ms(ms) if(millis() % (ms) == 0)
void loop() {
  // move hands a little
  runEvery_ms(13) {
    analogWrite(hoursPin,
                currPWM.hours += incdec(nextPWM.hours - currPWM.hours));
    analogWrite(minutesPin,
                currPWM.minutes += incdec(nextPWM.minutes - currPWM.minutes));
    analogWrite(secondsPin,
                currPWM.seconds += incdec(nextPWM.seconds - currPWM.seconds));
  }

  // sync every second
  runEvery_ms(1000) {
    updateNextPWM();
  }

  // button-pressing
  VoltclockButton buttonPressed = getButtonPress();
  if(buttonPressed) {
    byte incrementor, incrementee;
    handleButton(buttonPressed, incrementor, incrementee);
    adjust(incrementor, incrementee);
    // force sync time
    updateNextPWM();
  }
  
}

void updateNextPWM() {
  nextPWM = {calcHours(time.Hours),
             calcMinutes(time.minutes),
             calcSeconds(time.seconds)};
  Serial.println(time.gettime("h:i:s"));
}

inline byte calcHours(const byte hour) {
  return 23*(hour > 11 ? hour - 12 : hour);
}

inline byte calcMinutes(const byte minute) {
  return 4*minute;
}

inline byte calcSeconds(const byte second) {
  return 4*second;
}

void handleButton(VoltclockButton button,
                  byte &incrementor,
                  byte &incrementee) {
  incrementor =
    button == hourUp ? +1
    : button == minuteUp ? +1
    : button == secondDown ? +1
    : -1;
  incrementee =
    button == hourUp ? 1
    : button == hourDown ? 1
    : button == minuteUp ? 2
    : button == minuteDown ? 2
    : 3;
}

// incrementee: 1 h  2 m  3 s
// incrementor: 0 or 1
void adjust(byte incrementor, byte incrementee) {
  byte _hours   = incrementee == 1
    ? ring(time.Hours,   incrementor, 0, 23) : -1;
  byte _minutes = incrementee == 2
    ? ring(time.minutes, incrementor, 0, 59) : -1;
  byte _seconds = incrementee == 3
    ? ring(time.seconds, incrementor, 0, 59) : -1;
  time.settime(_seconds, _minutes, _hours);
}
