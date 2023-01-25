
#ifndef CODE_UNDER_TEST_H
#define CODE_UNDER_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "../fake/include/fakefuncs.h"
#include "config.h"

typedef char data_in_ui[35];

typedef struct data_out{
	uint32_t rpm1;
	uint32_t rpm2;
	uint32_t rpm3;
	uint32_t rpm4;
	uint32_t rpm_pump;
	uint32_t temperature;
}data_out_t;

typedef struct pulse{
	uint16_t p1;
	uint16_t p2;
}collected_pulses_t[NUM_FANS];

enum fans{FAN_0, FAN_1, FAN_2, FAN_3, FAN_4};


uint32_t convert_raw_to_temp(uint32_t raw_adc);

void read_fan_pulses(collected_pulses_t pulse_set);

uint16_t calcule_fan_speed(collected_pulses_t all_pulses);

#endif
