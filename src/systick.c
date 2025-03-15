#include <mtd12_x.h>
#include <sam.h>

void systick (void ) {
	static uint16_t div1hz = 0;
	static uint16_t div10hz = 0;
	static uint16_t div100hz = 0;

	if (div1hz < 1000) {
		div1hz ++;
	} else {
		div1hz = 0;
		task._1hz = 1;
	}

	if (div10hz < 100) {
		div10hz ++;
	} else {
		div10hz = 0;
		task._10hz = 1;
	}

	if (div100hz < 10) {
		div100hz ++;
	} else {
		div100hz = 0;
		task._100hz = 1;
	}
}
