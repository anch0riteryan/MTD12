#include <mtd12_x.h>
#include <bldc_const.h>

static uint16_t ts = 0;
static float x = 0; // 每ms變化量

static void bldc_shift_to_start () {
	mtd.is_on = 1;
	mtd.is_starting = 1;
	mtd.is_stable = 0;
	mtd.startup_counter = 0;
	mtd.startup_time = parameter_get (24);
	mtd.startup_interval = bldc_calc_rpm_to_interval (parameter_get (22));

	ts = mtd.startup_interval;
	x = (float) (bldc_calc_rpm_to_interval (parameter_get (22)) - bldc_calc_rpm_to_interval (parameter_get (23))) / (float) mtd.startup_time;

	TCC1_REGS->TCC_PER = TCC_PER_PER (mtd.startup_interval);
	bldc_setup_software_commutation (mtd.startup_interval);
	bldc_software_commutation_enable ();
}

static void bldc_shift_to_stop () {
	bldc_software_commutation_disable ();
	mtd.is_on = 0;

}

void bldc_tick () { // 1KHz
	static uint16_t st_debounce_counter = 0;
	static uint16_t sp_debounce_counter = 0;

	if (mtd.is_on) { // on->off
		if (*mtd.input_value < parameter_get (20)) {
			if (sp_debounce_counter < parameter_get (21)) {
				sp_debounce_counter ++;
			} else {
				sp_debounce_counter = 0;

				bldc_shift_to_stop ();
			}
		} else {
			sp_debounce_counter = 0;

			if (mtd.is_starting) {
				if (mtd.startup_counter < mtd.startup_time) {
					mtd.startup_counter ++;
				} else {
					mtd.is_starting = 0;
				}

				mtd.startup_interval =  ts - (x * mtd.startup_counter);
				bldc_setup_software_commutation (mtd.startup_interval);
			} 

		}
	} else { // off->on
		if (*mtd.input_value >= parameter_get (20)) {
			if (st_debounce_counter < parameter_get (21)) {
				st_debounce_counter ++;
			} else {
				st_debounce_counter = 0;

				bldc_shift_to_start ();
			}
		} else {
			st_debounce_counter = 0;
		}
	}
}

