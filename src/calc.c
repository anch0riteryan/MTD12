#include <calc.h>

const float ADC_RESOLUTION = ((float ) VANA / 4095);

uint32_t calc_get_mV_from_adc12 (uint32_t scale) {
	return (uint32_t ) (scale * ADC_RESOLUTION);
}
