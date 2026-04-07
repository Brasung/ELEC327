#include "music.h"
#include "colors.h"
#include "buttons.h"
#include "state_machine_logic.h"


// Define the melody as a const array 
// I used LLMs to convert notes to array

//STARTUP SONG - A Cyber's World by Toby Fox 
const animation_note_t animation[] = {
{.note={NOTE_CS5, true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_C5,  true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_C5,  true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_GS4, true}, .leds=&leds_blue,   .duration=1}, {.note={NOTE_F4,  true}, .leds=&leds_green,  .duration=1},
    {.note={NOTE_GS4, true}, .leds=&leds_red,    .duration=3}, {.note={NOTE_CS4, true}, .leds=&leds_yellow, .duration=1},
    {.note={NOTE_DS4, true}, .leds=&leds_blue,   .duration=1}, {.note={NOTE_CS4, true}, .leds=&leds_green,  .duration=1},

    {.note={NOTE_CS5, true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_C5,  true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_C5,  true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_GS4, true}, .leds=&leds_red,    .duration=1}, {.note={NOTE_F4,  true}, .leds=&leds_yellow, .duration=1},
    {.note={NOTE_GS4, true}, .leds=&leds_blue,   .duration=3}, {.note={NOTE_CS4, true}, .leds=&leds_green,  .duration=1},
    {.note={NOTE_DS4, true}, .leds=&leds_red,    .duration=1}, {.note={NOTE_CS4, true}, .leds=&leds_yellow, .duration=1},

    {.note={NOTE_F4,  true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_F4,  true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_DS4, true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_DS4, true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_CS4, true}, .leds=&leds_blue,   .duration=1}, {.note={NOTE_C4,  true}, .leds=&leds_green,  .duration=1},
    {.note={NOTE_CS4, true}, .leds=&leds_red,    .duration=3}, {.note={NOTE_GS4, true}, .leds=&leds_yellow, .duration=1},
    {.note={NOTE_AS4, true}, .leds=&leds_blue,   .duration=1}, {.note={NOTE_GS4, true}, .leds=&leds_green,  .duration=1},

    {.note={NOTE_F5,  true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_FS5, true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_F5,  true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_DS5, true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_CS5, true}, .leds=&leds_red,    .duration=1}, {.note={NOTE_C5,  true}, .leds=&leds_yellow, .duration=1},
    {.note={NOTE_CS5, true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_GS4, true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_AS4, true}, .leds=&leds_red,    .duration=2},

    {.note={NOTE_CS5, true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_C5,  true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_C5,  true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_GS4, true}, .leds=&leds_yellow, .duration=1}, {.note={NOTE_F4,  true}, .leds=&leds_blue,   .duration=1},
    {.note={NOTE_GS4, true}, .leds=&leds_green,  .duration=3}, {.note={NOTE_CS4, true}, .leds=&leds_red,    .duration=1},
    {.note={NOTE_DS4, true}, .leds=&leds_yellow, .duration=1}, {.note={NOTE_CS4, true}, .leds=&leds_blue,   .duration=1},

    {.note={NOTE_CS5, true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_C5,  true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_C5,  true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_GS4, true}, .leds=&leds_green,  .duration=1}, {.note={NOTE_F4,  true}, .leds=&leds_red,    .duration=1},
    {.note={NOTE_GS4, true}, .leds=&leds_yellow, .duration=3}, {.note={NOTE_CS4, true}, .leds=&leds_blue,   .duration=1},
    {.note={NOTE_DS4, true}, .leds=&leds_green,  .duration=1}, {.note={NOTE_CS4, true}, .leds=&leds_red,    .duration=1},

    {.note={NOTE_F4,  true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_F4,  true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_DS4, true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_DS4, true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_CS4, true}, .leds=&leds_yellow, .duration=1}, {.note={NOTE_C4,  true}, .leds=&leds_blue,   .duration=1},
    {.note={NOTE_CS4, true}, .leds=&leds_green,  .duration=3}, {.note={NOTE_GS4, true}, .leds=&leds_red,    .duration=1},
    {.note={NOTE_AS4, true}, .leds=&leds_yellow, .duration=1}, {.note={NOTE_GS4, true}, .leds=&leds_blue,   .duration=1},

    {.note={NOTE_F6,  true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_FS6, true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_F6,  true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_DS6, true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_CS6, true}, .leds=&leds_green,  .duration=1}, {.note={NOTE_C6,  true}, .leds=&leds_red,    .duration=1},
    {.note={NOTE_CS6, true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_GS5, true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_AS5, true}, .leds=&leds_green,  .duration=2},

    {.note={NOTE_CS6, true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_CS6, true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_C6,  true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_C6,  true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_GS5, true}, .leds=&leds_red,    .duration=1}, {.note={NOTE_F5,  true}, .leds=&leds_yellow, .duration=1},
    {.note={NOTE_GS5, true}, .leds=&leds_blue,   .duration=3}, {.note={NOTE_CS5, true}, .leds=&leds_green,  .duration=1},
    {.note={NOTE_DS5, true}, .leds=&leds_red,    .duration=1}, {.note={NOTE_CS5, true}, .leds=&leds_yellow, .duration=1},

    {.note={NOTE_CS6, true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_CS6, true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_C6,  true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_C6,  true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_GS5, true}, .leds=&leds_blue,   .duration=1}, {.note={NOTE_F5,  true}, .leds=&leds_green,  .duration=1},
    {.note={NOTE_GS5, true}, .leds=&leds_red,    .duration=3}, {.note={NOTE_CS5, true}, .leds=&leds_yellow, .duration=1},
    {.note={NOTE_DS5, true}, .leds=&leds_blue,   .duration=1}, {.note={NOTE_CS5, true}, .leds=&leds_green,  .duration=1},

    {.note={NOTE_F5,  true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_F5,  true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_DS5, true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_DS5, true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_CS5, true}, .leds=&leds_red,    .duration=1}, {.note={NOTE_C5,  true}, .leds=&leds_yellow, .duration=1},
    {.note={NOTE_CS5, true}, .leds=&leds_blue,   .duration=3}, {.note={NOTE_GS5, true}, .leds=&leds_green,  .duration=1},
    {.note={NOTE_AS5, true}, .leds=&leds_red,    .duration=1}, {.note={NOTE_GS5, true}, .leds=&leds_yellow, .duration=1},

    {.note={NOTE_F6,  true}, .leds=&leds_blue,   .duration=2}, {.note={NOTE_FS6, true}, .leds=&leds_green,  .duration=2},
    {.note={NOTE_F6,  true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_DS6, true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_CS6, true}, .leds=&leds_blue,   .duration=1}, {.note={NOTE_C6,  true}, .leds=&leds_green,  .duration=1},
    {.note={NOTE_CS6, true}, .leds=&leds_red,    .duration=2}, {.note={NOTE_GS5, true}, .leds=&leds_yellow, .duration=2},
    {.note={NOTE_AS5, true}, .leds=&leds_blue,   .duration=2},

    {.note={NOTE_CS6, true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_CS6, true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_C6,  true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_C6,  true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_GS5, true}, .leds=&leds_green,  .duration=1}, {.note={NOTE_F5,  true}, .leds=&leds_red,    .duration=1},
    {.note={NOTE_GS5, true}, .leds=&leds_yellow, .duration=3}, {.note={NOTE_CS5, true}, .leds=&leds_blue,   .duration=1},
    {.note={NOTE_DS5, true}, .leds=&leds_green,  .duration=1}, {.note={NOTE_CS5, true}, .leds=&leds_red,    .duration=1},

    {.note={NOTE_CS6, true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_CS6, true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_C6,  true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_C6,  true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_GS5, true}, .leds=&leds_yellow, .duration=1}, {.note={NOTE_F5,  true}, .leds=&leds_blue,   .duration=1},
    {.note={NOTE_GS5, true}, .leds=&leds_green,  .duration=3}, {.note={NOTE_C6,  true}, .leds=&leds_red,    .duration=1},
    {.note={NOTE_CS6, true}, .leds=&leds_yellow, .duration=1}, {.note={NOTE_DS6, true}, .leds=&leds_blue,   .duration=1},

    {.note={NOTE_F6,  true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_F6,  true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_DS6, true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_DS6, true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_CS6, true}, .leds=&leds_green,  .duration=1}, {.note={NOTE_C6,  true}, .leds=&leds_red,    .duration=1},
    {.note={NOTE_CS6, true}, .leds=&leds_yellow, .duration=3}, {.note={NOTE_GS5, true}, .leds=&leds_blue,   .duration=1},
    {.note={NOTE_AS5, true}, .leds=&leds_green,  .duration=1}, {.note={NOTE_GS5, true}, .leds=&leds_red,    .duration=1},

    {.note={NOTE_F6,  true}, .leds=&leds_yellow, .duration=2}, {.note={NOTE_GS6, true}, .leds=&leds_blue,   .duration=2},
    {.note={NOTE_F6,  true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_DS6, true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_CS6, true}, .leds=&leds_yellow, .duration=1}, {.note={NOTE_C6,  true}, .leds=&leds_blue,   .duration=1},
    {.note={NOTE_CS6, true}, .leds=&leds_green,  .duration=2}, {.note={NOTE_GS5, true}, .leds=&leds_red,    .duration=2},
    {.note={NOTE_AS5, true}, .leds=&leds_yellow, .duration=2}
};

