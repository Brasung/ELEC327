#include "state_machine.h"

int GetNextState(int current_state) //Update state given current state
{
    switch (current_state) {
        case MUSIC: return INTERNOTE;
        case INTERNOTE: return MUSIC; //swap between internote and note
        case BUTTONS:   return BUTTONS;  //stays in button mode
        default:    return MUSIC;
    }
}
