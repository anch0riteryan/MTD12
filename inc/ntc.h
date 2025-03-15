#ifndef _NTC_
#define _NTC_

#include <stdint.h>
#include <math.h>

//ntc.c
int16_t ntc_calc_temperature_from_r_ntc (uint32_t );
uint32_t ntc_calc_r_ntc_from_analog (uint32_t );

#endif