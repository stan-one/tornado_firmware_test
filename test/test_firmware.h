#ifndef TEST_FIRMWARE_H
#define TEST_FIRMEARE_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/unity.h"
#include "../fake/include/fakefuncs.h"
#include "../include/code_under_test.h"

void test_adc();
void test_pulse_collection();
void test_pulse_colletion_timeout();
void test_fan_speed_calculator();
void test_process_ui();
void test_setup_data();
void test_process_led_data();

#endif