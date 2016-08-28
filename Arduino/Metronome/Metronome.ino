

void setBeatsPerBar(int);
void setTempo(int);

int pin = 7;
int beatInMilliseconds;
int beatsPerBar;
int noteIsOneBeat;

void setBeatsPerBar(int b) {
  beatsPerBar = b;
}
void setNoteIsOneBeat(int b) {
  noteIsOneBeat = b;
}
void setTempo(int t) {
  beatInMilliseconds = 1.0 / (t / 60.0 / 1000.0) / noteIsOneBeat;
}
void setup() {
  pinMode(pin, OUTPUT);

  setBeatsPerBar(3); // numerator of time signature
  setNoteIsOneBeat(4); // denominator of time signature
  
  setTempo(120); // in "(1 / noteIsOneBeat)-notes per minute" i.e. "quarter notes per minute" or "eighth notes per minute"


}

void loop() {
  tone(pin, 220);
  delay(16 * beatInMilliseconds / 10 / noteIsOneBeat);
  noTone(pin);
  delay(16 * beatInMilliseconds / 10 * 9 / noteIsOneBeat);
  for (int j = 0; j < beatsPerBar - 1; j++) {
    tone(pin, 110);
    delay(16 * beatInMilliseconds / 10 / noteIsOneBeat );
    noTone(pin);
    delay(16 * beatInMilliseconds / 10 * 9 / noteIsOneBeat);
  }
}
