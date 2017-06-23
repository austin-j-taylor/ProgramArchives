
#include <math.h>

/* TODO
    fix songs playing without reseting
    have note multiplier so DD doesn't take up so much memory
*/
//** ReacXion Source Code **//
//** www.jeremyblum.com **//

/* forgive the usage of chars as numbers. Arduinos have no access to the C++ libraries for int_8 and so on. Gotta save that 5% memory.

  /* CONSTANT AND VARIABLE DECLARATIONS*/
// used to describe how fast the Arduino calls the interrupt. Higher means slower update and less accurate frequencies; lower means faster update and more accurate frequency. Anything lower than ~20 is corruptive.
#define SPEEDCONST 32
// used to describe conversion from Hz to microseconds for Arduino
#define MICROC 1000000.0 / 2 / SPEEDCONST
// used in calculation of frequencies
// Frequency 'n' semitones away from Base Frequency = Base Frequency * ((2^(1/12))^n)
#define twototheonetwelfth pow(2, (1 / 12.0))

/* Timer reload value, globally available */
unsigned int tcnt2;

/* Toggle HIGH or LOW digital write */
int toggle[] = { 0, 0 };

// holds the current frequency to play (actually holds the note's half-period in 64-microseconds) (i.e. 0 = 0 us, 1 = 64 us, 2 = 2 * 64, etc.
unsigned char freq[] = { 126, 126 };

// keeps track of when each note needs to be switched, used to describe half-period in 64-microseconds; increases with time up to the count1/2/etc.'s respective freq[0]/2/etc.
unsigned int countf[] = { 0, 0 };

unsigned int countd[] = { 0, 0 };

bool playingSong[] = { false, false };

// holds the  time to play a note in units of 64-microseconds
int duration[] = { 0, 0 };

// holds the index of the current Motif of the Song to play
unsigned short motifIndex[] = { 0, 0 };

// holds the index of the current Note of a Motif to play
unsigned short noteIndex[] = { 0, 0 };

// indicates if the metronome is currently playing
bool playingMetronome = false;

/* Frequency Output Pins */
const char pin[] = { 6, 3 };
// length of songs (number of motifs)
unsigned short songLength[] = { 0, 0 };
// length of motifs (number of notes)
//unsigned short motifLength[] = { 0, 0 };

double key = 220.0;
double beatInMilliseconds;
unsigned int noteIsOneBeat;
unsigned char beatsPerMeasure;
unsigned char measuresToPlay;
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
  private:
    unsigned short length; // number of note
  public:
    unsigned short getlength() {
      return length;
    }
    Note* notes;
    Motif(Note* nNotes,  unsigned short nLength) : length(nLength), notes(nNotes) {}
};

// an array of Motifs
class Song {
  private:
    unsigned short length;
  public:
    unsigned short getlength() {
      return length;
    }
    unsigned char defaultTempo; // in "(1 / noteIsOneBeat)-notes per minute" i.e. "quarter notes per minute" or "eighth notes per minute"       NUMERATOR of time signature
    unsigned char defaultNoteIsOneBeat; // note that is one beat                                                                                DENOMINATOR of time signature
    Motif** motifs;
    Song(Motif** nMotifs,  unsigned short nLength,  unsigned char tempo,  unsigned char beat) : motifs(nMotifs), length(nLength), defaultTempo(tempo), defaultNoteIsOneBeat(beat) {}
};

// collection of written Songs
// Some songs may be commented out, as the Arduino doesn't have enough memory to store them.
class Songbook {
    // declaration of Notes, Motifs, and Songs.
    // motifs' number postfix show the order in the song they first appear
    /*
      PREFIX KEY:
      n_          ...   Note[]  ---> Motif
      n_...REST#  ...   Note[] with only rests
      m_          ...   Motif
      s_          ...   Motif[] ---> Song
      [nothing]   ...   Song
    */
  private:
    static Note n_ClocktownB1[15];
    static Note n_ClocktownB2[14];
    static Note n_ClocktownB3[10];
    static Note n_ClocktownREST1[8];
    static Note n_Clocktown2[7];
    static Note n_Clocktown3[8];
    static Note n_Clocktown4[7];
    static Note n_Clocktown5[7];
    static Note n_Clocktown6[8];
    static Note n_Clocktown7[7];
    static Note n_Clocktown8[11];

    static Note n_ZeldasLullaby1[9];
    static Note n_ZeldasLullaby2[9];
    static Note n_ZeldasLullaby3[6];
    static Note n_ZeldasLullaby4[5];
    static Note n_ZeldasLullaby5[7];
    static Note n_ZeldasLullaby6[4];
    
//    static Note n_BM1[6];
//    static Note n_BM2[6];
//    static Note n_BM3[6];
//    static Note n_BM4[6];
//    static Note n_BM5[7];
//    static Note n_BM6[4];
//    static Note n_BM7[6];
//    static Note n_BM8[8];
//    static Note n_BM9[7];
//    static Note n_BM10[8];
//    static Note n_BM11[8];
//    static Note n_BM12[10];
//    static Note n_BM13[5];

    static Note n_DragonsREST1[4];
    static Note n_DragonsB1[10];
    static Note n_DragonsB2[9];
    static Note n_DragonsB3[10];
    static Note n_DragonsB4[9];
    static Note n_DragonsB5[5];
    static Note n_DragonsB6[5];
    static Note n_DragonsB7[5];
    static Note n_DragonsB8[4];
    static Note n_DragonsB9[4];
    static Note n_DragonsB10a[3];
    static Note n_Dragons1[5];
    static Note n_Dragons2[5];
    static Note n_Dragons3[5];
    static Note n_Dragons4[5];
    static Note n_Dragons5a[3];
    static Note n_Dragons5b[20];
    static Note n_Dragons6a[3];
    static Note n_Dragons6b[20];
    static Note n_Dragons7a[3];
    static Note n_Dragons7b[19];
    static Note n_Dragons8[20];
    //    static Note n_Dragons9[1];

