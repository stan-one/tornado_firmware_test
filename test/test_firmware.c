
#include "test_firmware.h"

extern data_out_t data_out;

void setUp(){

};
void tearDown(){

};

//TESTS
void test_adc(){
	 enum ADC_VALUES_E{
		IMPOSSIBLE_LOW = -1000,
		IMPOSSIBLE_HIGH = 6000,
		POS_VAL_1 = 1675,
		POS_VAL_2 = 2048};

	uint32_t TEMPERATURE_VAL_1 = 3500;//35.00deg
	uint32_t TEMPERATURE_VAL_2 = 2500;//25.00deg

	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_TEMP, convert_raw_to_temp((uint32_t)IMPOSSIBLE_LOW));
	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_TEMP, convert_raw_to_temp((uint32_t)IMPOSSIBLE_HIGH));
	TEST_ASSERT_EQUAL_UINT32(TEMPERATURE_VAL_1, convert_raw_to_temp((uint32_t)POS_VAL_1));
	TEST_ASSERT_EQUAL_UINT32(TEMPERATURE_VAL_2, convert_raw_to_temp((uint32_t)POS_VAL_2));
}

void test_pulse_collection(){
	collected_pulses_t pulses;
	init_pulses(pulses);
	read_fan_pulses(pulses);
	TEST_ASSERT_EQUAL_UINT32(PULSE_A, pulses[0].p1);
	TEST_ASSERT_EQUAL_UINT32(PULSE_B, pulses[0].p2);

	TEST_ASSERT_EQUAL_UINT32(PULSE_A, pulses[1].p1);
	TEST_ASSERT_EQUAL_UINT32(PULSE_B, pulses[1].p2);

	TEST_ASSERT_EQUAL_UINT32(PULSE_A, pulses[2].p1);
	TEST_ASSERT_EQUAL_UINT32(PULSE_B, pulses[2].p2);

	TEST_ASSERT_EQUAL_UINT32(PULSE_A, pulses[3].p1);
	TEST_ASSERT_EQUAL_UINT32(PULSE_B, pulses[3].p2);

	TEST_ASSERT_EQUAL_UINT32(PULSE_A, pulses[4].p1);
	TEST_ASSERT_EQUAL_UINT32(PULSE_B, pulses[4].p2);

}

void test_pulse_colletion_timeout(){
	fake_timeout_flag = true;
	collected_pulses_t pulses;
	init_pulses(pulses);
	read_fan_pulses(pulses);

	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_COUNTER, pulses[0].p1);
	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_COUNTER, pulses[0].p2);

	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_COUNTER, pulses[4].p1);
	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_COUNTER, pulses[4].p2);

}

void test_fan_speed_calculator(){
	uint32_t fan_speeds[5] = {IMPOSSIBLE_VALUE_RPM};
	collected_pulses_t pulses;
	init_pulses(pulses);
	pulses[0].p1 = 0; pulses[0].p2 = FAKE_60HZ;
	pulses[1].p1 = 0; pulses[1].p2 = FAKE_100HZ;
	pulses[2].p1 = PULSE_A; pulses[2].p2 = 0;
	fan_speed_calculator(fan_speeds, pulses);
	TEST_ASSERT_EQUAL_UINT32(FAKE_60HZ_RPM, fan_speeds[0]);
	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_RPM, fan_speeds[1]);
	TEST_ASSERT_EQUAL_UINT32(IMPOSSIBLE_VALUE_RPM, fan_speeds[2]);

}

void test_process_ui(){
	char buffer[] = "$80;76;56;44;1;1;1;1;20000#";
	data_in_t formated_in;
	TEST_ASSERT_EQUAL_INT(1, process_buffer_command(buffer+1, &formated_in));
	TEST_ASSERT_EQUAL_UINT32(80, formated_in.pwm_f0);
	TEST_ASSERT_EQUAL_UINT32(76, formated_in.pwm_f1);
	TEST_ASSERT_EQUAL_UINT32(1, formated_in.sw_1);
	TEST_ASSERT_EQUAL_UINT32(20000, formated_in.freq_pwm);
}

void test_setup_data(){
	char buffer[] = "&12;20#";
	led_setup_t led_setup;
	TEST_ASSERT_EQUAL_INT(1, process_setup_data(buffer+1, &led_setup));
	TEST_ASSERT_EQUAL_UINT32(12, led_setup.num_led_fan);
	TEST_ASSERT_EQUAL_UINT32(20, led_setup.num_led_strip);

}

void test_process_led_data(){
	char buffer[] = "@16;16;16|24;24;24#";
	int num_leds = 2;
	uint32_t effect[30] = {0};
	process_led_effect_data(buffer+1, effect);
	TEST_ASSERT_EQUAL_UINT32((16<<16) | (16<<8) |  (16), effect[0]);
	TEST_ASSERT_EQUAL_UINT32((24<<16) | (24<<8) |  (24), effect[1]);
}



int main(void) {
	RUN_TEST(test_adc, 1);
	RUN_TEST(test_pulse_collection, 2);
	RUN_TEST(test_pulse_colletion_timeout, 3);
	RUN_TEST(test_fan_speed_calculator, 4);
	RUN_TEST(test_process_ui, 5);
	RUN_TEST(test_setup_data, 6);
	RUN_TEST(test_process_led_data, 7);
}