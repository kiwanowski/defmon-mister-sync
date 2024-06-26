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

  if (startState == HIGH) {
    if (startLatch == LOW) {
      MIDI.sendStart();
      startLatch = HIGH;
    }

    if (clockState == HIGH) {
      if (clockLatch == LOW) {
        MIDI.sendClock();
        clockLatch = HIGH;
      }
    } else if (clockLatch == HIGH) {
      clockLatch = LOW;
    }
  } else if (startLatch == HIGH) {
    MIDI.sendStop();
    startLatch = LOW;
  }
}
