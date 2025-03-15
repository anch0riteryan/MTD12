#include <mtd_dmac.h>

//DMAC CONFIGS
dmac_descriptor_registers_t DMA_DESCRIPTOR[DMAC_CH_NUM] __attribute__ ((aligned (16))) = {
	{ // CH-0
		.DMAC_BTCTRL = 
			DMAC_BTCTRL_VALID (1) |
			DMAC_BTCTRL_EVOSEL_DISABLE |
			DMAC_BTCTRL_BLOCKACT_NOACT |
			DMAC_BTCTRL_BEATSIZE_WORD |
			DMAC_BTCTRL_SRCINC (0) |
			DMAC_BTCTRL_DSTINC (0) |
			DMAC_BTCTRL_STEPSEL (0) |
			DMAC_BTCTRL_STEPSIZE (0),
		.DMAC_BTCNT = DMAC_BTCNT_BTCNT (0xFFFF),
		.DMAC_SRCADDR = DMAC_SRCADDR_SRCADDR ((uint32_t) &(TSENS_REGS->TSENS_VALUE)),
		.DMAC_DSTADDR = 0, // DMAC_DSTADDR_DSTADDR ((uint32_t) &tsens_buf),
		.DMAC_DESCADDR = DMAC_DESCADDR_DESCADDR (0)
	},
	{ // CH-1
		.DMAC_BTCTRL = 
			DMAC_BTCTRL_VALID (1) |
			DMAC_BTCTRL_EVOSEL_DISABLE |
			DMAC_BTCTRL_BLOCKACT_NOACT |
			DMAC_BTCTRL_BEATSIZE_WORD |
			DMAC_BTCTRL_SRCINC (0) |
			DMAC_BTCTRL_DSTINC (0) |
			DMAC_BTCTRL_STEPSEL (0) |
			DMAC_BTCTRL_STEPSIZE (0),
		.DMAC_BTCNT = DMAC_BTCNT_BTCNT (49),
		.DMAC_SRCADDR = DMAC_SRCADDR_SRCADDR ((uint32_t) &(TCC2_REGS->TCC_CC[0])),
		.DMAC_DSTADDR = 0,
		.DMAC_DESCADDR = DMAC_DESCADDR_DESCADDR (0)
	},
	
};

dmac_descriptor_registers_t DMA_DESCRIPTOR_WB [DMAC_CH_NUM] __attribute__ ((aligned (16))) = {};