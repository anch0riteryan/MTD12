#include <mtd_adc.h>

const uint32_t VIN_R1 = 900000; // VFC上端分壓電阻值
const uint32_t VIN_R2 = 100000; // VFC下端分壓電阻值
const float VIN_RATIO = 1.0 / ((float) VIN_R2 / (VIN_R1 + VIN_R2));

const float DAC_SCALE = (float ) (VANA / 1024.0); // 4.904296875 mV/LSB
void dac_set_vout (uint16_t vout) { // 1 = 1mV
	uint16_t v =  (uint16_t ) (vout / DAC_SCALE);
	
	DAC_REGS->DAC_DATA = DAC_DATA_DATA (v);
	while (DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_DATA (1));
}

static void init_dac () {
	MCLK_REGS->MCLK_APBCMASK |= MCLK_APBCMASK_DAC (1);

	GCLK_REGS->GCLK_PCHCTRL[DAC_GCLK_ID] = 
		GCLK_PCHCTRL_WRTLOCK (0) |
		GCLK_PCHCTRL_GEN (8) |
		GCLK_PCHCTRL_CHEN (1);

	DAC_REGS->DAC_CTRLA = DAC_CTRLA_SWRST (1);
	while (DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_SWRST (1));

	DAC_REGS->DAC_CTRLB = 
		DAC_CTRLB_REFSEL_AVCC |
		DAC_CTRLB_DITHER (0) |
		DAC_CTRLB_VPD (0) | 
		DAC_CTRLB_LEFTADJ (0) |
		DAC_CTRLB_IOEN (1) |
		DAC_CTRLB_EOEN (0);
	
	DAC_REGS->DAC_DATA = DAC_DATA_DATA (0);
	while (DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_DATA (1));

	DAC_REGS->DAC_CTRLA = DAC_CTRLA_ENABLE (1);
	while (DAC_REGS->DAC_SYNCBUSY & DAC_SYNCBUSY_ENABLE (1));
}

// 0.1V / LSB
uint16_t adc_get_vin () {
	uint32_t scale = adc_get_value (ADC0_REGS, 11);
	uint32_t v = calc_get_mV_from_adc12 (scale);
	uint16_t vin = 0;
	
	vin = (uint16_t ) (v * VIN_RATIO) / 100;

	return vin;
}

int16_t adc_get_temp_motor () {
	return 0;
}

int16_t adc_get_temp_sink () {
	uint32_t scale = adc_get_value (ADC0_REGS, 0);
	uint32_t vntc = calc_get_mV_from_adc12 (scale);

	int16_t temperature = 0;

	temperature = ntc_calc_temperature_from_r_ntc (
		ntc_calc_r_ntc_from_analog (vntc)
	);

	if (temperature < -200) {
		temperature = -200;
	} else if (temperature > 800) {
		temperature = 800;
	}

	return temperature;
}

/*
int16_t adc_get_tfc () {
	uint32_t scale = adc_get_value (ADC1_REGS, 7);
	uint32_t vntc = calc_get_mV_from_adc12 (scale);
	
	int16_t tfc = 0;

	tfc = ntc_calc_temperature_from_r_ntc (
		ntc_calc_r_ntc_from_analog (vntc)
	);

	if (tfc > 1500) {
		tfc = 1500;
	} else if (tfc < -200) {
		tfc = -200;
	}

	return tfc;
}*/

uint32_t adc_get_value (adc_registers_t *adc, uint16_t ain) {
	uint32_t result = 0;

	if (ain > 11) {
		return 0;
	}

	adc->ADC_INPUTCTRL = ADC_INPUTCTRL_MUXNEG_GND | ADC_INPUTCTRL_MUXPOS (ain);
	while (adc->ADC_SYNCBUSY & ADC_SYNCBUSY_INPUTCTRL (1));

	adc->ADC_SWTRIG = ADC_SWTRIG_START (1);
	while (adc->ADC_SWTRIG & ADC_SWTRIG_START (1));

	adc->ADC_SWTRIG = ADC_SWTRIG_FLUSH (1);
	while (adc->ADC_SWTRIG & ADC_SWTRIG_FLUSH (1));

	result = adc->ADC_RESULT;

	return result;
}

