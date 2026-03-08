#ifndef buzzer_include
#define buzzer_include

#include <stdbool.h>
#include <stdint.h>

//Used LLM to write note frequencies
// Octave 3
#define NOTE_C3   61156   // 130.81 Hz
#define NOTE_D3   54452   // 146.83 Hz
#define NOTE_E3   48482   // 164.81 Hz
#define NOTE_F3   45776   // 174.61 Hz
#define NOTE_G3   40775   // 196.00 Hz
#define NOTE_A3   36363   // 220.00 Hz
#define NOTE_B3   32395   // 246.94 Hz

// Octave 4
#define NOTE_C4   30577   // 261.63 Hz
#define NOTE_D4   27226   // 293.66 Hz
#define NOTE_E4   24241   // 329.63 Hz
#define NOTE_F4   22888   // 349.23 Hz
#define NOTE_G4   20387   // 392.00 Hz
#define NOTE_A4   18181   // 440.00 Hz
#define NOTE_B4   16197   // 493.88 Hz

// Octave 5
#define NOTE_C5   15288   // 523.25 Hz
#define NOTE_D5   13612   // 587.33 Hz
#define NOTE_E5   12120   // 659.25 Hz
#define NOTE_F5   11443   // 698.46 Hz
#define NOTE_G5   10193   // 783.99 Hz
#define NOTE_A5    9090   // 880.00 Hz
#define NOTE_B5    8098   // 987.77 Hz

#define NOTE_OFF  0       // Used to silence the buzzer

void InitializeBuzzer(void);

void SetBuzzerPeriod(uint16_t period);
void EnableBuzzer(void);
void DisableBuzzer(void);

#endif // buzzer_include