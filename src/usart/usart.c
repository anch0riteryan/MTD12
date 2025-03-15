#include <usart.h>
#include <modbus.h>

//sercom_registers_t *instance = SERCOM0_REGS;
static const uint32_t BAUD = 115200;

void modbus_transmit_bytes (uint8_t *data, uint8_t size) {
	usart_send_bytes (SERCOM3_REGS, data, size);
}

void usart_recv_byte (sercom_registers_t *sercom) {
	uint8_t s = 0;
	if (sercom->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR (1)) {
		sercom->USART_INT.SERCOM_INTFLAG = SERCOM_USART_INT_INTFLAG_ERROR (1);
		return;
	}

	if (sercom->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC (1)) {

		s = (uint8_t ) sercom->USART_INT.SERCOM_DATA;
		modbus.receivce_byte (s);

		sercom->USART_INT.SERCOM_INTFLAG = SERCOM_USART_INT_INTFLAG_RXC (1);
	}
}

// modbus send
void usart_send_bytes (sercom_registers_t *sercom, uint8_t *data, uint8_t size) {
	for (uint8_t index = 0; index < size; index++) {
		while ((sercom->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE (1)) == 0);
		sercom->USART_INT.SERCOM_DATA = SERCOM_USART_INT_DATA_DATA ((uint16_t ) *(data + index));
	}
}

uint16_t usart_calc_register_from_baud (uint32_t baud) {
	uint16_t value = 0;
	
	value = (uint16_t ) (0x10000 * (1 - 0x10 * ((float ) baud / 8000000.0)));

	return value;
}

void init_usart (sercom_registers_t *instance) {
	uint32_t mclk_mask_value = 0;
	uint32_t gclk_id = 0;

	switch ((uint32_t) instance) {
	case (uint32_t) SERCOM0_REGS:
	break;
	case (uint32_t) SERCOM1_REGS:
	break;
	case (uint32_t) SERCOM2_REGS:
	break;
	case (uint32_t) SERCOM3_REGS:
		mclk_mask_value = MCLK_APBCMASK_SERCOM3 (1);
		gclk_id = SERCOM3_GCLK_ID_CORE;
	break;
	case (uint32_t) SERCOM4_REGS:
	break;
	case (uint32_t) SERCOM5_REGS:
	break;
	}

	MCLK_REGS->MCLK_APBCMASK |= mclk_mask_value; //MCLK_APBCMASK_SERCOM0 (1);

	GCLK_REGS->GCLK_PCHCTRL[gclk_id] = 
		GCLK_PCHCTRL_WRTLOCK (1) |
		GCLK_PCHCTRL_GEN (8) |
		GCLK_PCHCTRL_CHEN (1);

	instance->USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_SWRST (1);
	while (instance->USART_INT.SERCOM_CTRLA & SERCOM_USART_INT_CTRLA_SWRST (1));

	instance->USART_INT.SERCOM_CTRLA = 
		SERCOM_USART_INT_CTRLA_DORD_LSB |
		SERCOM_USART_INT_CTRLA_CPOL_IDLE_LOW |
		SERCOM_USART_INT_CTRLA_CMODE_ASYNC |
		SERCOM_USART_INT_CTRLA_FORM_USART_FRAME_NO_PARITY |
		SERCOM_USART_INT_CTRLA_SAMPA_ADJ0 |
		//SERCOM_USART_INT_CTRLA_RXPO (1) | // PAD1=RX
		//SERCOM_USART_INT_CTRLA_TXPO (3) | // PAD0=TX, PAD2=TE(RS485-DIR)
		SERCOM_USART_INT_CTRLA_RXPO (3) | // PAD3=RX
		SERCOM_USART_INT_CTRLA_TXPO (1) | // PAD2=TX
		SERCOM_USART_INT_CTRLA_SAMPR_16X_ARITHMETIC |
		SERCOM_USART_INT_CTRLA_IBON (0) |
		SERCOM_USART_INT_CTRLA_RUNSTDBY (0) |
		SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK;

	instance->USART_INT.SERCOM_CTRLB = 
		SERCOM_USART_INT_CTRLB_LINCMD_NONE |
		SERCOM_USART_INT_CTRLB_RXEN (1) |
		SERCOM_USART_INT_CTRLB_TXEN (1) |
		SERCOM_USART_INT_CTRLB_PMODE (0) |
		SERCOM_USART_INT_CTRLB_ENC (0) |
		SERCOM_USART_INT_CTRLB_SFDE (0) |
		SERCOM_USART_INT_CTRLB_COLDEN (0) |
		SERCOM_USART_INT_CTRLB_SBMODE_1_BIT |
		SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT;
	while (instance->USART_INT.SERCOM_SYNCBUSY & SERCOM_USART_INT_SYNCBUSY_CTRLB (1));

	instance->USART_INT.SERCOM_CTRLC = 
		SERCOM_USART_INT_CTRLC_HDRDLY_DELAY0 |
		SERCOM_USART_INT_CTRLC_BRKLEN_13_BIT |
		SERCOM_USART_INT_CTRLC_GTIME (3);

	instance->USART_INT.SERCOM_INTFLAG = 0xFF;
	instance->USART_INT.SERCOM_INTENSET = 
		SERCOM_USART_INT_INTENSET_ERROR (1) |
		SERCOM_USART_INT_INTENSET_RXC (1);

	instance->USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD (
		usart_calc_register_from_baud (BAUD)
	);

}

void usart_enable (sercom_registers_t *instance) {
	instance->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE (1);
	while (instance->USART_INT.SERCOM_SYNCBUSY & SERCOM_USART_INT_SYNCBUSY_ENABLE (1));
}

void usart_disable (sercom_registers_t *instance) {
	instance->USART_INT.SERCOM_CTRLA &= ~SERCOM_USART_INT_CTRLA_ENABLE (1);
}
