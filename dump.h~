// dump.h: time dumping features for voltclock
#pragma once

struct TimeDump {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} timeDump;

// Print `timeDump`.
void echoDump() {
  Serial.println("Awaiting input. Time dump:");
  Serial.print(timeDump.hours, DEC);
  Serial.print(":");
  Serial.print(timeDump.minutes, DEC);
  Serial.print(":");
  Serial.println(timeDump.seconds, DEC);
}

// Dump time to `timeDump`.
void dumpTime() {
  timeDump.hours = time.Hours;
  timeDump.minutes = time.minutes;
  timeDump.seconds = time.seconds;
}

// Do the opposite of `dumpTime`.
void dedumpTime() {
  Serial.println("Dedump time");
  echoDump();
  time.settime(timeDump.seconds, timeDump.minutes, timeDump.hours);
  Serial.println("The new time is:");
  Serial.println(time.gettime("H:i:s"));
}
