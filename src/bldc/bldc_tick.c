#include <bldc.h>
#include <bldc_const.h>

void bldc_tick () { // 1KHz
	static uint16_t st_debounce_counter = 0;
	static uint16_t sp_debounce_counter = 0;

	if (mtd.is_on) { // on->off
		if (*mtd.input_value < 10) {
			if (sp_debounce_counter < 200) {
				sp_debounce_counter ++;
			} else {
				sp_debounce_counter = 0;

				// on stop
				//p->is_on = 0;
			}
		} else {
			sp_debounce_counter = 0;
		}
	} else { // off->on
		if (*mtd.input_value >= 10) {
			if (st_debounce_counter < 200) {
				st_debounce_counter ++;
			} else {
				st_debounce_counter = 0;

				// on start

				//p->is_on = 1;
				//p->is_starting = 1;
			}
		} else {
			st_debounce_counter = 0;
		}
	}
}

