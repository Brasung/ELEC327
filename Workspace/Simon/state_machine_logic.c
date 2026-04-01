#include <ti/devices/msp/msp.h>
#include "state_machine_logic.h"
#include "buzzer.h"
#include "music.h"
#include "buttons.h"
#include "leds.h"
#include "colors.h"

const uint32_t button_mask[] = {SW1, SW2, SW3, SW4};
const uint16_t button_tones[] = {NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E3};
const leds_message_t *button_colors[] = {&leds_blue, &leds_red, &leds_green, &leds_yellow};

button_t UpdateButton(button_t button, uint32_t input, uint32_t mask) {
    button_t new_button = button;

    if ((input & mask) == 0) {
        switch (button.state) {
            case BUTTON_IDLE:
                new_button.state = BUTTON_BOUNCING;
                new_button.depressed_counter = 1;
                break;
            case BUTTON_BOUNCING:
                new_button.depressed_counter = button.depressed_counter + 1;
                if (new_button.depressed_counter > BUTTON_BOUNCE_LIMIT) {
                    new_button.state = BUTTON_PRESS;
                }
                break;
            case BUTTON_PRESS:
            default:
                // The button counter stops here, so it never overflows
                break;
        }
    }
    else {
        // Before, we wanted to take action on the release. Here we don't care!
        new_button.state = BUTTON_IDLE;
        new_button.depressed_counter = 0;
    }

    return new_button;
}

state_t GetNextState(state_t current_state, uint32_t input)
{
    state_t new_state = current_state;

    // Update buttons
    int button_pressed = 0; // helper

    for (int i =0; i < 4; i++) {
        new_state.buttons[i] = UpdateButton(current_state.buttons[i], input, button_mask[i]);
        if (new_state.buttons[i].state == BUTTON_PRESS)
            button_pressed = button_pressed + 1;
        
    }

switch (current_state.mode) {
    case MODE_STARTUP: {
        // Check if any button was pressed to exit startup
        if (button_pressed > 0) {
            new_state.mode = MODE_PLAYING;
            new_state.buzzer.sound_on = false;
            new_state.leds = &leds_off;
            break;
        }

        // Play the startup animation/song
        song_state_t *ss = &new_state.song_state;
        ss->music_counter++;

        if (ss->note_state == PLAYING_NOTE) {
            new_state.buzzer.period = animation[ss->index].note.period;
            new_state.buzzer.sound_on = animation[ss->index].note.sound_on;
            new_state.leds = animation[ss->index].leds;

            if (ss->music_counter >= animation[ss->index].duration * SIXTEENTH_NOTE) {
                ss->music_counter = 0;
                ss->note_state = INTERNOTE;
            }
        } else {
            new_state.buzzer.sound_on = false;
            new_state.leds = &leds_off;

            if (ss->music_counter >= SIXTEENTH_NOTE / 4) {
                ss->music_counter = 0;
                ss->note_state = PLAYING_NOTE;
                ss->index++;
                if (ss->index >= animation_length) {
                    ss->index = 0;
                }
            }
        }
        break;
    }

    case MODE_PLAYING: {
        new_state.buzzer.sound_on = false;
        new_state.leds = &leds_off;

        for (int i = 0; i < 4; i++) {
            if (new_state.buttons[i].state == BUTTON_PRESS) {
                new_state.buzzer.period = button_tones[i];
                new_state.buzzer.sound_on = true;
                new_state.leds = button_colors[i];
                break;
            }
        }
        break;
    }

    default:
        new_state.buzzer.sound_on = false;
        new_state.leds = &leds_off;
        break;
}
    return new_state;
}

void SetBuzzerState(buzzer_state_t buzzer) {
    if (buzzer.sound_on) {
        EnableBuzzer();
    }
    else {
        DisableBuzzer();
    }

    SetBuzzerPeriod(buzzer.period);
}
