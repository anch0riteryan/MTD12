#include <mtd12_x.h>

void EIC_Handler () {
}

void AC_Handler () {
	if (AC_REGS->AC_INTFLAG & AC_INTFLAG_COMP0 (1)) {
			// C
		AC_REGS->AC_INTFLAG = AC_INTFLAG_COMP0 (1);
	}

	if (AC_REGS->AC_INTFLAG & AC_INTFLAG_COMP1 (1)) {
			// B
		AC_REGS->AC_INTFLAG = AC_INTFLAG_COMP1 (1);
	}

	if (AC_REGS->AC_INTFLAG & AC_INTFLAG_COMP2 (1)) {
			// A
		AC_REGS->AC_INTFLAG = AC_INTFLAG_COMP2 (1);
	}
}

void SERCOM3_Handler () {
	usart_recv_byte (SERCOM3_REGS);
}


