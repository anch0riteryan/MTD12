
#ifndef _RADIO_PPM_
#define _RADIO_PPM_

#include <stdint-gcc.h>
#include <arm_math.h>

#define RADIO_PPM_MAX_US 2100
#define RADIO_PPM_MIN_US 900
#define RADIO_PPM_NEUTRO_US 1500

#define RADIO_FULLSCALE 1000

typedef struct _radio_input {
	uint16_t ppm_length; // ppm signal pulse length 1uS/LSB
	float norm;
	int16_t value;
} RadioInput;

int16_t radio_calc_fullscale (uint16_t );
float_t radio_calc_fullscale_norm (uint16_t );
float_t radio_calc_halfscale_norm (uint16_t );

#endif
