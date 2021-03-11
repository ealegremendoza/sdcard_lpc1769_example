/*
 * sdcard.c
 *
 *  Created on: 11 mar. 2021
 *      Author: eze
 */

#include "sdcard_lpc1769.h"

uint32_t get_fattime(void)//*
{
	uint32_t dia = 8;
	uint32_t mes = 7;
	uint32_t anio = 2020;
	return ((anio - 1980) << 25) | (mes << 21) | (dia << 16);
}