    static Note n_HuntREST1[4];
    static Note n_HuntB1[4];
    static Note n_HuntB2[5];
    static Note n_HuntB3[5];
    static Note n_HuntB4[5];
    static Note n_HuntB5[6];
    static Note n_Hunt1[5];
    static Note n_Hunt2[4];
    static Note n_Hunt3[5];
    static Note n_Hunt4[5];
    static Note n_Hunt5[6];

    static Note n_CustomB1[6];
    //    static Note n_CustomB2[x];
    static Note n_CustomB3[4];
    static Note n_CustomB4[4];

//    static Note n_MEGAREST1[1];
//    static Note n_MEGAB1[7];
//    static Note n_MEGAB2[7];
//    static Note n_MEGAB3[7];
//    static Note n_MEGAB4[7];
//    static Note n_MEGAMelody[12];
//    static Note n_MEGA1[2];
//    static Note n_MEGA2[2];
//    static Note n_MEGA3[2];
//    static Note n_MEGA4[2];
    
    // ----------------------------------
    static Motif* m_ClocktownB1;
    static Motif* m_ClocktownB2;
    static Motif* m_ClocktownB3;
    static Motif* m_ClocktownREST1;
    static Motif* m_Clocktown2;
    static Motif* m_Clocktown3;
    static Motif* m_Clocktown4;
    static Motif* m_Clocktown5;
    static Motif* m_Clocktown6;
    static Motif* m_Clocktown7;
    static Motif* m_Clocktown8;

    static Motif* m_ZeldasLullaby1;
    static Motif* m_ZeldasLullaby2;
    static Motif* m_ZeldasLullaby3;
    static Motif* m_ZeldasLullaby4;
    static Motif* m_ZeldasLullaby5;
    static Motif* m_ZeldasLullaby6;
//    static Motif* m_BM1;
//    static Motif* m_BM2;
//    static Motif* m_BM3;
//    static Motif* m_BM4;
//    static Motif* m_BM5;
//    static Motif* m_BM6;
//    static Motif* m_BM7;
//    static Motif* m_BM8;
//    static Motif* m_BM9;
//    static Motif* m_BM10;
//    static Motif* m_BM11;
//    static Motif* m_BM12;
//    static Motif* m_BM13;

    static Motif* m_DragonsREST1;
    static Motif* m_DragonsB1;
    static Motif* m_DragonsB2;
    static Motif* m_DragonsB3;
    static Motif* m_DragonsB4;
    static Motif* m_DragonsB5;
    static Motif* m_DragonsB6;
    static Motif* m_DragonsB7;
    static Motif* m_DragonsB8;
    static Motif* m_DragonsB9;
    static Motif* m_DragonsB10a;
    static Motif* m_Dragons1;
    static Motif* m_Dragons2;
    static Motif* m_Dragons3;
    static Motif* m_Dragons4;
    static Motif* m_Dragons5a;
    static Motif* m_Dragons5b;
    static Motif* m_Dragons6a;
    static Motif* m_Dragons6b;
    static Motif* m_Dragons7a;
    static Motif* m_Dragons7b;
    static Motif* m_Dragons8;
    //    static Motif* m_Dragons9;

    static Motif* m_HuntREST1;
    static Motif* m_HuntB1;
    static Motif* m_HuntB2;
    static Motif* m_HuntB3;
    static Motif* m_HuntB4;
    static Motif* m_HuntB5;
    static Motif* m_Hunt1;
    static Motif* m_Hunt2;
    static Motif* m_Hunt3;
    static Motif* m_Hunt4;
    static Motif* m_Hunt5;

    static Motif* m_CustomB1;
    //    static Motif* m_CustomB2;
    static Motif* m_CustomB3;
    static Motif* m_CustomB4;

//    static Motif* m_MEGAREST1;
//    static Motif* m_MEGAB1;
//    static Motif* m_MEGAB2;
//    static Motif* m_MEGAB3;
//    static Motif* m_MEGAB4;
//    static Motif* m_MEGAMelody;
//    static Motif* m_MEGA1;
//    static Motif* m_MEGA2;
//    static Motif* m_MEGA3;
//    static Motif* m_MEGA4;
    // ----------------------------------
    static Motif* s_ClocktownBass[11];
    static Motif* s_Clocktown[35];

    static Motif* s_ZeldasLullaby[7];

//    static Motif* s_BanneredMare[16];

    static Motif* s_DragonsBass[46];
    static Motif* s_Dragons[36];

    static Motif* s_HuntBass[13];
    static Motif* s_Hunt[17];

    static Motif* s_CustomBass[12];

//    static Motif* s_MegalovaniaBass[8];
//    static Motif* s_Megalovania[16];
    // ----------------------------------
  public:
    static Song ClocktownBass;
    static Song Clocktown;

    static Song ZeldasLullaby;

//    static Song BanneredMare;

    static Song DragonsBass;
    static Song Dragons;

    static Song HuntBass;
    static Song Hunt;

