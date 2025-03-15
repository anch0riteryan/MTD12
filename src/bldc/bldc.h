
#ifndef _MTD_BLDC_
#define _MTD_BLDC_

#include <sam.h>
#include <stdint-gcc.h>

typedef struct _brushless_motor {
	uint16_t is_on;
	uint16_t is_starting;
	uint16_t direction;
	uint16_t step;

	// software
	uint32_t commuatation_interval;

	// 
	uint16_t rpm;

} BrushlessMotor;

void bldc_tick (void );

void bldc_commuation (void );
void bldc_update_driver (BrushlessMotor *);
void bldc_enable_current_comparator (BrushlessMotor *);
void bldc_disable_current_comparator (BrushlessMotor *);
void bldc_start_deadtime_counter (BrushlessMotor *);
void bldc_stop_deadtime_counter (BrushlessMotor *);
void bldc_set_hi_side_pwm (uint16_t );
void bldc_set_lo_side_pwm (uint16_t );
void init_brushless_motor (BrushlessMotor *);

//
uint32_t bldc_calc_rpm_to_interval (uint32_t );
float bldc_calc_interval_to_rpm (uint32_t );

#endif
