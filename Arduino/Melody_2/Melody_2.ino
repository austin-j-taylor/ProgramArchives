
#include <math.h>

/* TODO

   merge other songs, finish Clocktown
*/
//** ReacXion Source Code **//
//** www.jeremyblum.com **//

/* forgive the usage of chars as integers. Arduinos have no acces to the C++ libraries for int_8 and so on. Gotta save that 5% memory.

  /* CONSTANT AND VARIABLE DECLARATIONS*/
// used to describe how fast the Arduino calls the interrupt. Higher means slower update and less accurate frequencies; lower means faster update and more accurate frequency. Anything lower than ~20 is corruptive.
#define SPEEDCONST 32
// used to describe conversion from Hz to microseconds for Arduino
#define MICROC 1000000.0 / 2 / SPEEDCONST
// used in calculation of frequencies
#define twototheonetwelfth pow(2, (1 / 12.0))

/* Timer reload value, globally available */
unsigned int tcnt2;

/* Toggle HIGH or LOW digital write */
int toggle[] = { 0, 0 };

// holds the current frequency to play (actually holds the note's half-period in 64-microseconds) (i.e. 0 = 0 us, 1 = 64 us, 2 = 2 * 64, etc.
unsigned char freq[] = { 126, 126 };

// keeps track of when each note needs to be switched, used to describe half-period in 64-microseconds; increases with time up to the count1/2/etc.'s respective freq[0]/2/etc.
volatile unsigned int countf[] = { 0, 0 };

volatile unsigned int countd[] = { 0, 0 };

//bool volatile playNext[] = { true, true };
bool playingSong[] = { false, false };

// holds the  time to play a note in units of 64-microseconds
unsigned int duration[] = { 0, 0 };

// holds the index of the current Motif of the Song to play
volatile unsigned char motifIndex[] = { 0, 0 };

// holds the index of the current Note of a Motif to play
volatile unsigned char noteIndex[] = { 0, 0 };

/* Frequency Output Pins */
const char pin[] = { 9, 10 };
// length of songs (number of motifs)
char length[] = { 0, 0 };

// Frequency 'n' semitones away from Base Frequency = Base Frequency * ((2^(1/12))^n)
double key = 220.0;
double beatInMilliseconds;
unsigned int noteIsOneBeat;
// durations: 64 = whole note, 32 = half note, 16 = quarter note, 8 = eighth note, 4 = sixteenth note

/* CLASSES USED IN FORMATION OF SONGS */
// a single note to be played in a Motif
class Note {
  public:
    unsigned char duration;
    char distance;
    Note(char note, int nDur) : duration(nDur), distance(note) {}
};

// an array of Notes
class Motif {
  public:
    unsigned char length; // number of notes
    Note* notes;
    Motif(Note* nNotes,  unsigned char nLength) : length(nLength), notes(nNotes) {}
};

// an array of Motifs
class Song {
  private:
    // be warned: there are SERIOUS memory problems with using getlength(). somehow, length gets changed (pointer gone rogue? I don't know) and getlength() returns a bad value. use the global variable length[] instead.
    unsigned char length;
  public:
    unsigned char getlength() {
      return length;
    }
    unsigned char defaultTempo; // in "(1 / noteIsOneBeat)-notes per minute" i.e. "quarter notes per minute" or "eighth notes per minute"       NUMERATOR of time signature
    unsigned char defaultNoteIsOneBeat; // note that is one beat                                                                                DENOMINATOR of time signature
    Motif** motifs;
    Song(Motif** nMotifs,  unsigned char nLength,  unsigned char tempo,  unsigned char beat) : motifs(nMotifs), length(nLength), defaultTempo(tempo), defaultNoteIsOneBeat(beat) {}
};

// collection of written Songs
class Songbook {
    // declaration of Notes, Motifs, and Songs.
    // motifs' number postfix show the order in the song they first appear
    /*
      PREFIX KEY:
      n_          ...   Note[]  ---> Motif
      m_          ...   Motif
      s_          ...   Motif[] ---> Song
      [nothing]   ...   Song
    */
  private:
    static Note n_ClocktownB1[15];
    static Note n_ClocktownB2[14];
    static Note n_ClocktownB3[10];
    static Note n_Clocktown1[8];
    static Note n_Clocktown2[7];
    static Note n_Clocktown3[8];
    static Note n_Clocktown4[7];
    static Note n_Clocktown5[7];
    static Note n_Clocktown6[8];
    static Note n_Clocktown7[7];
    static Note n_Clocktown8[11];

