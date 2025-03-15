#include <intel_fan.h>

void intel_fan_set_pwm (uint16_t p) {
	TC4_REGS->COUNT8.TC_CC[0] = TC_COUNT8_CC_CC (p);
}
void intel_fan_enable (void );
void intel_fan_disable (void );
