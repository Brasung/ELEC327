#include "state_machine_logic.h"
#include <ti/devices/msp/msp.h>
//Lookup table for hour LEDs
const uint32_t hour_pins[12] = {
    (1<<0),  // 12A (PA0)
    (1<<26), // 1A  (PA26)
    (1<<24), // 2A  (PA24)
    (1<<22), // 3A  (PA22)
    (1<<18), // 4A  (PA18)
    (1<<16), // 5A  (PA16)
    (1<<14), // 6A  (PA14)
    (1<<12), // 7A  (PA12)
    (1<<10),  // 8A  (PA10)
    (1<<8),  // 9A  (PA8)
    (1<<6),  // 10A (PA6)
    (1<<28)  // 11A (PA28)
};
//Lookup table for minute LEDs
const uint32_t minute_pins[12] = {
    (1<<27), // 12B (PA27)
    (1<<25), // 1B  (PA25)
    (1<<23), // 2B  (PA23)
    (1<<21), // 3B  (PA21)
    (1<<17), // 4B  (PA17)
    (1<<15), // 5B  (PA15)
    (1<<13), // 6B  (PA13)
    (1<<11), // 7B  (PA11)
    (1<<9), // 8B  (PA9)
    (1<<7),  // 9B  (PA7)
    (1<<5),  // 10B (PA5)
    (1<<1)   // 11B (PA1)
};

int GetNextState(int current_state) //Update state given current state
{
    if (current_state < 143) {
        return current_state + 1; // Increment state by 1
    }
    else {
            //Reset to 0 if state is 144
            return 0;
    }
}

int GetStateOutputGPIOA(int current_state) {
    int hour = current_state / 12; //Get hour using integer division
    int minute = current_state % 12; //Get minute using modulus
    uint32_t hour_pin = hour_pins[hour];  //Get hour pin
    uint32_t minute_pin = minute_pins[minute]; //Get minute pin
    return ~(hour_pin | minute_pin); //Invert because LEDs are active low
}

int GetStateOutputGPIOB(int current_state) {
    return 0;
};

// Increments the hour while keeping minute the same
int IncrementHour(int current_state)
{
    int hour = current_state / 12;
    int minute = current_state % 12;

    // Increment hour and wrap around
    hour = (hour + 1) % 12;

    // Reconstruct state
    return (hour * 12) + minute;
}

// Increments the minute while keeping hour the same
int IncrementMinute(int current_state)
{
    int hour = current_state / 12;
    int minute = current_state % 12;

    // Increment minute and wrap around
    minute = (minute + 1) % 12;

    // Reconstruct state
    return (hour * 12) + minute;
}



// Returns pattern with hour off and minute on
int FlashHour(int current_state)
{
    int minute = current_state % 12;
    uint32_t minute_pin = minute_pins[minute];

    // Only invert the minute pin, which keeps the hour pin off. 
    return ~minute_pin;
}

// Returns pattern with minute off and hour on 
int FlashMinute(int current_state)
{
    int hour = current_state / 12;
    uint32_t hour_pin = hour_pins[hour];

    // Only invert the hour pin, which keeps the minute pin off. 
    return ~hour_pin;
}

