#include <mtd12_x.h>

extern uint32_t bldc_phase_time[6];

void bldc_port_update_phase_time_count () {
	TCC1_REGS->TCC_CTRLBSET = TCC_CTRLBCLR_CMD_READSYNC;

	bldc_phase_time[mtd.step] = TCC1_REGS->TCC_COUNT;
}

void bldc_port_start_phase_time_counter () {
}

void bldc_port_stop_phase_time_counter () {
}

void bldc_port_set_hi_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CC[0] = TCC_CC_CC (value);
}

void bldc_port_set_lo_side_pwm (uint16_t value) {
	TCC0_REGS->TCC_CC[1] = TCC_CC_CC (value);
}

void bldc_port_comparator () {
	switch (mtd.step) {
		case 0:
		case 3:
			mtd.c_cnt ++;
			break;
		case 1:
		case 4:
			mtd.b_cnt ++;
			break;
		case 2:
		case 5:
			mtd.a_cnt ++;
			break;
		default:
			break;
	}

	bldc_set_lo_side_pwm (0);
	bldc_set_hi_side_pwm (0);
	TCC1_REGS->TCC_CTRLBSET = TCC_CTRLBCLR_CMD_RETRIGGER;
	while (TCC1_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CTRLB (1));

	bldc_commutation ();
	bldc_setup_deadtime_counter (mtd.startup_interval * 0.05);
}
