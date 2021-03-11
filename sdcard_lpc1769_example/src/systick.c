/*
 * systick.c
 *
 *  Created on: 9 mar. 2021
 *      Author: ealegremendoza
 */

#include "systick.h"
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */


void SysTick_Handler(void)
{
	/*
	 * Función que necesita la SD
	 */
	disk_timerproc();
}



void SysTick_Init(uint32_t freq)
{
	if(freq > 0xffffff)
		return;
	/* Enable and setup SysTick Timer at a periodic rate */
	/* Configuro el systick para que de ticks cada 1ms con TICKRATE_HZ1=1000*/
	//SysTick_Config(ticks*100);
	SysTick_Config(SystemCoreClock / freq);
}


