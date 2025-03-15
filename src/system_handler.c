#include <mtd12_x.h>
#include <modbus.h>
#include <sam.h>

void SysTick_Handler () {
	systick ();
	bldc_tick ();
	modbus.tick ();
}

void NMI_Handler () {
}

void PendSV_Handler () {
}

void HardFault_Handler () {
	while (1);
}

void SVCall_Handler () {
}
