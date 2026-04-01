#include "music.h"
#include "colors.h"
#include "buttons.h"
#include "state_machine_logic.h"


// Define the melody as a const array 
const animation_note_t animation[] = {
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_C4, true},  .leds = &leds_blue,    .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 2},

    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 2},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 2},

    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_C4, true},  .leds = &leds_blue,    .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_C4, true},  .leds = &leds_blue,    .duration = 1},

    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_E4, true},  .leds = &leds_red,    .duration = 1},
    {.note = {NOTE_D4, true},  .leds = &leds_green,   .duration = 1},
    {.note = {NOTE_C4, true},  .leds = &leds_blue,    .duration = 4},
};

const int animation_length = sizeof(animation) / sizeof(animation_note_t);
