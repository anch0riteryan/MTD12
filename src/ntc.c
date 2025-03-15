#include <ntc.h>

/**
 * @brief 計算 NTC 熱敏電阻的溫度值。
 *
 * 根據輸入的 NTC 電阻值 `r_ntc`，使用簡化的 Steinhart-Hart 方程計算攝氏溫度：
 * T = [1 / (ln(Rntc / R25) / B + 1 / T25)] - 273.15
 * 為提高精度，結果乘以一個縮放因子 `SCALE`（10），返回值單位為 0.1°C。
 *
 * 計算過程：
 * 1. 計算 `ln(r_ntc / R25)`，得到電阻比值的自然對數。
 * 2. 將對數結果除以 Beta 係數 `K`，與 `1 / T25` 相加。
 * 3. 將結果取倒數得到絕對溫度（Kelvin）。
 * 4. 將 Kelvin 溫度轉換為攝氏溫度，並乘以縮放因子 `SCALE`。
 *
 * @param r_ntc 輸入的 NTC 電阻值（單位：歐姆，通常以實際測量值代入）。
 * @return int16_t 返回計算結果，單位為 0.1°C（例如 250 表示 25.0°C）。
 */

const uint32_t SCALE = 10;
const uint16_t K = 3435;
const float R25 = 10000.0; //10kOhm
const float T2_298 = (1.0 / 298.15); // 273.15 + 25c 

int16_t ntc_calc_temperature_from_r_ntc (uint32_t r_ntc) {
	int16_t temperature = 0;
	float c = 0;

	c = logf (r_ntc / R25);
	c /= K;
	c += T2_298;
	c = (1 / c);
	c -= (273.15); // K溫標

	c *= SCALE;

	temperature = (int16_t) c;

	return temperature;
}

const uint32_t V_SYS = 5022; // 系統電壓 5000mV
const uint32_t R_HIGHSIDE = 15000; // 上端分壓電阻

// 12K 電阻與下端NTC分壓電壓輸入 單位mV
uint32_t ntc_calc_r_ntc_from_analog (uint32_t vntc) {
	uint32_t rntc = 0;

	rntc = (vntc * R_HIGHSIDE) / (V_SYS - vntc);
	
	return rntc;
}
