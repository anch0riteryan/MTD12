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

	init_brushless_motor ();

	NVIC_EnableIRQ (EIC_IRQn);
	NVIC_EnableIRQ (DMAC_IRQn);
	NVIC_EnableIRQ (TCC1_IRQn);
	NVIC_EnableIRQ (TC0_IRQn);
	NVIC_EnableIRQ (AC_IRQn);
	NVIC_EnableIRQ (SERCOM3_IRQn);
	NVIC_SetPriority (SysTick_IRQn, 0);
	SysTick_Config (48000);

	__enable_irq ();

	usart_enable (SERCOM3_REGS);
	adc_enable ();

	mtd.control.radiator_rpm = 800;

	while (1) {
		//mtd.loop ();

		if (mtd.is_on) {
			if (mtd.is_starting) {
				mtd.output_curr = parameter_get (25); // 固定啟動功率
				//mtd.output_curr = mtd.radio.value;
			} else {
				mtd.output_curr = mtd.radio.value;
			}

		} else {
			mtd.output_curr = 0;
			//bldc_set_lo_side_pwm (0);
			//bldc_set_hi_side_pwm (0);
		}

		if (task._10hz) {
			mtd.monitor.v_in = adc_get_vin ();
			mtd.monitor.temp_sink = adc_get_temp_sink ();

			mtd.radio.value = radio_calc_fullscale (mtd.radio.ppm_length);

			intel_fan_set_pwm (mtd.control.radiator_rpm);

			task._10hz = 0;
		}

		modbus.routine ();
	}

	return 0;
}
