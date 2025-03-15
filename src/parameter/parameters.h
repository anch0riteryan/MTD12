
#ifndef _MTD_PARAMETERS_
#define _MTD_PARAMETERS_

#include <stdint-gcc.h>
#include <nvm.h>

#define PARAMETER_SIGNATURE_OFFSET 0x00
#define PARAMETER_SYSTEM_OFFSET 0x40
#define PARAMETER_SYSTEM_SIZE 40

#define PARAM_STARTUP_INIT_RPM (*(parameter_mtd + 17))
#define PARAM_STARTUP_TARG_RPM (*(parameter_mtd + 18))
#define PARAM_STARTUP_TIME (*(parameter_mtd + 19))
#define PARAM_STARTUP_INIT_PWM (*(parameter_mtd + 20))
#define PARAM_STARTUP_TARG_PWM (*(paramter_mtd + 21))
#define PARAM_STARTUP_FAULT_TIME (*(parameter_mtd + 22))

void init_parameters (void );
uint8_t parameter_is_signeture_exist (void );
void parameter_set_default (void );
void parameter_load (void );
void parameter_save (void );

extern uint16_t parameter_mtd[];

#endif
