#ifndef __TONE_PLAYER_H__
#define __TONE_PLAYER_H__

#include "Time.h"

#define TONE_VOICES 1
#define TONE_PINS {4};

struct toneNote {
  int length;
  int noteFreq;
  
  toneNote(int len, int freq) { 
    length = len; 
    noteFreq = freq; 
  }
};

#define NOTE_PAUSE -1
#define NOTE_STOP 0
#define tonePause(LENGTH) toneNote(NOTE_PAUSE, LENGTH)
#define toneEnd() toneNote(NOTE_STOP, 0)

class TonePlayerAsync {
  toneNote* currentMelody;
  int currentNoteIndex = 0;
  int voices = 1;
  int tonePin = 4;
  time_t nextToneTime;

public:

  void Init() { 

  }
  
  void PlayNote(int timeMs, int noteFreq, time_t currentTime) {
    nextToneTime = currentTime + timeMs;
    if (noteFreq > 0) {
      tone(tonePin, noteFreq);
    } else {
      noTone(tonePin);
      if (noteFreq == NOTE_STOP) {
        currentMelody = NULL;
      }
    }
  }
  
  void PlayMelody(toneNote* pMelody, int currentTime) {
    currentMelody = pMelody;
    currentNoteIndex = 0;
    PlayNote(pMelody[0].length, pMelody[0].noteFreq, currentTime);
  }
  
  void ClearMelody() { 
    currentMelody = NULL;
    currentNoteIndex = 0;
    nextToneTime = 0;
  }
  
  void Update(time_t currentTime) { 
    // Stop tone 
    if (currentTime >= nextToneTime) {
      
      // Next note in melody
      if (currentMelody != NULL) {
        currentNoteIndex++;
        PlayNote(currentMelody[currentNoteIndex].length, currentMelody[currentNoteIndex].noteFreq, currentTime);
      }
    }
    
  }
};

#endif
