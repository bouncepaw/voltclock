struct VoltclockDial {
  byte pin;
  byte *steps;
} hourDial, minuteDial, secondDial;


byte hourValues[] = {
                     23, 37, 49, 64,
                     74, 83, 93, 104,
                     115, 128, 144, 160};

byte minuteValues[] = {
                       0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
                       20, 22, 23, 25, 27, 28, 30, 32, 34, 35,
                       37, 39, 40, 42, 43, 45, 47, 48, 50, 51,
                       53, 55, 57, 60, 62, 64, 66, 68, 71, 73,
                       75, 78, 81, 84, 87, 91, 94, 97, 100, 103,
                       106, 111, 115, 120, 124, 129, 134, 138, 143, 147};

byte secondValues[] = {
                       6, 8, 11, 13, 15, 18, 20, 22, 24, 27,
                       29, 31, 33, 35, 37, 39, 40, 42, 44, 46,
                       48, 50, 52, 53, 55, 57, 59, 61, 62, 64,
                       66, 68, 70, 72, 74, 76, 77, 79, 81, 83,
                       85, 88, 90, 93, 95, 98, 101, 103, 106, 108,
                       111, 115, 119, 123, 127, 131, 134, 138, 142, 146};

void initDial(VoltclockDial &dial,
              byte pin, byte *steps) {
  dial.pin = pin;
  dial.steps = steps;
  pinMode(pin, OUTPUT);
}

void writeGenericTime(VoltclockDial dial, byte value) {
  analogWrite(dial.pin, dial.steps[value]);
}

void writeHours(byte hours) {
  writeGenericTime(hourDial, hours);
}

void writeMinutes(byte minutes) {
  writeGenericTime(minuteDial, minutes);
}

void writeSeconds(byte seconds) {
  writeGenericTime(secondDial, seconds);
}
