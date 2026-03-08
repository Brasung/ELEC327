#ifndef state_machine_logic_include
#define state_machine_logic_include

int GetNextState(int current_state);

int GetStateOutputGPIOA(int current_state);

int GetStateOutputGPIOB(int current_state);

/* Define states as constants */
#define MUSIC 0
#define BUTTONS  1

#endif /* state_machine_logic_include */
