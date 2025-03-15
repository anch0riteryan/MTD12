#include <mtd_tsens.h>
#include <nvm.h>

volatile uint32_t tsens_buf;
int16_t temperature = 0;

void tsens_update_temp () {
	int32_t tmp = tsens_buf;
	if (tmp & 0x800000) {
		tmp = 0xFF800000;
	}

	temperature = tmp / 10;
}

void init_tsens () {
	MCLK_REGS->MCLK_APBAMASK |= MCLK_APBAMASK_TSENS (1);

	GCLK_REGS->GCLK_PCHCTRL[TSENS_GCLK_ID] = 
		GCLK_PCHCTRL_WRTLOCK (1) |
		GCLK_PCHCTRL_GEN (8) |
		GCLK_PCHCTRL_CHEN (1);

	TSENS_REGS->TSENS_CTRLA = TSENS_CTRLA_SWRST (1);
	while (TSENS_REGS->TSENS_CTRLA & TSENS_CTRLA_SWRST (1));

	TSENS_REGS->TSENS_GAIN = TSENS_GAIN_GAIN (nvm.temp_sensor_calibration.bit.TSENS_GAIN);
	TSENS_REGS->TSENS_OFFSET = TSENS_OFFSET_OFFSETC (nvm.temp_sensor_calibration.bit.TSENS_OFFSET);
	TSENS_REGS->TSENS_CAL =
		TSENS_CAL_TCAL (nvm.temp_sensor_calibration.bit.TSENS_TCAL) |
		TSENS_CAL_FCAL (nvm.temp_sensor_calibration.bit.TSENS_FCAL);

	if (DSU_REGS->DSU_STATUSB & DSU_STATUSB_DBGPRES (1)) {
		TSENS_REGS->TSENS_DBGCTRL = TSENS_DBGCTRL_DBGRUN (1);
	}

	TSENS_REGS->TSENS_CTRLC = TSENS_CTRLC_FREERUN (1) | TSENS_CTRLC_WINMODE_DISABLE;
	TSENS_REGS->TSENS_CTRLA = TSENS_CTRLA_ENABLE (1);
	TSENS_REGS->TSENS_CTRLB = TSENS_CTRLB_START (1);

}
