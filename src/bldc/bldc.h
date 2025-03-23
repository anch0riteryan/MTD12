
#ifndef _MTD_BLDC_
#define _MTD_BLDC_

#include <sam.h>
#include <stdint-gcc.h>

void bldc_tick (void );

void bldc_software_commutation_enable (void );
void bldc_software_commutation_disable (void );
void bldc_setup_software_commutation (uint32_t );

void bldc_commutation (void );
void bldc_update_driver (void );
void bldc_enable_current_comparator (void );
void bldc_disable_current_comparator (void );
void bldc_setup_deadtime_counter (uint32_t );

void init_brushless_motor (void );

// bldc_port.c
void bldc_port_update_phase_time_count (void );
void bldc_port_start_phase_time_counter (void );
void bldc_port_stop_phase_time_counter (void );
void bldc_port_set_hi_side_pwm (uint16_t );
void bldc_port_set_lo_side_pwm (uint16_t );
void bldc_port_comparator (void );

// calc.c
uint32_t bldc_calc_rpm_to_interval (uint32_t );
float bldc_calc_interval_to_rpm (uint32_t );

#endif
