#include <ti/devices/msp/msp.h>
#include "state_machine_logic.h"
#include "buzzer.h"
#include "music.h"
#include "buttons.h"
#include "leds.h"
#include "colors.h"
#include "random.h"

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
        bool button_released = false;
        for (int i = 0; i < 4; i++) {
            //check if any of the four buttons are RELEASED
            //this means idle in current state and pressed in prev state
            if (current_state.buttons[i].state == BUTTON_PRESS && new_state.buttons[i].state == BUTTON_IDLE) {
                button_released = true;
                break;
            }
        }
        if (button_released) {
        // wait for button RELEASE
            srand(new_state.song_state.music_counter); // set random state
            new_state.mode = MODE_PLAYING; //switch to play mode
            new_state.buzzer.sound_on = false; //stop the light and sound
            new_state.leds = &leds_off;
            new_state.play_counter = -1500; //delay before the first note

            break;
        }

        //otherwise, play the startup song
        song_state_t *ss = &new_state.song_state;
        ss->music_counter++;

        if (ss->note_state == PLAYING_NOTE) {
            new_state.buzzer.period = animation[ss->index].note.period;
            new_state.buzzer.sound_on = animation[ss->index].note.sound_on;
            new_state.leds = animation[ss->index].leds;

            if (ss->music_counter >= animation[ss->index].duration * SIXTEENTH_NOTE) {
                //after playing a note, go to internote state
                ss->music_counter = 0;
                ss->note_state = INTERNOTE;
            }
        } else {
            //internote state
            new_state.buzzer.sound_on = false;
            new_state.leds = &leds_off;
            //lasts quarter of sixteenth note
            if (ss->music_counter >= SIXTEENTH_NOTE / 4) {
                ss->music_counter = 0;
                //go onto the next note
                ss->note_state = PLAYING_NOTE;
                ss->index++;
                if (ss->index >= animation_length) {
                    //loop song
                    ss->index = 0;
                }
            }
        }
        break;
    }

    case MODE_PLAYING: {
    //add a new random note only on the first tick
    if (new_state.show_index == 0 && new_state.play_counter == -1500) {
        //this only runs when it first transitions to the state
        new_state.sequence[new_state.sequence_length] = rand();
        new_state.sequence_length++;
    }

    uint8_t current_note = new_state.sequence[new_state.show_index];
    new_state.play_counter++; //counter for note duration

    uint32_t note_duration = SIXTEENTH_NOTE * 4;
    uint32_t gap_duration = SIXTEENTH_NOTE * 4;

if (new_state.play_counter >= 0){ //wait for counter to reach 0
    if (new_state.play_counter <= note_duration) {
        //play the note
        new_state.buzzer.period = button_tones[current_note];
        new_state.buzzer.sound_on = true;
        new_state.leds = button_colors[current_note];
    } else if (new_state.play_counter <= note_duration + gap_duration) {
        //silent gap
        new_state.buzzer.sound_on = false;
        new_state.leds = &leds_off;
    } else {
        //advance to next note
        new_state.play_counter = 0;
        new_state.show_index++;
        if (new_state.show_index >= new_state.sequence_length) {
            //done showing, switch to wait mode
            new_state.show_index = 0;
            new_state.input_index = 0;
            new_state.mode = MODE_WAIT;
            new_state.buzzer.sound_on = false;
            new_state.leds = &leds_off;
            new_state.play_counter = 0;
        }
    }}
    break;
    }
case MODE_WAIT: {
    new_state.buzzer.sound_on = false;
    new_state.leds = &leds_off;

    new_state.play_counter++; //timeout timer

    for (int i = 0; i < 4; i++) {
        if (new_state.buttons[i].state == BUTTON_PRESS) {
            //light up and play tone while held
            new_state.buzzer.period = button_tones[i];
            new_state.buzzer.sound_on = true;
            new_state.leds = button_colors[i];
            
            //check on first tick of press only
            if (current_state.buttons[i].state != BUTTON_PRESS) {
                new_state.play_counter = 0; //reset timeout timer

                if (i == new_state.sequence[new_state.input_index]) {
                    //correct input - go on to check next input
                    new_state.input_index++;
                } else {
                    // incorrect input
                    new_state.mode = MODE_LOSE;
                    //restart the song
                    new_state.song_state.index = 0;
                    new_state.song_state.music_counter = 0;
                    new_state.song_state.note_state = PLAYING_NOTE;
                }
            }
            //break;
        }

        //detect button release
        if (current_state.buttons[i].state == BUTTON_PRESS && new_state.buttons[i].state == BUTTON_IDLE) {
            //check if sequence is complete on release
            if (new_state.input_index >= new_state.sequence_length) {
                if (new_state.input_index >= MAX_SEQUENCE) {
                    //if correct sequence long enough, then win
                    new_state.mode = MODE_WIN;
                    //restart the song
                    new_state.song_state.index = 0;
                    new_state.song_state.music_counter = 0;
                    new_state.song_state.note_state = PLAYING_NOTE;
                } else {
                    //go back to play mode with delay before the first note
                    new_state.show_index = 0;
                    new_state.play_counter = -1500; //delay before playing 
                    new_state.mode = MODE_PLAYING;
                }
            }
            break;
        }
    }
        if (new_state.play_counter > 10000){ //auto lose timer 
            new_state.mode = MODE_LOSE;
            //restart the song
            new_state.song_state.index = 0;
            new_state.song_state.music_counter = 0;
            new_state.song_state.note_state = PLAYING_NOTE;
    }
    break;
} case MODE_LOSE: {
    //on game loss, play lose song
    song_state_t *ss = &new_state.song_state;
        ss->music_counter++;

        if (ss->note_state == PLAYING_NOTE) {
            new_state.buzzer.period = lose_song[ss->index].note.period;
            new_state.buzzer.sound_on = lose_song[ss->index].note.sound_on;
            new_state.leds = lose_song[ss->index].leds;

            if (ss->music_counter >= lose_song[ss->index].duration * SIXTEENTH_NOTE) {
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
                if (ss->index >= lose_song_length) {
                    ss->index = 0;
                }
            }
        }
    break;
} case MODE_WIN: {
    //on game win, play win song
    song_state_t *ss = &new_state.song_state;
        ss->music_counter++;

        if (ss->note_state == PLAYING_NOTE) {
            new_state.buzzer.period = win_song[ss->index].note.period;
            new_state.buzzer.sound_on = win_song[ss->index].note.sound_on;
            new_state.leds = win_song[ss->index].leds;

            if (ss->music_counter >= win_song[ss->index].duration * SIXTEENTH_NOTE) {
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
                if (ss->index >= win_song_length) {
                    ss->index = 0;
                }
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
