#include "../include/fakefuncs.h"

bool fake_timeout_flag = false;
int pulse_order[] = {0,1,2,3,4,4,3,2,1,0}; 
uint16_t fake_pulses[] = {PULSE_A, PULSE_B,
                        PULSE_A, PULSE_B,
                        PULSE_A, PULSE_B,
                        PULSE_A, PULSE_B,
                        PULSE_A, PULSE_B};

int fake_isr_pulse_detect(){
    static int i = -1;
    i++;
    return pulse_order[i];
}