#include <parameters.h>

uint16_t parameter_mtd[PARAMETER_SYSTEM_SIZE];

void init_parameters () {
	parameter_set_default ();
	parameter_save ();
}

uint16_t parameter_get (uint16_t index) {
	if (index >= PARAMETER_SYSTEM_SIZE) {
		return 0;
	}

	return *(parameter_mtd + index);
}

uint8_t parameter_is_signeture_exist () {
	return 0;
}

void parameter_set_default () {
	parameter_mtd[0] = 3;
	parameter_mtd[1] = 4;
	parameter_mtd[2] = 14;
	parameter_mtd[3] = 18000;
	parameter_mtd[4] = 64;
	parameter_mtd[5] = 145;
	parameter_mtd[6] = 200;
	parameter_mtd[7] = 5;
	parameter_mtd[8] = 600;
	parameter_mtd[9] = 30;

	parameter_mtd[10] = 800;
	parameter_mtd[11] = 600;
	parameter_mtd[12] = 300;
	parameter_mtd[13] = 600;
	parameter_mtd[14] = 300;
	parameter_mtd[15] = 0;
	parameter_mtd[16] = 0;
	parameter_mtd[17] = 0;
	parameter_mtd[18] = 0;
	parameter_mtd[19] = 0;
	
	parameter_mtd[20] = 150;
	parameter_mtd[21] = 100;
	parameter_mtd[22] = 10; // startup init rpm
	parameter_mtd[23] = 450; // startup target rpm
	parameter_mtd[24] = 900; // startup time

	parameter_mtd[25] = 250;
	parameter_mtd[26] = 200;
	parameter_mtd[27] = 30;
	parameter_mtd[28] = 0;
	parameter_mtd[29] = 1000;

	parameter_mtd[30] = 2100;
	parameter_mtd[31] = 900;
	parameter_mtd[32] = 1500;
	parameter_mtd[33] = 0;
	parameter_mtd[34] = 0;

	parameter_mtd[35] = 0;
	parameter_mtd[36] = 0;
	parameter_mtd[37] = 0;
	parameter_mtd[38] = 0;
	parameter_mtd[39] = 0;
}

void parameter_load () {
}

void parameter_save () {
}
