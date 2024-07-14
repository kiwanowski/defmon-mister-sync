#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

const int startPin = 26;
const int clockPin = 25;

int startState;
int clockState;

int startLatch = LOW;
int clockLatch = LOW;

void setup() {
  pinMode(startPin, INPUT);
  pinMode(clockPin, INPUT);
  MIDI.begin();
}

void loop() {
  startState = digitalRead(startPin);
  clockState = digitalRead(clockPin);

  if (startState == HIGH && startLatch == LOW) {
    MIDI.sendStart();
    startLatch = HIGH;
  } else if (startState == LOW && startLatch == HIGH) {
    MIDI.sendStop();
    startLatch = LOW;
  }

  if (startState == HIGH && clockState == HIGH && clockLatch == LOW) {
    MIDI.sendClock();
    clockLatch = HIGH;
  } else if (clockState == LOW && clockLatch == HIGH) {
    clockLatch = LOW;
  }
}
