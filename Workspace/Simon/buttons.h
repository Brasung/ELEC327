#ifndef buttons_include
#define buttons_include

#include <stdint.h>

//I used LLMs to define notes and freqencies 

// --- Octave 2 ---
#define NOTE_C2   122305  // 65.41 Hz
#define NOTE_CS2  115440  // 69.30 Hz (C# / Db)
#define NOTE_D2   108962  // 73.42 Hz
#define NOTE_DS2  102854  // 77.78 Hz (D# / Eb)
#define NOTE_E2   97075   // 82.41 Hz
#define NOTE_F2   91627   // 87.31 Hz
#define NOTE_FS2  86486   // 92.50 Hz (F# / Gb)
#define NOTE_G2   81632   // 98.00 Hz
#define NOTE_GS2  77049   // 103.83 Hz (G# / Ab)
#define NOTE_A2   72727   // 110.00 Hz
#define NOTE_AS2  68645   // 116.54 Hz (A# / Bb)
#define NOTE_B2   64793   // 123.47 Hz

// --- Octave 3 ---
#define NOTE_C3   61156   // 130.81 Hz
#define NOTE_CS3  57724   // 138.59 Hz
#define NOTE_D3   54452   // 146.83 Hz
#define NOTE_DS3  51427   // 155.56 Hz
#define NOTE_E3   48482   // 164.81 Hz
#define NOTE_F3   45776   // 174.61 Hz
#define NOTE_FS3  43243   // 185.00 Hz
#define NOTE_G3   40775   // 196.00 Hz
#define NOTE_GS3  38526   // 207.65 Hz
#define NOTE_A3   36363   // 220.00 Hz
#define NOTE_AS3  34323   // 233.08 Hz
#define NOTE_B3   32395   // 246.94 Hz

// --- Octave 4 (Middle C) ---
#define NOTE_C4   30577   // 261.63 Hz
#define NOTE_CS4  28862   // 277.18 Hz
#define NOTE_D4   27226   // 293.66 Hz
#define NOTE_DS4  25712   // 311.13 Hz
#define NOTE_E4   24241   // 329.63 Hz
#define NOTE_F4   22888   // 349.23 Hz
#define NOTE_FS4  21622   // 369.99 Hz
#define NOTE_G4   20387   // 392.00 Hz
#define NOTE_GS4  19263   // 415.30 Hz
#define NOTE_A4   18181   // 440.00 Hz
#define NOTE_AS4  17161   // 466.16 Hz
#define NOTE_B4   16197   // 493.88 Hz

// --- Octave 5 ---
#define NOTE_C5   15288   // 523.25 Hz
#define NOTE_CS5  14431   // 554.37 Hz
#define NOTE_D5   13612   // 587.33 Hz
#define NOTE_DS5  12856   // 622.25 Hz
#define NOTE_E5   12120   // 659.25 Hz
#define NOTE_F5   11443   // 698.46 Hz
#define NOTE_FS5  10811   // 739.99 Hz
#define NOTE_G5   10193   // 783.99 Hz
#define NOTE_GS5  9631    // 830.61 Hz
#define NOTE_A5   9090    // 880.00 Hz
#define NOTE_AS5  8580    // 932.33 Hz
#define NOTE_B5   8098    // 987.77 Hz

// --- Octave 6 ---
#define NOTE_C6   7644    // 1046.50 Hz
#define NOTE_CS6  7215    // 1108.73 Hz
#define NOTE_D6   6810    // 1174.66 Hz
#define NOTE_DS6  6428    // 1244.51 Hz
#define NOTE_E6   6067    // 1318.51 Hz
#define NOTE_F6   5727    // 1396.91 Hz
#define NOTE_FS6  5405    // 1479.98 Hz
#define NOTE_G6   5102    // 1567.98 Hz
#define NOTE_GS6  4815    // 1661.22 Hz
#define NOTE_A6   4545    // 1760.00 Hz
#define NOTE_AS6  4290    // 1864.66 Hz
#define NOTE_B6   4049    // 1975.53 Hz

#define NOTE_OFF  0       // Used to silence the buzzer

void InitializeButtonGPIO(void);

// Pin numbers on GPIOA from Simon PCB
// Kicad here - https://github.com/ckemere/ELEC327/tree/master/PCBs/Simon-2026-JLC
#define SW1 ((uint32_t) 0x1 << 23)
#define SW2 ((uint32_t) 0x1 << 24)
#define SW3 ((uint32_t) 0x1 << 25)
#define SW4 ((uint32_t) 0x1 << 26)


#endif /* buttons_include */
