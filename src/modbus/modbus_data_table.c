#include <mtd12_x.h>
#include <modbus.h>

const uint16_t dummy_value = 0xFFFF;
uint16_t *modbus_data_table [MODBUS_DATA_TABLE_SIZE] = {
	&(mtd.mode),
	&(mtd.error),
	&(mtd.is_starting),
	&(mtd.is_ccw),
	&(mtd.rpm_curr),

	&(mtd.rpm_targ),
	(parameter_mtd + 3), // max rpm limit
	(parameter_mtd + 5), // input source
	&(mtd.radio.value),
	(uint16_t *) &dummy_value,

	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,

	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,

	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,

	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
	(uint16_t *) &dummy_value,
};
