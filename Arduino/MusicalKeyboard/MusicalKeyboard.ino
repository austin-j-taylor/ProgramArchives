#include <math.h>
#include <PS2Keyboard.h>

// Frequency 'n' semitones away from Base Frequency = Base Frequency * ((2^(1/12))^n)

const int DataPin = 8;
const int IRQpin =  3;
const float key = pow(2, (1/12.0));
const float E3 = 164.81;
PS2Keyboard keyboard;
int prevNote = 0;

//returns a new value dependant on a key's distance from the bottom-left key (z), represented by the note E3.
int getDistance(char c) {
  switch (c) {
    case 32: return -2;
    // FIRST BAR:
    case 'z': return 0;
    case 'x': return 1;
    case 'c': return 2;
    case 'v': return 3;
    case 'b': return 4;
    case 'n': return 5;
    case 'm': return 6;
    case ',': return 7;
    case '.': return 8;
    case '/': return 9;
    
    // SECOND BAR:
    case 'a': return 0 + 5;
    case 's': return 1 + 5;
    case 'd': return 2 + 5;
    case 'f': return 3 + 5;
    case 'g': return 4 + 5;
    case 'h': return 5 + 5;
    case 'j': return 6 + 5;
    case 'k': return 7 + 5;
    case 'l': return 8 + 5;
    case ';': return 9 + 5;
    case '\'': return 10 + 5;
   
    // THIRD BAR:
    case 'q': return 0 + 10;
    case 'w': return 1 + 10;
    case 'e': return 2 + 10;
    case 'r': return 3 + 10;
    case 't': return 4 + 10;
    case 'y': return 5 + 10;
    case 'u': return 6 + 10;
    case 'i': return 7 + 10;
    case 'o': return 8 + 10;
    case 'p': return 9 + 10;
    case '[': return 10 + 10;
    case ']': return 11 + 10;
    case '\\': return 12 + 10;
    
    // FOURTH BAR:
    case '1': return 0 + 15;
    case '2': return 1 + 15;
    case '3': return 2 + 15;
    case '4': return 3 + 15;
    case '5': return 4 + 15;
    case '6': return 5 + 15;
    case '7': return 6 + 15;
    case '8': return 7 + 15;
    case '9': return 8 + 15;
    case '0': return 9 + 15;
    case '-': return 10 + 15;
    case '=': return 11 + 15;
    
    default: return -1;
  }
}

int getFreq(char c) {
  int distance = getDistance(c);
  if(distance > -1)
    return round(E3 * pow(key, distance));
  else if(distance == -2) // SPACEBAR
    return -2;
}

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
}

void loop() {
  if (keyboard.available()) {
    // read the next key
    char c = keyboard.read();
    int note = getFreq(c);
    if(note == -2) {
      noTone(7);
      prevNote = note;
    } else if(note > 164 && note != prevNote) {
      prevNote = note;
      Serial.print(c);
      Serial.print(" -> ");
      Serial.println(note);
      tone(7, note);
    }
  }
}
