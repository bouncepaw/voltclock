struct VoltclockDial {
  byte pin;
  byte min;
  float step;
} hourDial, minuteDial, secondDial;

void initDial(VoltclockDial &dial,
              byte pin, byte min, byte max, byte intervals) {
  dial.pin = pin;
  dial.min = min;
  dial.step = (max - min) / intervals;
  pinMode(pin, OUTPUT);
}


void setup() {
  initDial(hourDial,   9,  0, 40, 11);
  initDial(minuteDial, 10, 0, 153, 59);
  initDial(secondDial, 11, 0, 153, 59);
  Serial.begin(9600);
}

void writeGenericTime(VoltclockDial dial, byte value) {
  analogWrite(dial.pin,
              dial.min + value * dial.step);
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

void loop() {
  for(int h = 0; h < 12; h++) {
    writeHours(h);
    delay(1000);
  }
}