    static Song CustomBass;

//    static Song MegalovaniaBass;
//    static Song Megalovania;
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

Note Songbook::n_ClocktownREST1[8] = {
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

Note Songbook::n_ZeldasLullaby1[9] = {
  Note(4, 32), Note(7, 16), Note(2, 32), Note(0, 8), Note(2, 8), Note(4, 32), Note(7, 16), Note(2, 32), Note(126, 16) // x9
};
Note Songbook::n_ZeldasLullaby2[9] = {
  Note(4, 32), Note(7, 16), Note(14, 32), Note(12, 16), Note(7, 32), Note(5, 8), Note(4, 8), Note(2, 32), Note(126, 16) // x9
};
Note Songbook::n_ZeldasLullaby3[6] = {
  Note(4, 32), Note(7, 16), Note(14, 32), Note(12, 16), Note(19, 64), Note(126, 32) // x6
};
Note Songbook::n_ZeldasLullaby4[5] = {
  Note(19, 32), Note(17, 8), Note(16, 8), Note(17, 8), Note(16, 8) // x5 //, Note(26, 32)
};
Note Songbook::n_ZeldasLullaby5[7] = {
  Note(14, 32), // x1
  Note(17, 32), Note(16, 8), Note(14, 8), Note(16, 8), Note(14, 8), Note(9, 32) // x6
};
Note Songbook::n_ZeldasLullaby6[4] = {
  Note(14, 16), Note(17, 16), Note(24, 64), Note(126, 32) // x4
};

//Note Songbook::n_BM1[6] = {
//  Note(15, 48), Note(12, 16), Note(14, 32), Note(15, 48), Note(17, 16), Note(15, 32) // x6
//};
//Note Songbook::n_BM2[6] = {
//  Note(14, 48), Note(10, 16), Note(12, 32), Note(14, 48), Note(15, 16), Note(14, 32) // x6
//};
//Note Songbook::n_BM3[6] = {
//  Note(12, 48), Note(8, 16), Note(10, 32), Note(12, 48), Note(14, 16), Note(12, 32) // x6
//};
//Note Songbook::n_BM4[6] = {
//  Note(11, 48), Note(12, 16), Note(9, 32), Note(11, 48), Note(126, 16), Note(7, 32)// x6
//};
//Note Songbook::n_BM5[7] = {
//  Note(12, 48), Note(14, 16), Note(12, 16),  Note(126, 16), Note(12, 48), Note(14, 16), Note(12, 32) // x7
//};
//Note Songbook::n_BM6[4] = {
//  Note(11, 64), Note(14, 32), Note(12, 64), Note(126, 32) // x4
//};
//Note Songbook::n_BM7[6] = {
//  Note(19, 48), Note(15, 16), Note(17, 32), Note(19, 48), Note(20, 16), Note(19, 32) // x6
//};
//Note Songbook::n_BM8[8] = {
//  Note(17, 48), Note(14, 16), Note(15, 32), Note(17, 48), Note(19, 16), Note(17, 16), Note(15, 8), Note(99, 8) // x8
//};
// + n_BM1
//Note Songbook::n_BM9[7] = {
//  Note(14, 32 / 3), Note(15, 32 / 3), Note(14, 32 / 3 + 48 + 8), Note(126, 8), Note(14, 64), Note(10, 24), Note(126, 8) // x7
//};
//Note Songbook::n_BM10[8] = {
//  Note(19, 64), Note(15, 16), Note(17, 16), Note(19, 32), Note(20, 16), Note(19, 16), Note(17, 16), Note(15, 16) // x8
//};
//Note Songbook::n_BM11[8] = {
//  Note(17, 64), Note(14, 16), Note(15, 16), Note(17, 32), Note(19, 16), Note(17, 16), Note(15, 16), Note(14, 16) // x8
//};
//Note Songbook::n_BM12[10] = {
//  Note(15, 32), Note(12, 16), Note(14, 16), Note(15, 24), Note(126, 8), Note(15, 32), Note(17, 16), Note(15, 16), Note(14, 16), Note(12, 16) // x10
//};
//Note Songbook::n_BM13[5] = {
//  Note(14, 32), Note(10, 32), Note(14, 32), Note(12, 64), Note(126, 32) // x5
//};

Note Songbook::n_DragonsREST1[4] = {
  Note(126, 64), Note(126, 64), Note(-12, 64), Note(-12, 64)
};
Note Songbook::n_DragonsB1[10] = {
  Note(0, 32), Note(-2, 32), Note(-5, 48), Note(-2, 16),
  Note(0, 16), Note(2, 16), Note(0, 16), Note(-2, 16), Note(-5, 48), Note(-2, 16)
};
Note Songbook::n_DragonsB2[9] = {
  Note(0, 48), Note(0, 16), Note(2, 16), Note(3, 8), Note(2, 8),
  Note(0, 16), Note(-2, 16), Note(0, 64), Note(0, 64)
};
Note Songbook::n_DragonsB3[10] = {
  Note(12, 32), Note(10, 32), Note(7, 48), Note(10, 16),
  Note(12, 16), Note(14, 16), Note(12, 16), Note(10, 16), Note(7, 48), Note(10, 16)
};
Note Songbook::n_DragonsB4[9] = {
  Note(12, 48), Note(12, 16), Note(14, 16), Note(15, 8), Note(14, 8),
  Note(12, 16), Note(10, 16), Note(12, 64), Note(0, 64)
};
Note Songbook::n_DragonsB5[5] = {
  Note(12, 16), Note(10, 8), Note(12, 8), Note(7, 16), Note(10, 16)
};
Note Songbook::n_DragonsB6[5] = {
  Note(12 - 5, 16), Note(10 - 5, 8), Note(12 - 5, 8), Note(7 - 5, 16), Note(10 - 5, 16)
};
Note Songbook::n_DragonsB7[5] = {
  Note(10, 16), Note(7, 8), Note(10, 8), Note(5, 16), Note(10, 16)
};
Note Songbook::n_DragonsB8[4] = {
  Note(0, 16), Note(3, 16), Note(5, 16), Note(7, 16)
};
Note Songbook::n_DragonsB9[4] = {
  Note(-2, 16), Note(0, 16), Note(2, 16), Note(5, 16)
};
Note Songbook::n_DragonsB10a[3] = {
  Note(0, 32), Note(-5, 16), Note(-2, 16),
};
// D5b
// B5-7

Note Songbook::n_Dragons1[5] = {
  Note(12, 16), Note(10, 8), Note(12, 8), Note(7, 16), Note(10, 16)
};
Note Songbook::n_Dragons2[5] = {
  Note(10, 16), Note(7, 8), Note(10, 8), Note(5, 16), Note(10, 16)
};
Note Songbook::n_Dragons3[5] = {
  Note(12 + 12, 16), Note(12 + 10, 8), Note(12 + 12, 8), Note(12 + 7, 16), Note(12 + 10, 16)
};
Note Songbook::n_Dragons4[5] = {
  Note(12 + 10, 16), Note(12 + 7, 8), Note(12 + 10, 8), Note(12 + 5, 16), Note(12 + 10, 16)
};
Note Songbook::n_Dragons5a[3] = {
  Note(12, 32), Note(7, 16), Note(10, 16),
};
Note Songbook::n_Dragons5b[20] = {
  Note(12, 32), Note(12, 16), Note(10, 16), Note(7, 32), Note(7, 16), Note(10, 16), Note(12, 16), Note(14, 16), Note(12, 16), Note(10, 16), Note(7, 48),
  Note(10, 16), Note(12, 48), Note(10, 16), Note(9, 16), Note(10, 8), Note(9, 8), Note(7, 16), Note(5, 16), Note(7, 64)
};
Note Songbook::n_Dragons6a[3] = {
  Note(126, 32), Note(7 + 12, 16), Note(10 + 12, 16),
};
Note Songbook::n_Dragons6b[20] = {
  Note(12 + 12, 32), Note(12 + 12, 16), Note(10 + 12, 16), Note(7 + 12, 32), Note(7 + 12, 16), Note(10 + 12, 16), Note(12 + 12, 16), Note(14 + 12, 16), Note(12 + 12, 16), Note(10 + 12, 16), Note(7 + 12, 48),
  Note(10 + 12, 16), Note(12 + 12, 48), Note(10 + 12, 16), Note(9 + 12, 16), Note(10 + 12, 8), Note(9 + 12, 8), Note(7 + 12, 16), Note(5 + 12, 16), Note(7 + 12, 64)
};
Note Songbook::n_Dragons7a[3] = {
  Note(126, 32), Note(7, 16), Note(10, 16),
};
Note Songbook::n_Dragons7b[19] = {
  Note(12, 32), Note(10, 32), Note(7, 48), Note(10, 16), Note(12, 16), Note(14, 16), Note(12, 16), Note(10, 16), Note(7, 48), Note(10, 16),
  Note(12, 48), Note(12, 16), Note(14, 16), Note(15, 8), Note(14, 8), Note(12, 16), Note(10, 16), Note(12, 64), Note(12, 64)
};
Note Songbook::n_Dragons8[20] = {
  Note(12 + 12, 32), Note(10 + 12, 16), Note(12 + 12, 8), Note(10 + 12, 8), Note(7 + 12, 48), Note(10 + 12, 16), Note(12 + 12, 16), Note(14 + 12, 16), Note(12 + 12, 16), Note(10 + 12, 16), Note(7 + 12, 48), Note(10 + 12, 16),
  Note(12 + 12, 48), Note(12 + 12, 16), Note(14 + 12, 16), Note(15 + 12, 8), Note(14 + 12, 8), Note(12 + 12, 16), Note(10 + 12, 16), Note(12 + 12, 64)
};
// B6
// B5-7 -last one, + 6a
// 6b
//Note Songbook::n_Dragons9[1] = {
//  Note(0, 64)
//};

Note Songbook::n_HuntREST1[4] = {
  Note(126, 96), Note(126, 96), Note(126, 96), Note(126, 96)
};
Note Songbook::n_HuntB1[4] = {
  Note(0, 96), Note(2, 96), Note(3, 96), Note(2, 96)
};
Note Songbook::n_HuntB2[5] = {
  Note(0, 80), Note(2, 16), Note(3, 32), Note(2, 32), Note(3, 32)
};
Note Songbook::n_HuntB3[5] = {
  Note(0, 80), Note(3, 16), Note(7, 32), Note(6, 32), Note(7, 32)
};
Note Songbook::n_HuntB4[5] = {
  Note(7, 80), Note(6, 16), Note(7, 32), Note(12, 32), Note(8, 32)
};
Note Songbook::n_HuntB5[6] = {
  Note(7, 32), Note(6, 32), Note(7, 48), Note(7, 32), Note(7, 32), Note(7, 96)
};
Note Songbook::n_Hunt1[5] = {
  Note(12, 48), Note(14, 48), Note(15, 32), Note(14, 32), Note(15, 32)
};
Note Songbook::n_Hunt2[4] = {
  Note(12, 48), Note(15, 48), Note(19, 96), Note(19, 0)
};
Note Songbook::n_Hunt3[5] = {
  Note(12, 48), Note(15, 48), Note(19, 32), Note(18, 32), Note(19, 32)
};
Note Songbook::n_Hunt4[5] = {
  Note(19, 32), Note(18, 32), Note(19, 32), Note(24, 32), Note(20, 64)
};
Note Songbook::n_Hunt5[6] = {
  Note(19, 32), Note(18, 32), Note(19, 48), Note(19, 32), Note(18, 32), Note(19, 96)
};
Note Songbook::n_CustomB1[6] = {
  Note(12, 64), Note(10, 64), Note(9, 64), Note(7, 32), Note(9, 16), Note(10, 16)
};
//Note Songbook::n_CustomB2[6] = {
//};
Note Songbook::n_CustomB3[4] = {
  Note(12, 64), Note(10, 64), Note(9, 64), Note(7, 64)
};
Note Songbook::n_CustomB4[4] = {
  Note(12, 32), Note(19, 32), Note(17, 32), Note(14, 32)
};

//Note Songbook::n_MEGAREST1[1] = {
//    Note(126, 64)
//};
//Note Songbook::n_MEGAB1[7] = {
//    Note(0, 8), Note(0, 8), Note(0, 12), Note(0, 8), Note(0, 8), Note(0, 12), Note(0, 8)
//};
//Note Songbook::n_MEGAB2[7] = {
//    Note(-2, 8), Note(-2, 8), Note(-2, 12), Note(-2, 8), Note(-2, 8), Note(-2, 12), Note(-2, 8)
//};
//Note Songbook::n_MEGAB3[7] = {
//    Note(-3, 8), Note(-3, 8), Note(-3, 12), Note(-3, 8), Note(-3, 8), Note(-3, 12), Note(-3, 8)
//};
//Note Songbook::n_MEGAB4[7] = {
//    Note(-4, 8), Note(-4, 8), Note(-4, 12), Note(-2, 8), Note(-2, 8), Note(-2, 12), Note(-2, 8)
//};
//Note Songbook::n_MEGAMelody[12] = {
//     Note(12, 4), Note(126, 4),  Note(7, 4), Note(126, 8),
//     Note(6, 4), Note(126, 4), Note(5, 4), Note(126, 4), Note(3, 8),
//     Note(0, 4), Note(6, 4), Note(5, 4) 
//};
//Note Songbook::n_MEGA1[2] = {
//     Note(0, 4), Note(0, 4)
//};
//Note Songbook::n_MEGA2[2] = {
//     Note(-2, 4), Note(-2, 4)
//};
//Note Songbook::n_MEGA3[2] = {
//     Note(-3, 4), Note(-3, 4)
//};
//Note Songbook::n_MEGA4[2] = {
//     Note(-4, 4), Note(-4, 4)
//};
// -----------------------------------------------------------------------------------------------------------------------------------
Motif* Songbook::m_ClocktownB1 = new Motif(n_ClocktownB1, 15);
Motif* Songbook::m_ClocktownB2 = new Motif(n_ClocktownB2, 14);
Motif* Songbook::m_ClocktownB3 = new Motif(n_ClocktownB3, 10);
Motif* Songbook::m_ClocktownREST1 = new Motif(n_ClocktownREST1, 8);
Motif* Songbook::m_Clocktown2 = new Motif(n_Clocktown2, 7);
Motif* Songbook::m_Clocktown3 = new Motif(n_Clocktown3, 8);
Motif* Songbook::m_Clocktown4 = new Motif(n_Clocktown4, 7);
Motif* Songbook::m_Clocktown5 = new Motif(n_Clocktown5, 7);
Motif* Songbook::m_Clocktown6 = new Motif(n_Clocktown6, 8);
Motif* Songbook::m_Clocktown7 = new Motif(n_Clocktown7, 7);
Motif* Songbook::m_Clocktown8 = new Motif(n_Clocktown8, 11);

Motif* Songbook::m_ZeldasLullaby1 = new Motif(n_ZeldasLullaby1, 9);
Motif* Songbook::m_ZeldasLullaby2 = new Motif(n_ZeldasLullaby2, 9);
Motif* Songbook::m_ZeldasLullaby3 = new Motif(n_ZeldasLullaby3, 6);
Motif* Songbook::m_ZeldasLullaby4 = new Motif(n_ZeldasLullaby4, 5);
Motif* Songbook::m_ZeldasLullaby5 = new Motif(n_ZeldasLullaby5, 7);
Motif* Songbook::m_ZeldasLullaby6 = new Motif(n_ZeldasLullaby6, 4);

//Motif* Songbook::m_BM1 = new Motif(n_BM1, 6);
//Motif* Songbook::m_BM2 = new Motif(n_BM2, 6);
//Motif* Songbook::m_BM3 = new Motif(n_BM3, 6);
//Motif* Songbook::m_BM4 = new Motif(n_BM4, 6);
//Motif* Songbook::m_BM5 = new Motif(n_BM5, 7);
//Motif* Songbook::m_BM6 = new Motif(n_BM6, 4);
//Motif* Songbook::m_BM7 = new Motif(n_BM7, 6);
//Motif* Songbook::m_BM8 = new Motif(n_BM8, 8);
//Motif* Songbook::m_BM9 = new Motif(n_BM9, 7);
//Motif* Songbook::m_BM10 = new Motif(n_BM10, 8);
//Motif* Songbook::m_BM11 = new Motif(n_BM11, 8);
//Motif* Songbook::m_BM12 = new Motif(n_BM12, 10);
//Motif* Songbook::m_BM13 = new Motif(n_BM13, 5);

Motif* Songbook::m_DragonsREST1 = new Motif(n_DragonsREST1, 4);
Motif* Songbook::m_DragonsB1 = new Motif(n_DragonsB1, 10);
Motif* Songbook::m_DragonsB2 = new Motif(n_DragonsB2, 9);
Motif* Songbook::m_DragonsB3 = new Motif(n_DragonsB3, 10);
Motif* Songbook::m_DragonsB4 = new Motif(n_DragonsB4, 9);
Motif* Songbook::m_DragonsB5 = new Motif(n_DragonsB5, 5);
Motif* Songbook::m_DragonsB6 = new Motif(n_DragonsB6, 5);
Motif* Songbook::m_DragonsB7 = new Motif(n_DragonsB7, 5);
Motif* Songbook::m_DragonsB8 = new Motif(n_DragonsB8, 4);
Motif* Songbook::m_DragonsB9 = new Motif(n_DragonsB9, 4);
Motif* Songbook::m_DragonsB10a = new Motif(n_DragonsB10a, 3);
Motif* Songbook::m_Dragons1 = new Motif(n_Dragons1, 5);
Motif* Songbook::m_Dragons2 = new Motif(n_Dragons2, 5);
Motif* Songbook::m_Dragons3 = new Motif(n_Dragons3, 5);
Motif* Songbook::m_Dragons4 = new Motif(n_Dragons4, 5);
Motif* Songbook::m_Dragons5a = new Motif(n_Dragons5a, 3);
Motif* Songbook::m_Dragons5b = new Motif(n_Dragons5b, 20);
Motif* Songbook::m_Dragons6a = new Motif(n_Dragons6a, 3);
Motif* Songbook::m_Dragons6b = new Motif(n_Dragons6b, 20);
Motif* Songbook::m_Dragons7a = new Motif(n_Dragons7a, 3);
Motif* Songbook::m_Dragons7b = new Motif(n_Dragons7b, 19);
Motif* Songbook::m_Dragons8 = new Motif(n_Dragons8, 20);
//Motif* Songbook::m_Dragons9 = new Motif(n_Dragons9, 1);

Motif* Songbook::m_HuntREST1 = new Motif(n_HuntREST1, 4);
Motif* Songbook::m_HuntB1 = new Motif(n_HuntB1, 4);
Motif* Songbook::m_HuntB2 = new Motif(n_HuntB2, 5);
Motif* Songbook::m_HuntB3 = new Motif(n_HuntB3, 5);
Motif* Songbook::m_HuntB4 = new Motif(n_HuntB4, 5);
Motif* Songbook::m_HuntB5 = new Motif(n_HuntB5, 6);
Motif* Songbook::m_Hunt1 = new Motif(n_Hunt1, 5);
Motif* Songbook::m_Hunt2 = new Motif(n_Hunt2, 4);
Motif* Songbook::m_Hunt3 = new Motif(n_Hunt3, 5);
Motif* Songbook::m_Hunt4 = new Motif(n_Hunt4, 5);
Motif* Songbook::m_Hunt5 = new Motif(n_Hunt5, 6);

Motif* Songbook::m_CustomB1 = new Motif(n_CustomB1, 6);
//Motif* Songbook::m_CustomB2 = new Motif(n_CustomB2, x);
Motif* Songbook::m_CustomB3 = new Motif(n_CustomB3, 4);
Motif* Songbook::m_CustomB4 = new Motif(n_CustomB4, 4);

//Motif* Songbook::m_MEGAREST1 = new Motif(n_MEGAREST1, 1);
//Motif* Songbook::m_MEGAB1 = new Motif(n_MEGAB1, 7);
//Motif* Songbook::m_MEGAB2 = new Motif(n_MEGAB2, 7);
//Motif* Songbook::m_MEGAB3 = new Motif(n_MEGAB3, 7);
//Motif* Songbook::m_MEGAB4 = new Motif(n_MEGAB4, 7);
//Motif* Songbook::m_MEGAMelody = new Motif(n_MEGAMelody, 12);
//Motif* Songbook::m_MEGA1 = new Motif(n_MEGA1, 2);
//Motif* Songbook::m_MEGA2 = new Motif(n_MEGA2, 2);
//Motif* Songbook::m_MEGA3 = new Motif(n_MEGA3, 2);
//Motif* Songbook::m_MEGA4 = new Motif(n_MEGA4, 2);
// -----------------------------------------------------------------------------------------------------------------------------------
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
  m_ClocktownREST1,
  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,
  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,

  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7,
  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7,
  m_ClocktownREST1,                         m_Clocktown8,

  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,
  m_Clocktown2, m_Clocktown3, m_Clocktown2, m_Clocktown4,

  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7,
  m_Clocktown5, m_Clocktown6, m_Clocktown5, m_Clocktown7
};

Motif* Songbook::s_ZeldasLullaby[7] = {
                    m_ZeldasLullaby2,
  m_ZeldasLullaby1, m_ZeldasLullaby3,

  m_ZeldasLullaby4, m_ZeldasLullaby5,
  m_ZeldasLullaby4, m_ZeldasLullaby6
};

//Motif* Songbook::s_BanneredMare[16] = {
//  m_BM1, m_BM2, m_BM3, m_BM4,
//  m_BM1, m_BM2, m_BM5, m_BM6,
//  m_BM7, m_BM8, m_BM1, m_BM9,
//  m_BM10, m_BM11, m_BM12, m_BM13
//};

Motif* Songbook::s_DragonsBass[46] = {
  m_DragonsREST1,


  m_DragonsB1,                                            m_DragonsB2,

  m_DragonsB3,                                            m_DragonsB4,


  m_DragonsB5, m_DragonsB6, m_DragonsB5, m_DragonsB6,     m_DragonsB5, m_DragonsB7, m_DragonsB5, m_DragonsB6,
  m_DragonsB5, m_DragonsB6, m_DragonsB5, m_DragonsB6,     m_DragonsB5, m_DragonsB7, m_DragonsB8, m_DragonsB8,


  m_DragonsB8, m_DragonsB8, m_DragonsB8, m_DragonsB8,     m_DragonsB8, m_DragonsB9, m_DragonsB8, m_DragonsB8,
  m_DragonsB8, m_DragonsB8, m_DragonsB8, m_DragonsB8,     m_DragonsB8, m_DragonsB9, m_DragonsB8, m_DragonsB10a,


  m_Dragons5b,
  m_DragonsB5, m_DragonsB6, m_DragonsB5, m_DragonsB6,     m_DragonsB5, m_DragonsB7, m_DragonsB5, m_DragonsB6

};
Motif* Songbook::s_Dragons[36] = {
  m_Dragons1, m_Dragons1, m_Dragons1, m_Dragons1,


  m_Dragons1, m_Dragons1, m_Dragons1, m_Dragons1,         m_Dragons1, m_Dragons2, m_Dragons1, m_Dragons1,
  m_Dragons3, m_Dragons3, m_Dragons3, m_Dragons3,         m_Dragons3, m_Dragons4, m_Dragons3, m_Dragons5a,


  m_Dragons5b,                            m_Dragons6a,    m_Dragons6b,                        m_Dragons7a,

  m_Dragons7b,                                            m_Dragons8,                         m_DragonsB6,


  m_DragonsB5, m_DragonsB6, m_DragonsB5, m_DragonsB6,     m_DragonsB5, m_DragonsB7, m_DragonsB5, m_Dragons6a,
  m_Dragons6b

};

Motif* Songbook::s_HuntBass[13] = {
  m_HuntB1, m_HuntB1,                                     //m_HuntB1, m_HuntB1,

  m_HuntB1, m_HuntB1,                                     m_HuntB1, m_HuntB1,
  m_HuntB2, m_HuntB3, m_HuntB3, m_HuntB4,                 m_HuntB2, m_HuntB3, m_HuntB5,
};
Motif* Songbook::s_Hunt[17] = {
  m_HuntREST1, m_HuntREST1,                               //m_HuntREST1, m_HuntREST1,

  m_Hunt1, m_Hunt2, m_Hunt1, m_Hunt2,                     m_Hunt1, m_Hunt2, m_Hunt1, m_Hunt2,
  m_Hunt1, m_Hunt3, m_Hunt1, m_Hunt4,                     m_Hunt1, m_Hunt3, m_Hunt5
};

Motif* Songbook::s_CustomBass[12] = {
  m_CustomB1, m_CustomB1, m_CustomB1, m_CustomB3,

  m_CustomB4, m_CustomB4, m_CustomB4, m_CustomB4,
  m_CustomB4, m_CustomB4, m_CustomB4, m_CustomB4

};

//Motif* Songbook::s_MegalovaniaBass[8] = {
//  m_MEGAREST1, m_MEGAREST1, m_MEGAREST1, m_MEGAREST1,
//
//  m_MEGAB1, m_MEGAB2, m_MEGAB3, m_MEGAB4, 
//  
//};
//Motif* Songbook::s_Megalovania[16] = {
//    m_MEGA1, m_MEGAMelody, m_MEGA2, m_MEGAMelody, m_MEGA3, m_MEGAMelody, m_MEGA4, m_MEGAMelody, 
//    
//    m_MEGA1, m_MEGAMelody, m_MEGA2, m_MEGAMelody, m_MEGA3, m_MEGAMelody, m_MEGA4, m_MEGAMelody
//};
// -----------------------------------------------------------------------------------------------------------------------------------
Song Songbook::ClocktownBass = Song(s_ClocktownBass, 11, 90, 8);
Song Songbook::Clocktown = Song(s_Clocktown, 35, 90, 8);

//Song Songbook::BanneredMare = Song(s_BanneredMare, 16, 90, 8);

Song Songbook::ZeldasLullaby = Song(s_ZeldasLullaby, 7, 60, 4);

Song Songbook::DragonsBass = Song(s_DragonsBass, 46, 105, 4);
Song Songbook::Dragons = Song(s_Dragons, 36, 105, 4);

Song Songbook::HuntBass = Song(s_HuntBass, 13, 100, 8);
Song Songbook::Hunt = Song(s_Hunt, 17, 100, 8);

Song Songbook::CustomBass = Song(s_CustomBass, 12, 90, 4);

//Song Songbook::MegalovaniaBass = Song(s_MegalovaniaBass, 8, 60, 4);
//Song Songbook::Megalovania = Song(s_Megalovania, 16, 60, 4);
// -----------------------------------------------------------------------------------------------------------------------------------
/* MORE DECLARATIONS*/
void setKey(char);
void setTempo(char);
double getFreq(char);
char getMicros(double);
void setMeter(Song, unsigned char, unsigned char);
void playSong(Song, char);

Song* songChannel;
Note* currentNote;

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
// sets the meter based on the given song
void setMeter(Song song, unsigned char bPM = 0, unsigned char mTP = 0) {
  setNoteIsOneBeat(song.defaultNoteIsOneBeat);
  setTempo(song.defaultTempo);
  beatsPerMeasure = bPM;
  measuresToPlay = mTP;
}
// activates a song on the specified channel
void playSong(Song song, char channel) {
  songChannel[channel] = song;
  songLength[channel] = song.getlength();
//  motifLength[channel] = song.motifs[0]->getlength();
  playingSong[channel] = true;
}
void setup() {
  setKey('D'); // C D E F G A B // lower keys work better
//  Serial.begin(9600);
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
  /* Note the lack of a for-loop for iterating through each channel. The notes sound slightly more grainy if the commands are executed through a for-loop. */

  // goes through each channel, sees if it's playing a song
  if (playingMetronome) { // metronome is playing
    if (freq[0] != 126) {
      countf[0]++;
      if (freq[0] == countf[0]) {
        digitalWrite(pin[0], toggle[0] == 0 ? HIGH : LOW);
        toggle[0] = ~toggle[0];
        countf[0] = 0;
      }
    } else {
      countf[0] = 0;
    }
    if (countd[0] == duration[0]) {
      countd[0] = 0;
      countf[0] = 0;

      if (freq[0] != 126) { // before was beep, now rest
        duration[0] = 14 * beatInMilliseconds / noteIsOneBeat * 1000 / SPEEDCONST;
        freq[0] = 126;
      } else { // before was rest, now beep
        if (noteIndex[0] == beatsPerMeasure && motifIndex[0] == measuresToPlay) { // end of metronome
          freq[0] = 126;
          playingMetronome = false;
          noteIndex[0] = 0;
          motifIndex[0] = 0;
          duration[0] = 0;
        } else { // not end of metronome
          if (noteIndex[0] == 0 || noteIndex[0] == beatsPerMeasure) { // end of measure, proceed to next
            freq[0] = getMicros(getFreq(24));
            noteIndex[0] = 0;
            motifIndex[0]++;
          } else { // not start of measure
            freq[0] = getMicros(getFreq(12));
          }
          duration[0] = 2 * beatInMilliseconds / noteIsOneBeat * 1000 / SPEEDCONST;
          noteIndex[0]++;
        }
      }
    } else {
      countd[0]++;
    }
  } else { // metronome is no longer playing/not yet playing
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
        countf[0] = 0;
      }

      /* CHANNEL 0 */
      if (countd[0] == duration[0]) {
        countd[0] = 0;
        countf[0] = 0;
        if (noteIndex[0] < songChannel[0].motifs[motifIndex[0]]->getlength()) { // same motif as before, next note
        } else { // next motif
          motifIndex[0]++;
          noteIndex[0] = 0;
        }
        if (motifIndex[0] == songLength[0]) { // end of song
          endSong(0);
        } else {
          currentNote = &songChannel[0].motifs[motifIndex[0]]->notes[noteIndex[0]];
          duration[0] = (currentNote->duration) * beatInMilliseconds / noteIsOneBeat * 1000 / SPEEDCONST;
          freq[0] = (currentNote->distance ==  '~') ? 126 : getMicros(getFreq(currentNote->distance)); // 126? rest if true, normal frequency if not
          noteIndex[0]++;
        }
      } else {
        countd[0]++;
      }
    }
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
        countf[1] = 0;
      }

      // if the current note has played as long as it should
      if (countd[1] == duration[1]) {
        countd[1] = 0;
        countf[1] = 0;

        /* BASICALLY A TRANS-INTERRUPT FOR LOOP... OH BOY */
        // figures out what note to play next or if the song should end
        if (noteIndex[1] < songChannel[1].motifs[motifIndex[1]]->getlength()) { // same motif as before, next note
        } else { // next motif
          motifIndex[1]++;
          noteIndex[1] = 0;
        }
        if (motifIndex[1] == songLength[1]) { // end of song, reset values
          endSong(1);
        } else {
          currentNote = &songChannel[1].motifs[motifIndex[1]]->notes[noteIndex[1]];
          duration[1] = (currentNote->duration) * beatInMilliseconds / noteIsOneBeat * 1000 / SPEEDCONST;
          freq[1] = (currentNote->distance == '~' /* ascii code 126, essentially a char variable with value 126 */ ) ? 126 : getMicros(getFreq(currentNote->distance)); // 126? rest if true, normal frequency if not
          noteIndex[1]++;
        }
      } else {
        countd[1]++;
      }
    }
  }
}
// resets variables used for tracking notes, etc.
void endSong(int i) {
//  for(int i = 0; i < 2; i++) {
    toggle[i] = 0;
    freq[i] = 126;
    countf[i] = 0;
    countd[i] = 0;
    playingSong[i] = false;
    duration[i] = 0;
    noteIndex[i] = 0;
    motifIndex[i] = 0;
    songLength[i] = 0;
//    motifLength[i] = 0;
//  }
}

