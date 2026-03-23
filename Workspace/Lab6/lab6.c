/*
 * Copyright (c) 2026, Caleb Kemere
 * All rights reserved, see LICENSE.md
 *
 */

#include <ti/devices/msp/msp.h>
#include "delay.h"
#include "buttons.h"
#include "timing.h"
#include "buzzer.h"
#include "leds.h"
#include "state_machine.h"

uint16_t onTxPacket[] =  {0x0, 0x0, 0xE5F0, 0x1010, 0xE510, 0x10F0, 0xE510, 0xF010, 0xE510, 0x0010, 0xFFFF, 0xFFFF};
uint16_t offTxPacket[] = {0x0, 0x0, 0xE000, 0x0000, 0xE000, 0x0000, 0xE000, 0x0000, 0xE000, 0x0000, 0xFFFF, 0xFFFF};

//define SPI packets for note lights
uint16_t c4_packet[] = {0x0,0x0, 0xE5FF,0x00FF, 0xE000,0x0000, 0xE000,0x0000, 0xE000,0x0000, 0xFFFF,0xFFFF};
uint16_t d4_packet[] = {0x0,0x0, 0xE000,0x0000, 0xE540,0x20FF, 0xE000,0x0000, 0xE000,0x0000, 0xFFFF,0xFFFF};
uint16_t e4_packet[] = {0x0,0x0, 0xE000,0x0000, 0xE000,0x0000, 0xE500,0x60FF, 0xE000,0x0000, 0xFFFF,0xFFFF};

//define SPI packets for switch lights
uint16_t sw1_packet[] = {0x0,0x0, 0xE500,0x00FF, 0xE000,0x0000, 0xE000,0x0000, 0xE000,0x0000, 0xFFFF,0xFFFF};
uint16_t sw2_packet[] = {0x0,0x0, 0xE000,0x0000, 0xE5FF,0x0000, 0xE000,0x0000, 0xE000,0x0000, 0xFFFF,0xFFFF};
uint16_t sw3_packet[] = {0x0,0x0, 0xE000,0x0000, 0xE000,0x0000, 0xE500,0xFF00, 0xE000,0x0000, 0xFFFF,0xFFFF};
uint16_t sw4_packet[] = {0x0,0x0, 0xE000,0x0000, 0xE000,0x0000, 0xE000,0x0000, 0xE500,0xFFFF, 0xFFFF,0xFFFF};


int message_len = sizeof(onTxPacket) / sizeof(onTxPacket[0]);

//function to return note SPI packet given a note
uint16_t* GetLEDPacket(uint16_t note) { 
    switch (note) {
        case NOTE_C4: return c4_packet;
        case NOTE_D4: return d4_packet;
        case NOTE_E4: return e4_packet;
        default: return offTxPacket; 
    }
}
    
int main(void)
{
    InitializeButtonGPIO();
    InitializeBuzzer();
    InitializeLEDInterface();
    InitializeTimerG0();

    // let the buzzer run for 0.1 s just so we know it's there!
    delay_cycles(1600000);
    DisableBuzzer();

    SetTimerG0Delay(20); // 20 ticks at 32 kHz is 0.6 ms
    EnableTimerG0();
    
    int state  = MUSIC; //initialize state to music mode

    //Used LLMs to generate note array
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

    int note_timer = 0;
    int internote = 0;
    int note_index = 0;

    while (1) {
        if (timer_wakeup) { // Ignore SPI wakeups
            if (state == MUSIC){ 
            //--MUSIC STATE--
            note_timer++;
                //playing a note
                if (note_timer == 1){ 
                    //only send the SPI when a note changes
                    SetBuzzerPeriod(notes[note_index]);
                    EnableBuzzer();
                    uint16_t *led = GetLEDPacket(notes[note_index]);
                    while (!SendSPIMessage(led, message_len)) {}

                }
                if (note_timer > (durations[note_index] * 1000)){ //each tick is 0.6ms, so 0.6*1000=600ms for quarter note
                    DisableBuzzer();
                    state = GetNextState(state); //swap to internote state
                    note_timer = 0;
                    while (!SendSPIMessage(offTxPacket, message_len)) {} //Turn lights off when entering internote 

                }
            }
            if (state == INTERNOTE){ 
                // INTERNOTE STATE 
                note_timer++;
                if (note_timer > (durations[note_index] * 200)){ //0.6*200=120ms internote period for quarter note
                    note_timer = 0;
                    state = GetNextState(state); //swap to music state
                    note_index++; //move on to next note
                }
            }
            if (note_index == 26){ state = BUTTONS;} //stop playing after one playthrough and enter button state
        

            //--Button Logic--
            uint32_t input = GPIOA->DIN31_0 & (SW1 + SW2 + SW3 + SW4);
            if ((input & SW1) == 0) { // active low!
                SetBuzzerPeriod(NOTE_G4);
                EnableBuzzer(); // Enable the buzzer
                state = BUTTONS; //immediately set state to BUTTONS
                while (!SendSPIMessage(sw1_packet, message_len)) {} //send SPI message for button light

            } else if ((input & SW2) == 0){
                SetBuzzerPeriod(NOTE_E4);
                EnableBuzzer(); // Enable the buzzer
                state = BUTTONS;
                while (!SendSPIMessage(sw2_packet, message_len)) {}

            } else if ((input & SW3) == 0){
                SetBuzzerPeriod(NOTE_C4);
                EnableBuzzer(); // Enable the buzzer
                state = BUTTONS;
                while (!SendSPIMessage(sw3_packet, message_len)) {}

            } else if ((input & SW4) == 0){
                SetBuzzerPeriod(NOTE_G3);
                EnableBuzzer(); // Enable the buzzer
                state = BUTTONS;
                while (!SendSPIMessage(sw4_packet, message_len)) {}
            }
            else if (state){ //ONLY DISABLE IF IN BUTTON MODE
                DisableBuzzer(); // Disable the buzzer
                while (!SendSPIMessage(offTxPacket, message_len)) {}

            }
            
         } //close timer wakeup
        
        

        __WFI(); // Go to sleep until timer counts down again.
    }
}



