#ifndef FAKEFUNCS_H
#define FAKEFUNCS_H

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

enum fake_pulses_hz{FAKE_60HZ = 800, FAKE_100HZ = 480};
enum fake_rpm{FAKE_60HZ_RPM = 1800};


int fake_isr_pulse_detect();

#endif
