#include <bldc.h>
#include <bldc_const.h>

void bldc_tick () { // 1KHz

}

void bldc_commutation (BrushlessMotor *p) {
	bldc_set_hi_side_pwm (0);
	bldc_set_lo_side_pwm (0);

	// unset comparator
	bldc_disable_current_comparator (p);

	// step = next step
	p->step = BLDC_NEXT_STEP_TABLE[p->direction][p->step];

	// setup comparator
	bldc_enable_current_comparator (p);

	// update output PATT
	bldc_update_driver (p);
}

void bldc_update_driver (BrushlessMotor *p) {
	TCC0_REGS->TCC_PATT = BLDC_PATT_VALUE_TABLE[p->step];
	while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_PATT (1));
}

void bldc_enable_current_comparator (BrushlessMotor *p) {
	AC_REGS->AC_COMPCTRL[BLDC_COMPARATOR_USING_TABLE[p->step]] = AC_COMPCTRL_ENABLE (0);
	while (AC_REGS->AC_SYNCBUSY);
}

void bldc_disable_current_comparator (BrushlessMotor *p) {
	AC_REGS->AC_COMPCTRL[BLDC_COMPARATOR_USING_TABLE[p->step]] =
		BLDC_COMPARATOR_SETUP_TABLE [p->direction][p->step];
	while (AC_REGS->AC_SYNCBUSY);
}

void bldc_start_deadtime_counter (BrushlessMotor *p) {
	// TCC1
}

void bldc_stop_deadtime_counter (BrushlessMotor *p) {
	// TCC1
}

void bldc_set_hi_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CC[0] = value;
}

void bldc_set_lo_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CCBUF[1] = TCC_CCBUF_CCBUF (value);
}

void init_brushless_motor (BrushlessMotor *p) {
	p->is_starting = 0;
}
