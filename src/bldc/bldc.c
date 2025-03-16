#include <mtd12_x.h>
#include <bldc_const.h>

void bldc_software_commutation_enable () {
	TCC1_REGS->TCC_CTRLA |= TCC_CTRLA_ENABLE (1);
	while (TCC1_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE(1));
}

void bldc_software_commutation_disable () {
	TCC1_REGS->TCC_CTRLA &= ~TCC_CTRLA_ENABLE (1);
}

void bldc_setup_software_commutation (uint32_t uS) {
	TCC1_REGS->TCC_PERBUF = TCC_PERBUF_PERBUF (uS * 6);
	//while (TCC1_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_PER (1));
}

void bldc_commutation () {
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
	TCC0_REGS->TCC_PATT = BLDC_PATT_VALUE_TABLE[mtd.step];
	while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_PATT (1));
}

void bldc_enable_current_comparator () {
	AC_REGS->AC_INTFLAG = AC_INTFLAG_COMP0 (1) | AC_INTFLAG_COMP1 (1) | AC_INTFLAG_COMP2 (1);
	AC_REGS->AC_COMPCTRL[BLDC_COMPARATOR_USING_TABLE[mtd.step]] = BLDC_COMPARATOR_SETUP_TABLE[mtd.is_ccw][mtd.step];
	while (AC_REGS->AC_SYNCBUSY & AC_SYNCBUSY_COMPCTRL0 (1));
}

void bldc_disable_current_comparator () {
	AC_REGS->AC_COMPCTRL[BLDC_COMPARATOR_USING_TABLE[mtd.step]] = 0;
	while (AC_REGS->AC_SYNCBUSY & AC_SYNCBUSY_COMPCTRL0 (1));
}

void bldc_setup_deadtime_counter (uint32_t uS) {
	TC0_REGS->COUNT32.TC_CC[0] = TC_COUNT32_CC_CC (uS);

	TC0_REGS->COUNT32.TC_CTRLBSET = TC_CTRLBSET_CMD_RETRIGGER;
	while (TC0_REGS->COUNT32.TC_SYNCBUSY & TC_SYNCBUSY_CTRLB (1));


}

void bldc_set_hi_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CC[0] = TCC_CC_CC (value);
}

void bldc_set_lo_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CC[1] = TCC_CC_CC (value);
}

void init_brushless_motor () {
	mtd.is_on = 0;
	mtd.is_starting = 0;
	mtd.is_ccw = 0;

	mtd.input_value = &(mtd.radio.value);
}
