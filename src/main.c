#include <mtd12_x.h>
#include <nvm.h>
#include <modbus.h>

Routine task;
System mtd;
Modbus modbus; // Modbus instance

int main (void ) {
	init_pinout ();
	init_nvm ();
	init_clock ();
	init_tsens ();
	init_dmac ();
	init_eic ();
	init_evsys ();
	init_adc ();

	init_tc ();
	init_tcc ();
	init_comp (); // AC Comparator

	init_usart (SERCOM3_REGS);
	init_modbus (&modbus);
	modbus.address = 160; // 0xA0
	modbus.transmit_bytes = modbus_transmit_bytes;

	if (parameter_is_signeture_exist ()) {
		parameter_load ();
	} else {
		init_parameters ();
	}

	NVIC_EnableIRQ (EIC_IRQn);
	NVIC_EnableIRQ (DMAC_IRQn);
	NVIC_EnableIRQ (AC_IRQn);
	NVIC_EnableIRQ (SERCOM3_IRQn);
	NVIC_SetPriority (SysTick_IRQn, 0);
	SysTick_Config (48000);

	__enable_irq ();

	usart_enable (SERCOM3_REGS);
	adc_enable ();

	while (1) {
		//mtd.loop ();

		if (task._10hz) {
			mtd.monitor.vin = adc_get_vin ();
			mtd.monitor.temp_sink = adc_get_temp_sink ();

			//

			task._10hz = 0;
		}

		if (AC_REGS->AC_STATUSB & AC_STATUSB_READY0 (1)) {
		}

		if (AC_REGS->AC_STATUSB & AC_STATUSB_READY1 (1)) {
		}

		if (AC_REGS->AC_STATUSB & AC_STATUSB_READY2 (1)) {
		}

		modbus.routine ();
	}

	return 0;
}