const int animation_length = sizeof(animation) / sizeof(animation_note_t);


//LOSE SONG - Fallen Down by Toby Fox 
const animation_note_t lose_song[] = {
{.note={NOTE_FS5, true}, .leds=&leds_blue, .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_green, .duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_red,  .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_yellow,.duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_blue, .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_green, .duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_red,  .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_yellow,.duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_blue, .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_green, .duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_red,  .duration=2}, {.note={NOTE_CS5, true}, .leds=&leds_yellow,.duration=2},
    
    // Beats 7 to 8
    {.note={NOTE_B4,  true}, .leds=&leds_blue, .duration=2}, {.note={NOTE_A4,  true}, .leds=&leds_green, .duration=2},
    {.note={NOTE_CS5, true}, .leds=&leds_on,  .duration=4}, 

    // Beats 9 to 12.5
    {.note={NOTE_A4,  true}, .leds=&leds_yellow,.duration=2}, {.note={NOTE_B4,  true}, .leds=&leds_blue, .duration=2},
    {.note={NOTE_E5,  true}, .leds=&leds_green, .duration=2}, {.note={NOTE_DS5, true}, .leds=&leds_red,  .duration=2},
    {.note={NOTE_E5,  true}, .leds=&leds_yellow,.duration=2}, {.note={NOTE_FS5, true}, .leds=&leds_blue, .duration=2},
    {.note={NOTE_DS5, true}, .leds=&leds_green, .duration=2}, {.note={NOTE_B4,  true}, .leds=&leds_red,  .duration=2},

    // Beats 13 to 17.5
    {.note={NOTE_FS5, true}, .leds=&leds_yellow,.duration=2}, {.note={NOTE_B4,  true}, .leds=&leds_blue, .duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_green, .duration=2}, {.note={NOTE_B4,  true}, .leds=&leds_red,  .duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_yellow,.duration=2}, {.note={NOTE_B4,  true}, .leds=&leds_blue, .duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_green, .duration=2}, {.note={NOTE_AS4, true}, .leds=&leds_red,  .duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_yellow,.duration=2}, {.note={NOTE_AS4, true}, .leds=&leds_blue, .duration=2},

    // Beats 18 to 24
    {.note={NOTE_G5,  true}, .leds=&leds_green, .duration=4},
    {.note={NOTE_FS5, true}, .leds=&leds_red,  .duration=2}, {.note={NOTE_D5,  true}, .leds=&leds_yellow,.duration=2},
    {.note={NOTE_FS5, true}, .leds=&leds_blue, .duration=2}, {.note={NOTE_D5,  true}, .leds=&leds_green, .duration=2},
    {.note={NOTE_E5,  true}, .leds=&leds_red,  .duration=2}, {.note={NOTE_FS5, true}, .leds=&leds_yellow,.duration=2},
    {.note={NOTE_E5,  true}, .leds=&leds_blue, .duration=4},
    {.note={NOTE_D5,  true}, .leds=&leds_green, .duration=4},
    {.note={NOTE_CS5, true}, .leds=&leds_on,  .duration=4},
};

