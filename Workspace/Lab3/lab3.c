/*
 * This template file implements an interrupt-driven infinite loop which
 * cycles a state machine with Software PWM for power saving.
 */

#include <ti/devices/msp/msp.h>
#include "delay.h"
#include "initialize_leds.h"
#include "state_machine_logic.h"

#define TIMER_LOAD_VALUE (128) //how many ticks to sleep
#define TICKS_PER_SECOND (256) 
#define BUTTON_PIN_8 (1 << 8)
int main(void)
{
    InitializeGPIO();
    
    /* --------------------------------------------------------------------- */
    /* Timer module and Sleep Mode Initialization */
    // 1. Step 1 is always to reset and enable
    TIMG0->GPRCM.RSTCTL = (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT);
    TIMG0->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);
    delay_cycles(16); // delay to enable module to turn on and reset

    // 2. Step 2 is to choose the desired clock. We want UPCLK (LFCLK) so we can use a LPM
    // TIMG0->CLKSEL = GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE;
    TIMG0->CLKSEL = GPTIMER_CLKSEL_LFCLK_SEL_ENABLE;

    // 3. By default, the timer counts down to zero and then stops. Configure it to repeat.
    TIMG0->COUNTERREGS.CTRCTL = GPTIMER_CTRCTL_REPEAT_REPEAT_1;

    // 4. Enable timer interrupt when we reach 0
    TIMG0->CPU_INT.IMASK |= GPTIMER_CPU_INT_IMASK_Z_SET;

    // 5. Enable the clock input to the timer. (The timer itself is still not enabled!)
    TIMG0->COMMONREGS.CCLKCTL = GPTIMER_CCLKCTL_CLKEN_ENABLED;
    // 6. Set sleep to be STANDBY (Rev 2025 TRM p. 227, also 2.4.2 Operating Mode Selection)
    SYSCTL->SOCLOCK.PMODECFG = SYSCTL_PMODECFG_DSLEEP_STANDBY;
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    // Set sleep to be STANDBY1 (Rev 2025 TRM Table 2-9. MSPM0Gxx ULPCLK by Operating Mode)
    SYSCTL->SOCLOCK.MCLKCFG |= SYSCTL_MCLKCFG_STOPCLKSTBY_ENABLE;
    /* --------------------------------------------------------------------- */

    int state = 0; //initialize state machine
    int pwm_tick_counter = 0; //counts from 0-3
    int one_second_counter = 0; //counts from 0-255 in normal mode, represents 1 second
    int current_led_pattern = 0; //led pattern
    int button_hold_time = 0; //1 tick = 4ms
    int long_press = 0; // 1 = pressed
    int short_press = 0; // 1 = pressed
    int clock_mode = 0; //0 = normal, 1 = hour set, 2 = minute set
    int flash_timer = 0; //counts from 0-255, representing 1 second, in all modes

    // Load timer for 256 Hz interrupt rate
    TIMG0->COUNTERREGS.LOAD = TIMER_LOAD_VALUE; 
    TIMG0->COUNTERREGS.CTRCTL |= (GPTIMER_CTRCTL_EN_ENABLED);
    NVIC_EnableIRQ(TIMG0_INT_IRQn); // Enable the timer interrupt

    //Initialize the first pattern
    current_led_pattern = GetStateOutputGPIOA(state);

while (1) {

        //PWM Logic
        if (pwm_tick_counter == 0) {

            GPIOA->DOUT31_0 = current_led_pattern; //Light up LEDs
            
        } else {
            //Turn everything off (active low)
            GPIOA->DOUT31_0 = 0xFFFFFFFF; 
        }

        // sleep
        __WFI(); 

        pwm_tick_counter++; //increment counter
        if (pwm_tick_counter >= 4) {
            //reset every 4 ticks
            pwm_tick_counter = 0;
        }

        //flash_timer cycles from 0 to 255 each second
        flash_timer++;
        if (flash_timer >= 256){ flash_timer = 0; }

        // ---- MODE DETECTION ----
        if (clock_mode == 0) {
            //CLOCK MODE
            one_second_counter++;
            //move onto next state each second and reset counter
            if (one_second_counter >= TICKS_PER_SECOND) {
                state = GetNextState(state);
                current_led_pattern = GetStateOutputGPIOA(state);
                one_second_counter = 0;
            }
        } else if (clock_mode == 1) {
            //HOUR SET MODE
            //turn hour LED off 0.5s each second
            if (flash_timer < 128){
                current_led_pattern = FlashHour(state);
            } else {
                current_led_pattern = GetStateOutputGPIOA(state);
            }
            if (short_press == 1){
                //on short_press, increment hour and reset flag
                state = IncrementHour(state);  
                short_press = 0;
            }
        } else {
            //MINUTE SET MODE
            //turn minute LED off 0.5s each second
            if (flash_timer < 128){
                current_led_pattern = FlashMinute(state);
            } else {
                current_led_pattern = GetStateOutputGPIOA(state);
            }          
            if (short_press == 1){
                //on short_press, increment minute and reset flag
                state = IncrementMinute(state); 
                short_press = 0;

            }
        }

        //BUTTON PRESS LOGIC
        if ((GPIOB->DIN31_0 & (1 << 8)) == 0) {
            //count how long button is held, one tick = 4ms
            button_hold_time++;
        } else {
            if (button_hold_time > 0){
                //on button RELEASE, check if it had just been pressed
                //then reset hold time
                if (button_hold_time > 256){
                    //if held for more than 1s, long press
                    long_press = 1;
                    button_hold_time = 0;
                } else if (button_hold_time > 2){
                    //if held less than 1s but more than 8ms, short press
                    short_press = 1;
                    button_hold_time = 0;
                } else {
                    //if held less than 8ms, ignore and reset (debounce protection)
                    button_hold_time = 0;
                }

            }
        }
    
        //cycle through modes 0-2 on long press
        if (long_press == 1){
            clock_mode++;
            if (clock_mode == 3) {
                //reset cycle
                clock_mode = 0;
            }
            //clear long press
            long_press = 0;
        }

    }
}

void TIMG0_IRQHandler(void)
{
    switch (TIMG0->CPU_INT.IIDX) {
        case GPTIMER_CPU_INT_IIDX_STAT_Z:
            break;
        default:
            break;
    }
}

//AI disclaimer: I used LLMs to debug

/*
 * Copyright (c) 2026, Caleb Kemere
 * Derived from example code which is
 *
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