    static Motif* m_ClocktownB1;
    static Motif* m_ClocktownB2;
    static Motif* m_ClocktownB3;
    static Motif* m_Clocktown1;
    static Motif* m_Clocktown2;
    static Motif* m_Clocktown3;
    static Motif* m_Clocktown4;
    static Motif* m_Clocktown5;
    static Motif* m_Clocktown6;
    static Motif* m_Clocktown7;
    static Motif* m_Clocktown8;

    static Motif* s_Clocktown[35];
    static Motif* s_ClocktownBass[11];

  public:
    static Song Clocktown;
    static Song ClocktownBass;
};

Note Songbook::n_ClocktownB1[15] = {
  Note(0, 96), Note(-1, 48), Note(126, 48), Note(-3, 96), Note(-1, 48), Note(126, 48), // x6
  Note(0, 96), Note(-1, 48), Note(126, 48), Note(-3, 40), Note(126, 8), Note(-1, 16), Note(126, 32), Note(0, 48), Note(126, 48) // x9
};
Note Songbook::n_ClocktownB2[14] = {
  Note(12, 96), Note(11, 16), Note(126, 80), Note(9, 96), Note(7, 16), Note(126, 80),
  Note(12, 96), Note(11, 16), Note(126, 32), Note(9, 40), Note(126, 8), Note(7, 96), Note(5, 32), Note(126, 64)
};
Note Songbook::n_ClocktownB3[10] = {
  Note(12, 96), Note(11, 16), Note(126, 80), Note(17, 96), Note(16, 16), Note(126, 80),
  Note(16, 96), Note(15, 96), Note(14, 96 + 48), Note(126, 48)
};

Note Songbook::n_Clocktown1[8] = {
  Note(126, 96), Note(126, 96), Note(126, 96), Note(126, 96), Note(126, 96), Note(126, 96), Note(126, 96), Note(126, 96) // x8
};
Note Songbook::n_Clocktown2[7] = {
  Note(12, 32), Note(24, 16), Note(23, 16), Note(21, 16), Note(19, 16), Note(21, 48), Note(17, 48) // x7
};
Note Songbook::n_Clocktown3[8] = {
  Note(19, 32), Note(14, 16), Note(19, 16), Note(17, 16), Note(14, 16), Note(17, 32), Note(19, 16), Note(16, 48) // x8
};
Note Songbook::n_Clocktown4[7] = {
  Note(19, 16), Note(17, 16), Note(14, 16), Note(17, 32), Note(16, 16), Note(12, 48), Note(126, 48) // x7
};
Note Songbook::n_Clocktown5[7] = {
  Note(12, 32), Note(12, 16), Note(12, 16), Note(11, 16), Note(12, 16), Note(14, 48), Note(7, 48) // x7
};
Note Songbook::n_Clocktown6[8] = {
  Note(17, 16), Note(16, 16), Note(17, 16), Note(16, 32), Note(12, 16), Note(14, 32), Note(11, 16), Note(7, 48) // x8
};
Note Songbook::n_Clocktown7[7] = {
  Note(17, 16), Note(16, 16), Note(17, 16), Note(16, 32), Note(11, 16), Note(12, 48), Note(126, 48) // x7
};
Note Songbook::n_Clocktown8[11] = {
  Note(126, 96), Note(126, 96), Note(126, 96), Note(126, 96),
  Note(126, 96), Note(126, 96), Note(126, 32), Note(7 + 12, 16), Note(19 + 12, 32), Note(7 + 12, 16), Note(19 + 12, 96)
};

Motif* Songbook::m_ClocktownB1 = new Motif(n_ClocktownB1, 15);
Motif* Songbook::m_ClocktownB2 = new Motif(n_ClocktownB2, 14);
Motif* Songbook::m_ClocktownB3 = new Motif(n_ClocktownB3, 10);
Motif* Songbook::m_Clocktown1 = new Motif(n_Clocktown1, 8);
Motif* Songbook::m_Clocktown2 = new Motif(n_Clocktown2, 7);
Motif* Songbook::m_Clocktown3 = new Motif(n_Clocktown3, 8);
Motif* Songbook::m_Clocktown4 = new Motif(n_Clocktown4, 7);
Motif* Songbook::m_Clocktown5 = new Motif(n_Clocktown5, 7);
Motif* Songbook::m_Clocktown6 = new Motif(n_Clocktown6, 8);
Motif* Songbook::m_Clocktown7 = new Motif(n_Clocktown7, 7);
Motif* Songbook::m_Clocktown8 = new Motif(n_Clocktown8, 11);

