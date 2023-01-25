#include "../include/code_under_test.h"
#include <math.h>
//data structure for outputting current state
data_out_t data_out;

extern bool fake_timeout_flag;
extern uint16_t fake_pulses[NUM_FANS*2];
//ADC CODE


uint32_t convert_raw_to_temp(uint32_t raw_adc){
    uint32_t temperature = 0;
	if(0>raw_adc || raw_adc>ADC_RES){
		temperature = IMPOSSIBLE_VALUE;
	}
    else{
        float real_voltage = ((float)raw_adc/ADC_RES)*MAX_VOLT;
        float Rth = (-real_voltage*R1)/(real_voltage-V_SUPPLY);
        float a = log(Rth/(float)RES_AT_25C)/(float)BETA_TERMISTOR;
        float b = (float)1/298;
        float c = 1/(a+b);
        c = roundf(c * 100) / 100;
        temperature = (c-273)*100; 
    }
    return temperature;
}
void read_fan_pulses(collected_pulses_t pulse_set){
    int count_pulses = 0;
    int pulse_orgin = 0;
    int already_pulsed[NUM_FANS] = {0};
    while (!fake_timeout_flag && count_pulses != NUM_FANS*2){
        
        pulse_orgin = fake_isr_pulse_detect();
        switch (pulse_orgin)
        {
            case FAN_0:
                if(!already_pulsed[FAN_0]){
                    pulse_set[FAN_0].p1 = fake_pulses[FAN_0];
                    already_pulsed[FAN_0] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_0].p2 = fake_pulses[FAN_0+1];
                    count_pulses++;
                }
            break;

            case FAN_1:
                if(!already_pulsed[FAN_1]){
                    pulse_set[FAN_1].p1 = fake_pulses[FAN_1];
                    already_pulsed[FAN_1] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_1].p2 = fake_pulses[FAN_1+1];
                    count_pulses++;
                }
            break;

            case FAN_2:
                if(!already_pulsed[FAN_2]){
                    pulse_set[FAN_2].p1 = fake_pulses[FAN_2];
                    already_pulsed[FAN_2] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_2].p2 = fake_pulses[FAN_2+1];
                    count_pulses++;
                }
            break;

            case FAN_3:
                if(!already_pulsed[FAN_3]){
                    pulse_set[FAN_3].p1 = fake_pulses[FAN_3];
                    already_pulsed[FAN_3] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_3].p2 = fake_pulses[FAN_3+1];
                    count_pulses++;
                }
            break;

            case FAN_4:
                if(!already_pulsed[FAN_4]){
                    pulse_set[FAN_4].p1 = fake_pulses[FAN_3];
                    already_pulsed[FAN_3] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_4].p2 = fake_pulses[FAN_4+1];
                    count_pulses++;
                }
            break;
                    
            default:
            break;
        }
    }
    
}

uint16_t calcule_fan_speed(collected_pulses_t all_pulses){
    
}