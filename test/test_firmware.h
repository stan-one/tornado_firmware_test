#ifndef TEST_FIRMWARE_H
#define TEST_FIRMEARE_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/unity.h"
#include "../fake/include/fakefuncs.h"
#include "../include/code_under_test.h"

void test_adc();
void test_pulse_collection();
void test_fan_speed_calculator();

#endif