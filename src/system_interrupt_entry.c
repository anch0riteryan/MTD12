#include <mtd12_x.h>
#include <bldc_const.h>

void EIC_Handler () {
}

// Deadtime end, start output
void TC0_Handler () {
	if (TC0_REGS->COUNT32.TC_INTFLAG & TC_INTFLAG_OVF (1)) {

		bldc_set_lo_side_pwm (1000);
		bldc_set_hi_side_pwm (mtd.output_curr);

		//AC_REGS->AC_CTRLB = AC_CTRLB_START (BLDC_COMPARATOR_USING_TABLE[mtd.step]);
		//AC_REGS->AC_CTRLB = AC_CTRLB_START0 (1);
		bldc_enable_current_comparator ();

		TC0_REGS->COUNT32.TC_INTFLAG = TC_INTFLAG_OVF (1);
	}
}

void TCC1_Handler () {
	if (TCC1_REGS->TCC_INTFLAG & TCC_INTFLAG_OVF (1)) {
		bldc_set_hi_side_pwm (0);
		bldc_set_lo_side_pwm (1000);

		bldc_commutation ();
		bldc_setup_deadtime_counter (mtd.startup_interval * 0.005);

		TCC1_REGS->TCC_INTFLAG = TCC_INTFLAG_OVF (1);
	}
}

void AC_Handler () {
	if (AC_REGS->AC_INTFLAG & AC_INTFLAG_COMP0 (1)) {
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

		AC_REGS->AC_INTFLAG = AC_INTFLAG_COMP0 (1);
	}
}

void SERCOM3_Handler () {
	usart_recv_byte (SERCOM3_REGS);
}


