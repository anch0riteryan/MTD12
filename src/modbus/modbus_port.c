#include <mtd12_x.h>
#include <modbus.h>

extern uint16_t const *modbus_data_table[];

uint16_t modbus_port_get_register_value (uint16_t reg) {
	uint16_t value = 0;

	if (reg < PARAMETER_SYSTEM_SIZE) {
		value = *(parameter_mtd + reg);
	} else if (reg < (PARAMETER_SYSTEM_SIZE + MODBUS_DATA_TABLE_SIZE)) {
		value = **(modbus_data_table + (reg - PARAMETER_SYSTEM_SIZE));
	}

	return value;
}

uint16_t modbus_port_set_register_value (uint16_t reg, uint16_t value) {
	uint16_t *p;

	return value;
}

uint8_t modbus_port_is_register_writable (uint16_t reg, uint16_t value) { //檢查當下狀態與數值是否可寫入
	return 1;
}

void modbus_port_on_process_frame_done (void ) { // Callback
}

void modbus_port_func_not_support (void ) {
}
