/*
 * sdcard.h
 *
 *  Created on: 11 mar. 2021
 *      Author: eze
 */

#ifndef SDCARD_LPC1769_H_
#define SDCARD_LPC1769_H_
#include "headers.h"
//#include "LPC176x.h"
#include "diskio.h"//*
#include "ff.h"//*

#define f_unmount(path) f_mount(0, path, 0)	//*
#define f_rewind(fp) 		f_lseek((fp), 0)

#define LEN_BUF				(100)		//para el buffer que leera la tarjeta sd

extern void disk_timerproc(void);//*
uint32_t get_fattime(void);//*

#endif /* SDCARD_LPC1769_H_ */
