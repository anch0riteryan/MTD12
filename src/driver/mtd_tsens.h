
#ifndef _MTD_TSENS_
#define _MTD_TSENS_

#include <stdint-gcc.h>
#include <sam.h>

void tsens_update_temp (void );
void init_tsens (void );

extern volatile uint32_t tsens_buf;

#endif