const int lose_song_length = sizeof(lose_song) / sizeof(animation_note_t);

//WIN SONG - Megalovania by Toby Fox 
const animation_note_t win_song[] = {
    // --- Measure 1 (Root C4) ---
    {.note = {NOTE_C4, true},  .leds = &leds_blue,   .duration = 1},
    {.note = {NOTE_C4, true},  .leds = &leds_blue,   .duration = 1},
    {.note = {NOTE_C5, true},  .leds = &leds_red,    .duration = 2},
    {.note = {NOTE_G4, true},  .leds = &leds_green,  .duration = 3}, 
    {.note = {NOTE_FS4, true}, .leds = &leds_yellow, .duration = 2}, 
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 2},
    {.note = {NOTE_DS4, true}, .leds = &leds_red,    .duration = 2}, 
    {.note = {NOTE_C4, true},  .leds = &leds_green,  .duration = 1},
    {.note = {NOTE_DS4, true}, .leds = &leds_yellow, .duration = 1},
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 1},

    // --- Measure 2 (Root Bb3) ---
    {.note = {NOTE_AS3, true}, .leds = &leds_blue,   .duration = 1}, 
    {.note = {NOTE_AS3, true}, .leds = &leds_blue,   .duration = 1},
    {.note = {NOTE_C5, true},  .leds = &leds_red,    .duration = 2},
    {.note = {NOTE_G4, true},  .leds = &leds_green,  .duration = 3},
    {.note = {NOTE_FS4, true}, .leds = &leds_yellow, .duration = 2},
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 2},
    {.note = {NOTE_DS4, true}, .leds = &leds_red,    .duration = 2},
    {.note = {NOTE_C4, true},  .leds = &leds_green,  .duration = 1},
    {.note = {NOTE_DS4, true}, .leds = &leds_yellow, .duration = 1},
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 1},

    // --- Measure 3 (Root A3) ---
    {.note = {NOTE_A3, true},  .leds = &leds_blue,   .duration = 1}, 
    {.note = {NOTE_A3, true},  .leds = &leds_blue,   .duration = 1},
    {.note = {NOTE_C5, true},  .leds = &leds_red,    .duration = 2},
    {.note = {NOTE_G4, true},  .leds = &leds_green,  .duration = 3},
    {.note = {NOTE_FS4, true}, .leds = &leds_yellow, .duration = 2},
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 2},
    {.note = {NOTE_DS4, true}, .leds = &leds_red,    .duration = 2},
    {.note = {NOTE_C4, true},  .leds = &leds_green,  .duration = 1},
    {.note = {NOTE_DS4, true}, .leds = &leds_yellow, .duration = 1},
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 1},

    // --- Measure 4 (Root Ab3) ---
    {.note = {NOTE_GS3, true}, .leds = &leds_blue,   .duration = 1}, 
    {.note = {NOTE_GS3, true}, .leds = &leds_blue,   .duration = 1},
    {.note = {NOTE_C5, true},  .leds = &leds_red,    .duration = 2},
    {.note = {NOTE_G4, true},  .leds = &leds_green,  .duration = 3},
    {.note = {NOTE_FS4, true}, .leds = &leds_yellow, .duration = 2},
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 2},
    {.note = {NOTE_DS4, true}, .leds = &leds_red,    .duration = 2},
    {.note = {NOTE_C4, true},  .leds = &leds_green,  .duration = 1},
    {.note = {NOTE_DS4, true}, .leds = &leds_yellow, .duration = 1},
    {.note = {NOTE_F4, true},  .leds = &leds_blue,   .duration = 1}
};

const int win_song_length = sizeof(win_song) / sizeof(animation_note_t);
