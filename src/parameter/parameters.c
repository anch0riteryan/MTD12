#include <parameters.h>

uint16_t parameter_mtd[PARAMETER_SYSTEM_SIZE];

void init_parameters () {
	parameter_set_default ();
	parameter_save ();
}

uint8_t parameter_is_signeture_exist () {
	return 0;
}

void parameter_set_default () {
	parameter_mtd[0] = 3;
	parameter_mtd[1] = 4;
	parameter_mtd[2] = 14;
	parameter_mtd[3] = 18000;
	parameter_mtd[4] = 0;
	parameter_mtd[5] = 0;
	parameter_mtd[6] = 64;
	parameter_mtd[7] = 145;
	parameter_mtd[8] = 200;
	parameter_mtd[9] = 8;

	parameter_mtd[10] = 600;
	parameter_mtd[11] = 30;
	parameter_mtd[12] = 800;
	parameter_mtd[13] = 600;
	parameter_mtd[14] = 300;
	parameter_mtd[15] = 600;
	parameter_mtd[16] = 300;
	parameter_mtd[17] = 600;
	parameter_mtd[18] = 1800;
	parameter_mtd[19] = 500;
	
	parameter_mtd[20] = 150;
	parameter_mtd[21] = 200;
	parameter_mtd[22] = 30;
	parameter_mtd[23] = 0;
	parameter_mtd[24] = 0;
}

void parameter_load () {
}

void parameter_save () {
}
