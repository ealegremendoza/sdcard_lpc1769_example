/*
===============================================================================
 Name        : sdcard_lpc1769_example.c
 Author      : ealegremendoza
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
/* note: FatFs - Generic FAT Filesystem Module
 * http://elm-chan.org/fsw/ff/00index_e.html
 * */
/* note:
 * 1 - SD mount
 * 2 - Open file (r/w)
 * 3 - Operate
 */
#include "headers.h"
void SysInit(void);

#define EXAMPLE_1	1	/*	READ FILE IF EXIST	*/
#define EXAMPLE_2	2	/*	WRITE FILE (APPEND)	*/
#define EXAMPLE_3	3	/*	READ FILE	*/
#define EXAMPLE_4	4	/* 	WRITE FILE (OVERWRITE)	*/
#define EXAMPLE		EXAMPLE_1

#define STR_SIZE	3
#define	CANT_STR	20
char vector_str[CANT_STR][STR_SIZE];

char buf[LEN_BUF]; //	read buffer


int main(void) {
	int i;
	FATFS fs;	//	File System object
	FIL fp;		//	Pointer to the file object structure
	FRESULT res;//	Return value

#if EXAMPLE == EXAMPLE_2
	FILINFO fno;//	FILINFO structure

	uint32_t len;	// strlen(buf);
	uint32_t bw;	// variable to return number of bytes written
#endif

	/* Initialize system */
	SysInit();
	DEBUGOUT("> main\n");

	/* Mount SD card */
	f_mount(&fs, "0:", 0);

#if EXAMPLE == EXAMPLE_1	/*	READ FILE IF EXIST	*/
	/* Open the file for reading, only if it exists.  */
	res = f_open(&fp, "0:/config.txt", FA_OPEN_EXISTING | FA_READ);
	if (res == FR_OK)
	{
		i=0;
		while (f_gets(vector_str[i], sizeof(vector_str[i]), &fp))
		{
			printf("%d - config.txt leido: %s\n",i,vector_str[i]);
			i++;
			f_gets(vector_str[i], sizeof(vector_str[i]), &fp);// Read line break
		}
		f_close(&fp);	// Close the file

		DEBUGOUT(">buffer\n");
		i=0;
		while (i < CANT_STR)
		{
			printf("%d - config.txt leido: %s\n",i,vector_str[i]);
			i++;
		}

	}else{
		DEBUGOUT("error al abrir config.txt\n");
	}
#endif
#if EXAMPLE == EXAMPLE_2	/*	WRITE FILE (APPEND)	*/
	/* Abre/crea un archivo para escritura (append) */
	res = f_open(&fp, "0:log.txt", FA_OPEN_ALWAYS | FA_WRITE);//*  ESCRIBO EN LOG.TXT
	if (res == FR_OK)
	{
		f_stat("0:log.txt", &fno);//* The f_stat function checks the existence of a file or sub-directory.
		f_lseek(&fp, fno.fsize);/* The f_lseek function moves the file read/write pointer of an open file object.
								*	It can also be used to expand the file size (cluster pre-allocation).*/
		f_sync(&fp);//* The f_sync function flushes the cached information of a writing file.

		strcpy(buf, "You say goodbye and I say hello!!\r\n");//	write buf
		len = strlen(buf);//*
		f_write(&fp, (const void*) buf, len, (UINT*) &bw);	//	write sd
		f_sync(&fp);//*
		f_close(&fp);//*
	}
	else{
		DEBUGOUT("error al abrir log.txt\n");}
#endif

#if EXAMPLE == EXAMPLE_3	/*	READ FILE	*/
	res = f_open(&fp, "hola.txt", FA_READ);//	read HOLA.TXT
	if (res == FR_OK)
	{
		while (f_gets(buf, sizeof buf, &fp)) {
			printf("hola.txt leido: %s\n",buf);
		}
		f_close(&fp);//*
	}
	else{
		DEBUGOUT("error al abrir hola.txt\n");}
#endif

#if EXAMPLE == EXAMPLE_4	/* 	WRITE FILE (OVERWRITE)	*/
	/* edit a line of a file. OVERWRITE */
	// Create a file (if it doesn't exist), if it exists, overwrite it
	res = f_open(&fp, "0:test_edit_line.txt", FA_OPEN_ALWAYS | FA_WRITE);
	if (res == FR_OK)
	{
		//f_stat("0:test_edit_line.txt", &fno);
		//f_lseek(&fp, fno.fsize);

		//f_sync(&fp);
		sprintf(buf,"%02d\r\n%02d\r\n%02d\r\n%02d\r\n%02d\r\n",1,11,99,24,4);
		//strcpy(buf, "00\r\n11\r\n22\r\n33\r\n44\r\n");
		len = strlen(buf);
		f_write(&fp, (const void*) buf, len, (UINT*) &bw);
		//f_sync(&fp);
		f_close(&fp);
		printf("test_edit_line.txt creado.\n");
	}
	else{
		DEBUGOUT("error al abrir test_edit_line.txt\n");}


	res = f_open(&fp, "0:test_edit_line.txt", FA_OPEN_EXISTING | FA_READ);// LEO ARCHIVO TEST
	if (res == FR_OK)
	{
		while (f_gets(buf, sizeof buf, &fp)) {
					printf("test_edit_line.txt leido: %s\n",buf);
				}
		f_close(&fp);
		printf("test_edit_line.txt leido.\n");
	}
	else{
		DEBUGOUT("error al abrir test_edit_line.txt\n");}


	/*res = f_open(&fp, "0:test_edit_line.txt", FA_OPEN_ALWAYS | FA_WRITE);// RE-ESCRIBO ARCHIVO TEST
	if (res == FR_OK)
	{
		//f_stat("0:test_edit_line.txt", &fno);
		//f_lseek(&fp, fno.fsize);

		//f_sync(&fp);

		strcpy(buf, "FF\r\nGG\r\nHH\r\nII\r\nJJ\r\n");
		len = strlen(buf);
		f_write(&fp, (const void*) buf, len, (UINT*) &bw);
		f_sync(&fp);
		f_close(&fp);
		printf("test_edit_line.txt creado.\n");
	}*/
#endif

    while(1) {
    	/* do something */
    }
    return 0 ;
}

void SysInit(void)
{
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();

	//	Initialize Systick with a frequency of 1000Hz (1ms)
	SysTick_Init(TICKRATE_HZ1);

}