Motif* Songbook::s_ClocktownBass[11] = {
  m_ClocktownB1,

  m_ClocktownB1,
  m_ClocktownB1,

  m_ClocktownB1,
  m_ClocktownB1,

  m_ClocktownB2, m_ClocktownB3,

  m_ClocktownB1,
  m_ClocktownB1,

  m_ClocktownB1,
  m_ClocktownB1
};
Motif* Songbook::s_Clocktown[35] = {
  m_Clocktown1,
  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,
  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,

  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7,
  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7,
  m_Clocktown1,                             m_Clocktown8,

  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,
  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,

  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7,
  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7

};

Song Songbook::ClocktownBass = Song(s_ClocktownBass, 11, 90, 8);
Song Songbook::Clocktown = Song(s_Clocktown, 35, 90, 8);

/* MORE DECLARATIONS*/
void setKey(char);
void setTempo(char);
double getFreq(char);
char getMicros(double);
void playSong( Song, char);

Song* volatile songChannel;
Note* volatile currentNote;

/* GETTERS AND SETTERS */
void setKey(char letter) {
  double multiplier = 1; //increases or decreases key. Higher = less accurate.
  switch (letter) {
    case 'C': {
        key = 130.81 * multiplier;
        break;
      }
    case 'D': {
        key = 146.83 * multiplier;
        break;
      }
    case 'E': {
        key = 164.81 * multiplier;
        break;
      }
    case 'F': {
        key = 174.61 * multiplier;
        break;
      }
    case 'G': {
        key = 196.00 * multiplier;
        break;
      }
    case 'A': {
        key = 220.00 * multiplier;
        break;
      }
    case 'B': {
        key = 246.94 * multiplier;
        break;
      }
  }
}
void setNoteIsOneBeat(char b) {
  noteIsOneBeat = b;
}
// tempo is in units of "(1 / noteIsOneBeat)-notes per minute"
// beatInMilliseconds is the period of one beat in milliseconds (of course)
void setTempo(char t) {
  beatInMilliseconds = (1.0 / (t / 60.0 / 1000.0) / 8);
}
double getFreq(char distance) {
  return key * pow(twototheonetwelfth, distance);
}
char getMicros(double freq) {
  return (char) (MICROC / freq + .5);
}
// plays a song on the specified channel
void playSong(Song song, char channel) {
  // only assigns once
  if (channel == 0) {
    setNoteIsOneBeat(song.defaultNoteIsOneBeat);
    setTempo(song.defaultTempo);
  }
  songChannel[channel] = song;
  length[channel] = song.getlength();
  playingSong[channel] = true;
}
void setup() {
  Serial.begin(9600);
  setKey('C'); // C D E F G A B
  /* TIMER STUFF */
  /* First disable the timer overflow interrupt*/
  TIMSK2 &= ~(1 << TOIE2);

  /* Configure timer2 in normal mode (no PWM) */
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  TCCR2B &= ~(1 << WGM22);

  /* Select clock source: internal I/O clock */
  ASSR &= ~(1 << AS2);

  /* Disable Compare Match A interrupt (only overflow) */
  TIMSK2 &= ~(1 << OCIE2A);

  /* Configure the prescaler to CPU clock divided by 128 */
  TCCR2B |= (1 << CS22)  | (1 << CS20); // Set bits
  TCCR2B &= ~(1 << CS21);           // Clear bit

  /* We need to calculate a proper value to load the counter.
    The following loads the value 248 into the Timer 2 counter
    The math behind this is:
    (Desired period) = SPEEDCONSTus.
    (CPU frequency) / (prescaler value) = 125000 Hz -> 8us.
    SPEEDCONSTus / 8us
    MAX(uint8) - SPEEDCONSTus / 8us = 252;
  */
  /* Save value globally for later reload in ISR */
  tcnt2 = 256 - SPEEDCONST / 8;

  /* Finally load end enable the timer */
  TCNT2 = tcnt2;
  TIMSK2 |= (1 << TOIE2);

  // configure pins for channels and buttons
  pinMode(pin[0],    OUTPUT);
  pinMode(pin[1],    OUTPUT);
  pinMode(4,    INPUT);
  pinMode(5,    INPUT);
  pinMode(8,    INPUT);
}

