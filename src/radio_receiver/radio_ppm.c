#include <radio_ppm.h>

uint16_t radio_calc_fullscale (uint16_t len_ppm) {
	return 0;
}

float_t radio_calc_fullscale_norm (uint16_t len_ppm) {
	float_t result = 0;

	if (len_ppm < RADIO_PPM_MIN_US) {
		result = 0.0;
	} else if (len_ppm > RADIO_PPM_MAX_US) {
		result = 1.0;
	} else {
		result = (((float_t) len_ppm) - RADIO_PPM_MIN_US)/ (float_t) (RADIO_PPM_MAX_US - RADIO_PPM_MIN_US);
	}

	return result;
}

float_t radio_calc_halfscale_norm (uint16_t len_ppm) {
	float_t result = 0;

	if (len_ppm < RADIO_PPM_MIN_US) {
		result = -1.0;
	} else if (len_ppm > RADIO_PPM_MAX_US) {
		result = 1.0;
	} else {
		result = (((float_t) len_ppm) - RADIO_PPM_NEUTRO_US)/ (float_t) (RADIO_PPM_MAX_US - RADIO_PPM_MIN_US);
	}

	return result;
}
