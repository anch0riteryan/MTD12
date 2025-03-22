
#ifndef _MTD12_
#define _MTD12_

#include <stdint-gcc.h>

#include <parameters.h>
#include <initialize.h>
#include <usart.h>

#include <mtd_dmac.h>
#include <mtd_tsens.h>
#include <mtd_tc.h>
#include <mtd_tcc.h>
#include <mtd_adc.h>
#include <mtd_comp.h>

#include <radio_ppm.h>
#include <intel_fan.h>
#include <bldc.h>

#define MODBUS_DATA_TABLE_SIZE 40

typedef struct _routine {
	uint8_t _1hz : 1;
	uint8_t _10hz : 1;
	uint8_t _100hz : 1;
} Routine;
extern Routine task;

typedef union _position_feedback {
	struct {
		uint8_t a : 1;
		uint8_t b : 1;
		uint8_t c : 1;
	} bits;
	uint16_t reg;
} PosFeedback;

typedef struct _monitor {
	// main voltage input (0.1V/LSB)
	uint16_t v_in;
	uint16_t v_motor;

	// low side current (0.1A/LSB)
	uint16_t current_phase_a;
	uint16_t current_phase_b;
	uint16_t current_phase_c;

	//
	uint16_t phase_time_a;
	uint16_t phase_time_b;
	uint16_t phase_time_c;

	// ntc temperature (0.1 degC/LSB)
	int16_t temp_motor;
	int16_t temp_sink;
} Monitor;

typedef struct _control {
	uint16_t radiator_curr;
	uint16_t radiator_targ;
	uint16_t radiator_rpm;
} Control;

typedef struct _system {
	RadioInput radio;
	Monitor monitor;
	Control control;

	uint16_t mode;
	uint16_t is_on;
	uint16_t is_starting;
	uint16_t is_stable;
	uint16_t is_ccw;
	uint16_t error;
	uint16_t step;

	int16_t *input_value;

	uint16_t rpm_curr, rpm_targ;
	uint16_t output_curr, output_targ;

	// startup
	uint16_t startup_counter;
	uint16_t startup_time;
	uint16_t startup_interval;

	// hall-sensor
	PosFeedback hall;
	PosFeedback emf;

	uint16_t a_cnt, b_cnt, c_cnt;

	void (*loop) (void ); // main loop
} System;
extern System mtd;

void systick (void );


#endif
