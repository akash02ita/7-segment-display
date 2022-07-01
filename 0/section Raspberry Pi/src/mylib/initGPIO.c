/**
 * @file initGPIO.c
 * This is boilerplate code provided for assignments 3 and 4 for CPSC 359
 * @brief this file is used for setting up gpio memory address when using linux os in raspberry pi
 */
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "initGPIO.h"

unsigned int *getGPIOPtr(void)
{
	int fdgpio = open("/dev/gpiomem", O_RDWR);
	
	if (fdgpio <0) {
		printf("unable to open");
	}
	
	unsigned int *gpioPtr = (unsigned int *)mmap(0,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fdgpio,0);
	return gpioPtr;
}
