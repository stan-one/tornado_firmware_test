
#ifndef CODE_UNDER_TEST_H
#define CODE_UNDER_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "../fake/include/fakefuncs.h"
#include "config.h"

typedef struct data_out{
	uint32_t rpm0;
	uint32_t rpm1;
	uint32_t rpm2;
	uint32_t rpm3;
	uint32_t rpm_pump;
	uint32_t temperature;
}data_out_t;

typedef struct datapack_fd{
    uint32_t pwm_f0;
    uint32_t pwm_f1;
    uint32_t pwm_f2;
    uint32_t pwm_f3;
    bool sw_1;
    bool sw_2;
    uint8_t strip_select;
    uint8_t effect_selected_fan;
    uint8_t effect_selected_strip;
    int freq_pwm;
}data_in_t;

typedef struct pulse{
	uint32_t p1;
	uint32_t p2;
}collected_pulses_t[NUM_FANS];

enum fans{FAN_0, FAN_1, FAN_2, FAN_3, FAN_4};
enum input_source{CONFIG_DATA_CASE, LED_DATA_CASE};


uint32_t convert_raw_to_temp(uint32_t raw_adc);

void read_fan_pulses(collected_pulses_t pulse_set);

void init_pulses(collected_pulses_t pulses);

void fan_speed_calculator(uint32_t speeds[], collected_pulses_t  pulses);

int route_data(char source);

bool process_buffer_command(char buff[], data_in_t *data_ui);

#endif
