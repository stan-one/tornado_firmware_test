#include "../include/fakefuncs.h"

bool fake_timeout_flag = false;
int pulse_order[] = {0,1,2,3,4,0,1,2,3,4}; 
uint16_t fake_pulses[] = {PULSE_A, PULSE_A,
                        PULSE_A, PULSE_A,
                        PULSE_A, PULSE_B,
                        PULSE_B, PULSE_B,
                        PULSE_B, PULSE_B};

char fake_data_buffer[USB_BUFFER_SIZE] = {0};

int fake_isr_pulse_detect(){
    static int i = 0;
    return pulse_order[i++];
}