#include <mtd12_x.h>
#include <modbus.h>

const uint16_t dummy_value = 0xFFFF;
uint16_t *modbus_data_table [MODBUS_DATA_TABLE_SIZE] = {
	&(mtd.mode),
	&(mtd.is_on),
	&(mtd.is_starting),
	&(mtd.error),
	&(mtd.is_ccw),

	&(mtd.step),
	(parameter_mtd + 3), // rpm limit
	&(mtd.rpm_curr),
	&(mtd.rpm_targ),
	(uint16_t *) &dummy_value,

	(parameter_mtd + 16), // input source
	&(mtd.radio.value),
	(uint16_t *) &dummy_value, // comm. input value
	&(mtd.output_curr),
	&(mtd.output_targ),

	(uint16_t *) &dummy_value, // temp mcu
	&(mtd.monitor.temp_sink),
	&(mtd.monitor.temp_motor),
	&(mtd.control.radiator_curr),
	&(mtd.control.radiator_rpm),

	&(mtd.monitor.v_in),
	&(mtd.monitor.v_motor),
	&(mtd.monitor.current_phase_a),
	&(mtd.monitor.current_phase_b),
	&(mtd.monitor.current_phase_c),

	&(mtd.startup_counter),
	&(mtd.startup_time),
	&(mtd.startup_interval),
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	
	&(mtd.a_cnt),
	&(mtd.b_cnt),
	&(mtd.c_cnt),
	&(mtd.monitor.phase_time_a),
	&(mtd.monitor.phase_time_b),
	
	&(mtd.monitor.phase_time_c),
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	
};
