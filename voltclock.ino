#include <Wire.h>
#include <iarduino_RTC.h>

#include "dial.h"
#include "button.h"

// Pins 2..7 are used for buttons. Six of them.
#define hourPin   9
#define minutePin 10
#define secondPin 11

iarduino_RTC time(RTC_DS1307);

void setup() {
  // higher pwm freq for pins 9, 10
  TCCR1B = TCCR1B & B11111000 | B00000001;
  // higher pwm freq for pins 3, 11
  TCCR2B = TCCR2B & B11111000 | B00000001;

  Serial.begin(9600);
  initDial(hourDial,   hourPin,   hourValues);
  initDial(minuteDial, minutePin, minuteValues);
  initDial(secondDial, secondPin, secondValues);
  DDRD |= 0; // set button pins to input at once

  time.begin();
  Serial.println("Init voltclock");
}

#define ring(val, incrementor, low, high)                \
  ((val) == (low) && (incrementor) == -1) ? (high)\
  : ((val) == (high) && (incrementor) == +1) ? (low)\
  : (val) + (incrementor)

void loop() {
  // button-pressing
  if(VoltclockButton buttonPressed = getButtonPress()) {
    byte incrementee;
    signed char incrementor;
    handleButton(buttonPressed, incrementor, incrementee);
    adjust(incrementor, incrementee);
    Serial.println(time.gettime("h:i:s"));
  }
  
  if(millis() % 1000 == 0) Serial.println(time.gettime("h:i:s"));

  writeHours(time.hours);
  writeMinutes(time.minutes);
  writeSeconds(time.seconds);
}

void handleButton(VoltclockButton button,
                  signed char &incrementor,
                  byte &incrementee) {
  incrementor =
    button == hourUp ? +1
    : button == minuteUp ? +1
    : button == secondUp ? +1
    : -1;
  incrementee =
    button == hourUp ? 1
    : button == hourDown ? 1
    : button == minuteUp ? 2
    : button == minuteDown ? 2
    : 3;
}

// incrementee: 1 h  2 m  3 s
// incrementor: -1 or 1
void adjust(signed char incrementor, byte incrementee) {
  // -1 to skip value
  time.settime((incrementee == 3
                ? ring(time.seconds, incrementor, 0, 59) : -1),
               (incrementee == 2
                ? ring(time.minutes, incrementor, 0, 59) : -1),
               (incrementee == 1
                ? ring(time.Hours, incrementor, 0, 23) : -1));
}