void loop() {
  // reading of buttons to decide what song to play
  // comments beside conditionals show what button presses activate that conditional
//  Serial.println(songChannel[0].getlength());
//  Serial.println(songChannel[1].getlength());
//  Serial.println(songLength[0]);
//  Serial.println(songLength[1]);
//  Serial.println(motifLength[0]);
//  Serial.println(motifLength[1]);
  Serial.println();
  if (!playingSong[0] && !playingSong[1]) {
    if (digitalRead(11) == HIGH || digitalRead(12) == HIGH || digitalRead(13) == HIGH) {
      delay(10);
      int state4 = digitalRead(11);
      int state5 = digitalRead(12);
      int state8 = digitalRead(13);
      if (state4 == HIGH) //Y__
        if (state5 == HIGH) //YY_
          if (state8 == HIGH) {} //YYY
      //          tone(pin[0], 880);
          else { //YYN
            setMeter(Songbook::Hunt);
            playSong(Songbook::Hunt, 0);
            playSong(Songbook::HuntBass, 1);
          }
        else //YN_
          if (state8 == HIGH) { //YNY
//            setMeter(Songbook::BanneredMare);
//            playSong(Songbook::BanneredMare, 0);
          }
          else {
            setMeter(Songbook::CustomBass, 4, 2);
            playingMetronome = true;
            playSong(Songbook::CustomBass, 0);
          } //YNN
      else  //N__
        if (state5 == HIGH) //NY_
          if (state8 == HIGH) { //NYY
//            setMeter(Songbook::Megalovania);
//            playSong(Songbook::Megalovania, 0);
//            playSong(Songbook::MegalovaniaBass, 1);
            setKey('G');
            setMeter(Songbook::ZeldasLullaby);
            playSong(Songbook::ZeldasLullaby, 0);
          }
          else { //NYN
            setKey('D');
            setMeter(Songbook::Dragons);
            playSong(Songbook::Dragons, 0);
            playSong(Songbook::DragonsBass, 1);
          }
        else  //NN_
          if (state8 == HIGH) { //NNY
            setMeter(Songbook::Clocktown);
            playSong(Songbook::Clocktown, 0);
            playSong(Songbook::ClocktownBass, 1);
          }
    }
  }
}