void init_adc () {
	init_dac ();
	dac_set_vout (2500);

	MCLK_REGS->MCLK_APBCMASK |= MCLK_APBCMASK_ADC0 (1) | MCLK_APBCMASK_ADC1 (1);

	GCLK_REGS->GCLK_PCHCTRL[ADC0_GCLK_ID] = 
		GCLK_PCHCTRL_WRTLOCK (0) |
		GCLK_PCHCTRL_GEN (0) |
		GCLK_PCHCTRL_CHEN (1);
	
	GCLK_REGS->GCLK_PCHCTRL[ADC1_GCLK_ID] =
		GCLK_PCHCTRL_WRTLOCK (0) |
		GCLK_PCHCTRL_GEN (0) |
		GCLK_PCHCTRL_CHEN (1);

	ADC0_REGS->ADC_CTRLA = ADC_CTRLA_SWRST (1);
	while (ADC0_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_SWRST (1));

	ADC1_REGS->ADC_CTRLA = ADC_CTRLA_SWRST (1);
	while (ADC1_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_SWRST (1));

	ADC0_REGS->ADC_CTRLA = 
		ADC_CTRLA_ONDEMAND (0) |
		ADC_CTRLA_RUNSTDBY (0) |
		ADC_CTRLA_SLAVEEN (0);
	
	ADC1_REGS->ADC_CTRLA = 
		ADC_CTRLA_ONDEMAND (0) |
		ADC_CTRLA_RUNSTDBY (0) |
		ADC_CTRLA_SLAVEEN (0);
	
	ADC0_REGS->ADC_CALIB =
		ADC_CALIB_BIASCOMP (nvm.software_calibration.bit.ADC0_BIASCAL) |
		ADC_CALIB_BIASREFBUF (nvm.software_calibration.bit.ADC0_LINEARITY);
	
	ADC1_REGS->ADC_CALIB =
		ADC_CALIB_BIASCOMP (nvm.software_calibration.bit.ADC1_BIASCAL) |
		ADC_CALIB_BIASREFBUF (nvm.software_calibration.bit.ADC1_LINEARITY);

	ADC0_REGS->ADC_CTRLB = ADC_CTRLB_PRESCALER_DIV32;
	ADC0_REGS->ADC_REFCTRL = ADC_REFCTRL_REFCOMP (0) | ADC_REFCTRL_REFSEL_INTVCC2;
	ADC0_REGS->ADC_CTRLC =
		ADC_CTRLC_DUALSEL_BOTH |
		ADC_CTRLC_WINMODE_DISABLE |
		ADC_CTRLC_R2R (0) |
		ADC_CTRLC_RESSEL_12BIT |
		ADC_CTRLC_CORREN (0) |
		ADC_CTRLC_FREERUN (0) |
		ADC_CTRLC_LEFTADJ (0) |
		ADC_CTRLC_DIFFMODE (0);
	while (ADC0_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_CTRLC (1));

	ADC1_REGS->ADC_CTRLB = ADC_CTRLB_PRESCALER_DIV32;
	ADC1_REGS->ADC_REFCTRL = ADC_REFCTRL_REFCOMP (0) | ADC_REFCTRL_REFSEL_INTVCC2;
	ADC1_REGS->ADC_CTRLC =
		ADC_CTRLC_DUALSEL_BOTH |
		ADC_CTRLC_WINMODE_DISABLE |
		ADC_CTRLC_R2R (0) |
		ADC_CTRLC_RESSEL_12BIT |
		ADC_CTRLC_CORREN (0) |
		ADC_CTRLC_FREERUN (0) |
		ADC_CTRLC_LEFTADJ (0) |
		ADC_CTRLC_DIFFMODE (0);
	while (ADC1_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_CTRLC (1));
	
	ADC0_REGS->ADC_AVGCTRL = ADC_AVGCTRL_ADJRES (4) | ADC_AVGCTRL_SAMPLENUM_16;
	while (ADC0_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_AVGCTRL (1));

	ADC1_REGS->ADC_AVGCTRL = ADC_AVGCTRL_ADJRES (4) | ADC_AVGCTRL_SAMPLENUM_16;
	while (ADC1_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_AVGCTRL (1));

	ADC0_REGS->ADC_SAMPCTRL = ADC_SAMPCTRL_OFFCOMP (0) | ADC_SAMPCTRL_SAMPLEN (63);
	while (ADC0_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_SAMPCTRL (1));

	ADC1_REGS->ADC_SAMPCTRL = ADC_SAMPCTRL_OFFCOMP (0) | ADC_SAMPCTRL_SAMPLEN (63);
	while (ADC1_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_SAMPCTRL (1));
}

void adc_enable () {
	ADC0_REGS->ADC_CTRLA |= ADC_CTRLA_ENABLE (1);
	while (ADC0_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_ENABLE (1));

	ADC1_REGS->ADC_CTRLA |= ADC_CTRLA_ENABLE (1);
	while (ADC1_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_ENABLE (1));
}

void adc_disable () {
	ADC0_REGS->ADC_CTRLA &= ~ADC_CTRLA_ENABLE (1);
	ADC0_REGS->ADC_CTRLA &= ~ADC_CTRLA_ENABLE (1);
}
