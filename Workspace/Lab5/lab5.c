
/*
 * Copyright (c) 2026, Caleb Kemere
 * All rights reserved, see LICENSE.md
 *
 */

#include <ti/devices/msp/msp.h>
#include "hw_interface.h"

int main(void)
{
    InitializeGPIO();

    InitializeTimerG0();
    InitializeTimerA1_PWM();

    // let the buzzer run for 0.1 s just so we know it's there!
    delay_cycles(1600000);
    TIMA1->COUNTERREGS.CTRCTL &= ~(GPTIMER_CTRCTL_EN_ENABLED); // Disable the buzzer

    SetTimerG0Delay(20); // 20 ticks at 32 kHz is 0.6 ms
    EnableTimerG0();

    //Used LLM to write note array
    uint16_t notes[] = {
        NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4,   NOTE_E4, NOTE_E4, NOTE_E4,
        NOTE_D4, NOTE_D4, NOTE_D4,             NOTE_E4, NOTE_E4, NOTE_E4,
        NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4,   NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4,
        NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4,   NOTE_C4
    };
    //Quarter note = 1, half note = 2, whole note = 4
    uint16_t durations[] = { 
        1, 1, 1, 1,   1, 1, 2,
        1, 1, 2,      1, 1, 2,
        1, 1, 1, 1,   1, 1, 1, 1,
        1, 1, 1, 1,   4
    };

    int button_pressed = 0;
    int note_timer = 0;
    int internote = 0;
    int note_index = 0;
    // VERY BASIC LOOP - If button 1 signals a 0, enable the PWM
    while (1) {
        if (button_pressed == 0){
        //--Melody Logic--
            note_timer++;
            if (internote == 0){ 
                //playing a note
                SetTimerA1Period(notes[note_index]);
                EnableTimerA1PWM();
                if (note_timer > (durations[note_index] * 1000)){ //each tick is 0.6ms, so 0.6*1000=600ms for quarter note
                    DisableTimerA1PWM();
                    internote = 1; //enter internote state
                    note_timer = 0;
                }
            }
            if (internote == 1){ //internote state
                if (note_timer > (durations[note_index] * 100)){ //0.6*100=60ms internote period for quarter note
                    note_timer = 0;
                    internote = 0;
                    note_index++; //move on to next note
                }
            }
            if (note_index == 26){ button_pressed = 1;} //stop playing after one playthrough
        }  

        //--Button Logic--
        uint32_t input = GPIOA->DIN31_0 & (SW1 + SW2 + SW3 + SW4);
        if ((input & SW1) == 0) { // active low!
            SetTimerA1Period(NOTE_G4);
            EnableTimerA1PWM(); // Enable the buzzer
            button_pressed = 1;
        } else if ((input & SW2) == 0){
            SetTimerA1Period(NOTE_E4);
            EnableTimerA1PWM(); // Enable the buzzer
            button_pressed = 1;
        } else if ((input & SW3) == 0){
            SetTimerA1Period(NOTE_C4);
            EnableTimerA1PWM(); // Enable the buzzer
            button_pressed = 1;
        } else if ((input & SW4) == 0){
            SetTimerA1Period(NOTE_G3);
            EnableTimerA1PWM(); // Enable the buzzer
            button_pressed = 1;
        }
        else if (button_pressed == 1){ //ONLY DISABLE IF IN BUTTON MODE
            DisableTimerA1PWM(); // Disable the buzzer
        }


        // The above is just a basic example I expect you to implement functions that look something like this:
        // SetPWMPeriodAndEnablement(state);
        // state = GetNextState(state, input);

        __WFI(); // Go to sleep until timer counts down again.
    }

}


