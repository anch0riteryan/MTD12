
#ifndef _USART_
#define _USART_

#include <sam.h>

void modbus_transmit_bytes (uint8_t *data, uint8_t size); // 移植MODBUS
void usart_recv_byte (sercom_registers_t *);
void usart_send_bytes (sercom_registers_t *, uint8_t *, uint8_t);
uint16_t usart_calc_register_from_baud (uint32_t );
void init_usart (sercom_registers_t *);
void usart_enable (sercom_registers_t *);
void usart_disable (sercom_registers_t *);

#endif
