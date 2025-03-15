#include <mtd12_x.h>
#include <bldc_const.h>

void bldc_tick () { // 1KHz
	static uint16_t st_debounce_counter = 0;
	static uint16_t sp_debounce_counter = 0;

	if (mtd.is_on) { // on->off
		if (*mtd.input_value < 10) {
			if (sp_debounce_counter < 200) {
				sp_debounce_counter ++;
			} else {
				sp_debounce_counter = 0;

				// on stop
				//p->is_on = 0;
			}
		} else {
			sp_debounce_counter = 0;
		}
	} else { // off->on
		if (*mtd.input_value >= 10) {
			if (st_debounce_counter < 200) {
				st_debounce_counter ++;
			} else {
				st_debounce_counter = 0;

				// on start

				//p->is_on = 1;
				//p->is_starting = 1;
			}
		} else {
			st_debounce_counter = 0;
		}
	}
}

void bldc_commutation () {
	bldc_set_hi_side_pwm (0);
	bldc_set_lo_side_pwm (0);

	// unset comparator
	bldc_disable_current_comparator ();

	// step = next step
	mtd.step = BLDC_NEXT_STEP_TABLE[mtd.is_ccw][mtd.step];

	// setup comparator
	bldc_enable_current_comparator ();

	// update output PATT
	bldc_update_driver ();
}

void bldc_update_driver () {
	//TCC0_REGS->TCC_PATT = BLDC_PATT_VALUE_TABLE[mtd.step]];
	//while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_PATT (1));
}

void bldc_enable_current_comparator () {
	//AC_REGS->AC_COMPCTRL[BLDC_COMPARATOR_USING_TABLE[mtd.step]]] = BLDC_COMPARATOR_SETUP_TABLE[p->direction][p->step];
	//while (AC_REGS->AC_SYNCBUSY);
}

void bldc_disable_current_comparator () {
	//AC_REGS->AC_COMPCTRL[BLDC_COMPARATOR_USING_TABLE[mtd.step]] =
	//	BLDC_COMPARATOR_SETUP_TABLE [p->direction][mtd.step]];
	//while (AC_REGS->AC_SYNCBUSY);
}

void bldc_start_deadtime_counter () {
	// TCC1
}

void bldc_stop_deadtime_counter () {
	// TCC1
}

void bldc_set_hi_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CC[0] = value;
}

void bldc_set_lo_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CCBUF[1] = TCC_CCBUF_CCBUF (value);
}

void init_brushless_motor () {
	mtd.is_on = 0;
	mtd.is_starting = 0;
	mtd.is_ccw = 0;

	mtd.input_value = &(mtd.radio.value);
}
