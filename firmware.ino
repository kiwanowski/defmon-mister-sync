#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

const int startPin = 25;
const int clockPin = 26;

void setup() {
  pinMode(startPin, INPUT);
  pinMode(clockPin, INPUT);
  MIDI.begin();
}

void loop() {
  startState = digitalRead(startPin);
  clockState = digitalRead(clockPin);

  if (startState == HIGH) {

    MIDI.sendStart();

    if (clockState == HIGH) {

      MIDI.sendClock();

    }

  } else {

    MIDI.sendStop();

  }

}
