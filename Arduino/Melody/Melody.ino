
#include <math.h>
/* TODO
   have individual Songs change tempo, time signature, etc.

   implement "repeat" system to save memory
*/


class Note {
  public:
    int duration;
    // xxx "note" is distance in semitones from base note. 999 = rest.
    // xxx durations: 64 = four beats, 32 = two beats, 16 = 1 beat, 8 = 1/2 beat, 4 = 1/4 beat, 2 = 1/8 beat
    // durations: 64 = whole note, 32 = half note, 16 = quarter note, 8 = eighth note, 4 = sixteenth note, 2 = thirty secondth note
    int distance;
    Note(int, int);
};
Note::Note(int note, int nDuration) : duration(nDuration), distance(note) {}


class Song {
  public:
    int length;
    int defaultTempo;// in "(1 / noteIsOneBeat)-notes per minute" i.e. "quarter notes per minute" or "eighth notes per minute"
    int defaultNoteIsOneBeat;
    static const int maxSize = 140;
    // bunch of zero-length notes
    Note notes[maxSize] = { Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0),
                            Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0), Note(0, 0)
                          };
    Song(Note* nNotes, int nLength, int tempo, int beat) : length(nLength), defaultTempo(tempo), defaultNoteIsOneBeat(beat) {
      for (int i = 0; i < length; i++)
        notes[i] = nNotes[i];
    }
};



class Songbook {
  private:
    //    static Note nTest[5];
    //    static Note nZeldasLullaby[32];
    //    static Note nClocktownBass[75];
    static Note* nClocktownMelody[131];
  public:
    //    static Song Test;
    //    static Song ZeldasLullaby;
    //    static Song ClocktownBass;
    static Song ClocktownMelody;
};
// Note Songbook::nTest[5] = {
//  new Note(0, 16 / 2 * 3), new Note(2, 16 / 2), new Note(4, 16), new Note(-1, 16), new Note(0, 16 * 2)
//};
//Note Songbook::nZeldasLullaby[32] = {
//  new Note(4, 32), new Note(7, 16), new Note(2, 32), new Note(0, 8), new Note(2, 8),
//  new Note(4, 32), new Note(7, 16), new Note(2, 32), new Note(999, 16), new Note(4, 32),
//  new Note(7, 16), new Note(14, 32), new Note(12, 16), new Note(7, 32), new Note(5, 8),
//  new Note(4, 8), new Note(2, 32), new Note(999, 16), new Note(4, 32), new Note(7, 16), new Note(2, 32), // + 1
//  new Note(0, 8), new Note(2, 8), new Note(4, 32), new Note(7, 16), new Note(2, 32),
//  new Note(999, 16), new Note(4, 32), new Note(7, 16), new Note(14, 32), new Note(12, 16),
//  new Note(19, 48)
//};
// Note Songbook::nClocktownBass[75] = {
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 96), new Note(-1, 48), new Note(999, 48), // x6
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 40), new Note(999, 8), new Note(-1, 16), new Note(999, 32), new Note(0, 48), new Note(999, 48), // x9
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 96), new Note(-1, 48), new Note(999, 48), // x6
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 40), new Note(999, 8), new Note(-1, 16), new Note(999, 32), new Note(0, 48), new Note(999, 48), // x9
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 96), new Note(-1, 48), new Note(999, 48), // x6
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 40), new Note(999, 8), new Note(-1, 16), new Note(999, 32), new Note(0, 48), new Note(999, 48), // x9
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 96), new Note(-1, 48), new Note(999, 48), // x6
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 40), new Note(999, 8), new Note(-1, 16), new Note(999, 32), new Note(0, 48), new Note(999, 48), // x9
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 96), new Note(-1, 48), new Note(999, 48), // x6
//  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 40), new Note(999, 8), new Note(-1, 16), new Note(999, 32), new Note(0, 48), new Note(999, 48), // x9
//};
Note* Songbook::nClocktownMelody[131] = {
  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 96), new Note(-1, 48), new Note(999, 48), // x6
  new Note(0, 96), new Note(-1, 48), new Note(999, 48), new Note(-3, 40), new Note(999, 8), new Note(-1, 16), new Note(999, 32), new Note(0, 48), new Note(999, 48), // x9

  new Note(12, 32), new Note(24, 16), new Note(23, 16), new Note(21, 16), new Note(19, 16), new Note(21, 48), new Note(17, 48), // x7
  new Note(19, 32), new Note(14, 16), new Note(19, 16), new Note(17, 16), new Note(14, 16), new Note(17, 32), new Note(19, 16), new Note(16, 48), // x8
  new Note(12, 32), new Note(24, 16), new Note(23, 16), new Note(21, 16), new Note(19, 16), new Note(21, 48), new Note(17, 48), // x7
  new Note(19, 16), new Note(17, 16), new Note(14, 16), new Note(17, 32), new Note(16, 16), new Note(12, 48), new Note(999, 48), // x7

  new Note(12, 32), new Note(24, 16), new Note(23, 16), new Note(21, 16), new Note(19, 16), new Note(21, 48), new Note(17, 48), // x7
  new Note(19, 32), new Note(14, 16), new Note(19, 16), new Note(17, 16), new Note(14, 16), new Note(17, 32), new Note(19, 16), new Note(16, 48), // x8
  new Note(12, 32), new Note(24, 16), new Note(23, 16), new Note(21, 16), new Note(19, 16), new Note(21, 48), new Note(17, 48), // x7
  new Note(19, 16), new Note(17, 16), new Note(14, 16), new Note(17, 32), new Note(16, 16), new Note(12, 48), new Note(999, 48), // x7

  new Note(12, 32), new Note(12, 16), new Note(12, 16), new Note(11, 16), new Note(12, 16), new Note(14, 48), new Note(7, 48), // x7
  new Note(17, 16), new Note(16, 16), new Note(17, 16), new Note(16, 32), new Note(12, 16), new Note(14, 32), new Note(11, 16), new Note(7, 48), // x8
  new Note(12, 32), new Note(12, 16), new Note(12, 16), new Note(11, 16), new Note(12, 16), new Note(14, 48), new Note(7, 48), // x7
  new Note(17, 16), new Note(16, 16), new Note(17, 16), new Note(16, 32), new Note(11, 16), new Note(12, 48), new Note(999, 48), // x7

  new Note(12, 32), new Note(12, 16), new Note(12, 16), new Note(11, 16), new Note(12, 16), new Note(14, 48), new Note(7, 48), // x7
  new Note(17, 16), new Note(16, 16), new Note(17, 16), new Note(16, 32), new Note(12, 16), new Note(14, 32), new Note(11, 16), new Note(7, 48), // x8
  new Note(12, 32), new Note(12, 16), new Note(12, 16), new Note(11, 16), new Note(12, 16), new Note(14, 48), new Note(7, 48), // x7
  new Note(17, 16), new Note(16, 16), new Note(17, 16), new Note(16, 32), new Note(11, 16), new Note(12, 48), new Note(999, 48) // x7
};