/* Installs the interrupt Service Routine (ISR) for Timer2, executed every SPEEDCONST microseconds */
ISR(TIMER2_OVF_vect) {
  /* Reload the timer */
  TCNT2 = tcnt2;
  // increment counters
  countd[0]++;
  countd[1]++;

  /* Note the lack of a for-loop for iterating through each channel. The Arduino REALLY doesn't like having a for loop in an Interrupt, so I had to copy-paste stuff instead. Sorry. */
  /* Also, for SOME reason, the channels have to execute in 1-followed-by-0 order, rather than 0-to-1. Otherwise, channel 0 skips the first note. And no, in 1-to-0, channel 1 doesn't skip its first note. ¯\_(ツ)_/¯  */

  // goes through each channel, sees if it's playing a song
  if (playingSong[1]) {
    /* PLAY FREQUENCY 1 */
    if (freq[1] != 126) {
      countf[1]++;
      if (freq[1] == countf[1]) {
        digitalWrite(pin[1], toggle[1] == 0 ? HIGH : LOW);
        toggle[1] = ~toggle[1];
        countf[1] = 0;
      }
    } else {
      //        digitalWrite(pin[1], LOW);
      countf[1] = 0;
    }

    // if the current note has played as long as it should
    if (countd[1] == duration[1]) {
      countd[1] = 0;
      countf[1] = 0;

      /* BASICALLY A TRANS-INTERRUPT FOR LOOP... OH BOY */
      // figures out what note to play next or if the song should end
      if (noteIndex[1] < songChannel[1].motifs[motifIndex[1]]->length) { // same motif as before, next note
      } else { // next motif
        motifIndex[1]++;
        noteIndex[1] = 0;
      }
      if (motifIndex[1] == length[1]) { // end of song
        freq[1] =  126;
        playingSong[1] = false;
        noteIndex[1] = 0;
        motifIndex[1] = 0;
        duration[1] = 0;
      } else {
        currentNote = &songChannel[1].motifs[motifIndex[1]]->notes[noteIndex[1]];
        duration[1] = (currentNote->duration) * beatInMilliseconds / noteIsOneBeat * 1000 / SPEEDCONST;
        freq[1] = (currentNote->distance == '~' /* ascii code 126 */ ) ? 126 : getMicros(getFreq(currentNote->distance)); // 126? rest if true, normal frequency if not
        noteIndex[1]++;
      }
    }
  }
  if (playingSong[0]) {
    /* PLAY FREQUENCY 0 */
    if (freq[0] != 126) {
      countf[0]++;
      if (freq[0] == countf[0]) {
        digitalWrite(pin[0], toggle[0] == 0 ? HIGH : LOW);
        toggle[0] = ~toggle[0];
        countf[0] = 0;
      }
    } else {
      //        digitalWrite(pin[0], LOW);
      countf[0] = 0;
    }

    /* CHANNEL 0 */
    if (countd[0] == duration[0]) {
      countd[0] = 0;
      countf[0] = 0;
      //      Serial.println(songChannel[0].getlength());
      if (noteIndex[0] < songChannel[0].motifs[motifIndex[0]]->length) { // same motif as before, next note
      } else { // next motif
        motifIndex[0]++;
        noteIndex[0] = 0;
      }
      if (motifIndex[0] == length[0]) { // end of song
        freq[0] = 126;
        playingSong[0] = false;
        noteIndex[0] = 0;
        motifIndex[0] = 0;
        duration[0] = 0;
      } else {
        currentNote = &songChannel[0].motifs[motifIndex[0]]->notes[noteIndex[0]];
        duration[0] = (currentNote->duration) * beatInMilliseconds / noteIsOneBeat * 1000 / SPEEDCONST;
        freq[0] = (currentNote->distance ==  '~') ? 126 : getMicros(getFreq(currentNote->distance)); // 126? rest if true, normal frequency if not
        noteIndex[0]++;
      }
    }
  }
}

void loop() {
  // reading of buttons to decide what song to play
  // comments beside conditionals show what button presses activate that conditional
  if (!playingSong[0] && !playingSong[1]) {
    if (digitalRead(4) == HIGH || digitalRead(5) == HIGH || digitalRead(8) == HIGH) {
      delay(100);
      int state4 = digitalRead(4);
      int state5 = digitalRead(5);
      int state8 = digitalRead(8);
      if (state4 == HIGH) //Y__
        if (state5 == HIGH) //YY_
          if (state8 == HIGH) {} //YYY
      //          tone(pin[0], 880);
          else {} //YYN
      //          tone(pin[0], 660);
        else //YN_
          if (state8 == HIGH) {}//YNY
      //          tone(pin[0], 550);
          else {} //YNN
      //          tone(pin[0], 330);
      //          playSong(Songbook::ZeldasLullaby);
      else  //N__
        if (state5 == HIGH) //NY_
          if (state8 == HIGH) {}//NYY
      //          tone(pin[0], 440);
      //          playSong(Songbook::BanneredMare);
          else {} //NYN
      //          tone(pin[0], 220);
        else  //NN_
          if (state8 == HIGH) { //NNY
            //          tone(pin[0], 110);
            playSong(Songbook::Clocktown, 0);
            playSong(Songbook::ClocktownBass, 1);
          }
    }
  }
}
