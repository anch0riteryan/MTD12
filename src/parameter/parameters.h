
#ifndef _MTD_PARAMETERS_
#define _MTD_PARAMETERS_

#include <stdint-gcc.h>
#include <nvm.h>

#define PARAMETER_SIGNATURE_OFFSET 0x00
#define PARAMETER_SYSTEM_OFFSET 0x40
#define PARAMETER_SYSTEM_SIZE 25

void init_parameters (void );
uint8_t parameter_is_signeture_exist (void );
void parameter_set_default (void );
void parameter_load (void );
void parameter_save (void );

extern uint16_t parameter_mtd[];

#endif
