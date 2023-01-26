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
		temperature = IMPOSSIBLE_VALUE_TEMP;
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
                    pulse_set[FAN_0].p1 = fake_pulses[0];
                    already_pulsed[FAN_0] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_0].p2 = fake_pulses[5];
                    count_pulses++;
                }
            break;

            case FAN_1:
                if(!already_pulsed[FAN_1]){
                    pulse_set[FAN_1].p1 = fake_pulses[1];
                    already_pulsed[FAN_1] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_1].p2 = fake_pulses[6];
                    count_pulses++;
                }
            break;

            case FAN_2:
                if(!already_pulsed[FAN_2]){
                    pulse_set[FAN_2].p1 = fake_pulses[2];
                    already_pulsed[FAN_2] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_2].p2 = fake_pulses[7];
                    count_pulses++;
                }
            break;

            case FAN_3:
                if(!already_pulsed[FAN_3]){
                    pulse_set[FAN_3].p1 = fake_pulses[4];
                    already_pulsed[FAN_3] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_3].p2 = fake_pulses[8];
                    count_pulses++;
                }
            break;

            case FAN_4:
                if(!already_pulsed[FAN_4]){
                    pulse_set[FAN_4].p1 = fake_pulses[4];
                    already_pulsed[FAN_4] = 1;
                    count_pulses++;
                }
                else{
                    pulse_set[FAN_4].p2 = fake_pulses[9];
                    count_pulses++;
                }
            break;
                    
            default:
            break;
        }
    }
    
}

void init_pulses(collected_pulses_t pulse_set){
    for(int i = 0; i<NUM_FANS; i++){
        pulse_set[i].p1 = IMPOSSIBLE_VALUE_COUNTER;
        pulse_set[i].p2 = IMPOSSIBLE_VALUE_COUNTER;
    }
}

void fan_speed_calculator(uint32_t speeds[], collected_pulses_t  pulses){
	int elapsed_ticks = 0U;
	float elapsed_time = 0.0;
	float fan_freq = 0.0;
	int RPM = IMPOSSIBLE_VALUE_RPM;
	for(int i = 0; i<NUM_FANS; i++){
		elapsed_ticks = pulses[i].p2 - pulses[i].p1;
		elapsed_time = (float)elapsed_ticks/CLOCK_SPEED;
		fan_freq = 1/elapsed_time;
        fan_freq = roundf(fan_freq * 100) / 100;
		RPM = ((fan_freq*60)/2);
        if(RPM < MIN_SPEED_FAN || RPM > MAX_SPEED_FAN){
            speeds[i] = IMPOSSIBLE_VALUE_RPM;
        }
        else{
		    speeds[i] = RPM;
        }
	}
}

int route_data(char source){
    switch (source)
    {
    case LED_DATA:
        return LED_DATA_CASE;
        break;
    case CONFIG_DATA:
        return CONFIG_DATA_CASE;
        break;
    default:
        break;
    }
}

bool process_buffer_command(char buff[], data_in_t *data_ui){
    char *token = strtok(buff, SEPARATOR);
    uint32_t hold_num[30] = {IMPOSSIBLE_VALUE_COUNTER};
    int i = 0;
        while (token != NULL){
            hold_num[i] =  atoi(token);
            i++;
            token = strtok(NULL, SEPARATOR);
        }
        if(hold_num[9] != IMPOSSIBLE_VALUE_COUNTER){
            data_ui->pwm_f0 = hold_num[0];
            data_ui->pwm_f1 = hold_num[1];
            data_ui->pwm_f2 = hold_num[2];
            data_ui->pwm_f3 = hold_num[3];
            data_ui->sw_1 = hold_num[4];
            data_ui->sw_2 = hold_num[5];
            data_ui->strip_select = hold_num[6];
            data_ui->effect_selected_fan = hold_num[7];
            data_ui->effect_selected_strip = hold_num[8];
            data_ui->freq_pwm = hold_num[9];
            return true;
        }
        else{
            return false;
        }

}