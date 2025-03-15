
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

#define MODBUS_DATA_TABLE_SIZE 25

typedef struct _routine {
	uint8_t _1hz : 1;
	uint8_t _10hz : 1;
	uint8_t _100hz : 1;
} Routine;
extern Routine task;

typedef struct _input {
	uint16_t radio_ppm; // ppm signal pulse length 1uS/LSB
	int16_t radio_input;

	uint16_t radiator_rpm;
} Input;

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
	uint16_t vin;

	// low side current (0.1A/LSB)
	uint16_t current_phase_a;
	uint16_t current_phase_b;
	uint16_t current_phase_c;

	// ntc temperature (0.1 degC/LSB)
	int16_t temp_motor;
	int16_t temp_sink;

	// hall-sensor
	PosFeedback hall;
	PosFeedback emf;

	// motor
	uint16_t mot_rpm;
	uint16_t mot_commuatation_interval;

} Monitor;

typedef struct _control {
	// output type select
	// 0: pwm driven
	// 1: rpm driven
	uint16_t output_select; 

	// pwm 0-100.0% (0.1%/LSB)
	uint16_t output_curr;
	uint16_t output_targ;

	uint16_t radiator_curr;
	uint16_t radiator_targ;

	//


} Control;

typedef struct _system {
	Input input;
	Monitor monitor;
	Control control;

	void (*loop) (void ); // main loop
} System;
extern System mtd;

void systick (void );


#endif