//Song Songbook::Test = Song(nTest, 5);
//Song Songbook::ZeldasLullaby = Song(nZeldasLullaby, 32);
//Song Songbook::ClocktownBass = Song(nClocktownBass, 75);
Song Songbook::ClocktownMelody = Song(nClocktownMelody, 131, 90, 8);



void setKey(char);
void setTempo(int);
double getFreq(int);
void playSong(const Song);
void playNote(Note);

// Frequency 'n' semitones away from Base Frequency = Base Frequency * ((2^(1/12))^n)
const float twototheonetwelfth = pow(2, (1 / 12.0));
const int pin = 7;
double key;
int beatInMilliseconds;
int noteIsOneBeat;



void setKey(char letter) {
  switch (letter) {
    case 'C': {
        key = 130.81;
        break;
      }
    case 'D': {
        key = 146.83;
        break;
      }
    case 'E': {
        key = 164.81;
        break;
      }
    case 'F': {
        key = 174.61;
        break;
      }
    case 'G': {
        key = 196.00;
        break;
      }
    case 'A': {
        key = 220.00;
        break;
      }
    case 'B': {
        key = 246.94;
        break;
      }
    default: {
        key = 220.00;
      }
  }
}
void overrideNoteIsOneBeat(int b) {
  noteIsOneBeat = b;
}
// tempo is in units of "(1 / noteIsOneBeat)-notes per minute"
void overrideTempo(int t) {
  beatInMilliseconds = 1.0 / (t / 60.0 / 1000.0) / noteIsOneBeat;
}
double getFreq(int distance) {
  return key * pow(twototheonetwelfth, distance);
}
void playSong(const Song song) {

  overrideNoteIsOneBeat(song.defaultNoteIsOneBeat);
  overrideTempo(song.defaultTempo);

  for (int i = 0; i < song.length; i++) {
    playNote(song.notes[i]);
  }
  playNote(Note(999, 0)); // "ends" song
}
void playNote(Note note) {
  if (note.distance == 999) {
    noTone(pin);
    delay(note.duration * beatInMilliseconds / noteIsOneBeat);
  } else if (note.duration != 0) {
    tone(pin, getFreq(note.distance));
    delay(note.duration * beatInMilliseconds / noteIsOneBeat);
    //noTone(pin);
  } else
    noTone(pin);
}
void setup() {
  pinMode(pin, OUTPUT);

  //  overrideNoteIsOneBeat(4);
  //  overrideTempo(120);

  setKey('A'); // C D E F G A B

  //  playSong(Songbook::Test);
  //  playSong(Songbook::ZeldasLullaby);
  //  playSong(Songbook::ClocktownBass);
  playSong(Songbook::ClocktownMelody);


}

void loop() {
}

