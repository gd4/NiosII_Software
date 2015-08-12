/*
 * led.c
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */
#include "pio.h"

void led_flush() {
    unsigned long cnt= 0;
    int led = 0;
    while(1) {
    	//cnt = cnt + 1;
    	usleep(500000);
    	led = 0;
    	//IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led);
    	LED->DATA = 0x0;
    	//printf("led twinkle %d\n",cnt);
    	usleep(500000);
    	led = 0xf;
    	//IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led);
    	LED->DATA = 0xF;
    }
}
