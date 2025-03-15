#include <bldc.h>
#include <bldc_const.h>

uint32_t bldc_calc_rpm_to_interval (uint32_t rpm) {
	uint32_t interval = 0;
	float tmp = (float) rpm / 60.0 * 42;

	tmp = 1000000 / tmp; // to uS

	interval = (uint32_t) tmp;

	return interval;
}

float bldc_calc_interval_to_rpm (uint32_t interval) {
	float rpm = 0;

	uint32_t tmp = interval * 42;

	rpm = 60000000.0 / tmp;

	return rpm;
}
