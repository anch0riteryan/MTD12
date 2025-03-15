
#ifndef _MTD_BLDC_
#define _MTD_BLDC_

#include <sam.h>
#include <stdint-gcc.h>

void bldc_tick (void );

void bldc_commuation (void );
void bldc_update_driver (void );
void bldc_enable_current_comparator (void );
void bldc_disable_current_comparator (void );
void bldc_start_deadtime_counter (void );
void bldc_stop_deadtime_counter (void );
void bldc_set_hi_side_pwm (uint16_t );
void bldc_set_lo_side_pwm (uint16_t );
void init_brushless_motor (void );

//
uint32_t bldc_calc_rpm_to_interval (uint32_t );
float bldc_calc_interval_to_rpm (uint32_t );

#endif
