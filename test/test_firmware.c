
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

	TEST_ASSERT_EQUAL_UINT32(convert_raw_to_temp((uint32_t)IMPOSSIBLE_LOW), IMPOSSIBLE_VALUE);
	TEST_ASSERT_EQUAL_UINT32(convert_raw_to_temp((uint32_t)IMPOSSIBLE_HIGH), IMPOSSIBLE_VALUE);
	TEST_ASSERT_EQUAL_UINT32(convert_raw_to_temp((uint32_t)POS_VAL_1), TEMPERATURE_VAL_1);
	TEST_ASSERT_EQUAL_UINT32(convert_raw_to_temp((uint32_t)POS_VAL_2), TEMPERATURE_VAL_2);
}

void test_pulse_collection(){
	collected_pulses_t pulses = {0};
	read_fan_pulses(pulses);
	TEST_ASSERT_EQUAL_UINT16(pulses[0].p1, PULSE_A);
	TEST_ASSERT_EQUAL_UINT16(pulses[0].p2, PULSE_B);

	TEST_ASSERT_EQUAL_UINT16(pulses[2].p1, PULSE_A);
	TEST_ASSERT_EQUAL_UINT16(pulses[2].p2, PULSE_B);
}

void test_fan(){

}


int main(void) {

	RUN_TEST(test_adc, 1);
	RUN_TEST(test_pulse_collection);
}




