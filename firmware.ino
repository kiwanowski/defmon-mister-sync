#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

const int startPin = 25;
const int clockPin = 26;

int startState;
int clockState;

int startLatch;
int clockLatch;

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

  delay(1);
}
