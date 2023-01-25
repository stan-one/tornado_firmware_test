#ifndef FAKEFUNCS_H
#define FAKEKUNCS_H

#include "../../include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define PULSE_A 1000U
#define PULSE_B 2000U

extern bool fake_timeout_flag;
extern int pulse_order[NUM_FANS*2];
extern uint16_t fake_pulses[NUM_FANS*2];

int fake_isr_pulse_detect();

#endif
