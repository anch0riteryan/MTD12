
#ifndef _MTD_ADC_
#define _MTD_ADC_

#include <sam.h>
#include <nvm.h>
#include <calc.h>
#include <ntc.h>

#define VANA 5029 // V_ANALOG FULL-SCALE

void dac_set_vout (uint16_t );

uint16_t adc_get_vin (void );
int16_t adc_get_temp_motor (void );
int16_t adc_get_temp_sink (void );

void init_adc (void );
void adc_enable (void );
void adc_disable (void );
uint32_t adc_get_value (adc_registers_t *, uint16_t );

#endif
