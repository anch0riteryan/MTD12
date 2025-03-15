
#ifndef _MTD_DMAC_
#define _MTD_DMAC_

#include <mtd12_x.h>

void init_dmac (void );

extern dmac_descriptor_registers_t DMA_DESCRIPTOR[];
extern dmac_descriptor_registers_t DMA_DESCRIPTOR_WB [];

#endif
