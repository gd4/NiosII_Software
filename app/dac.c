/*
 * dac.c
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */

#include "AD5668.h"

void DAC_Test(unsigned long channel) {
	//generate sawtooth wave
	unsigned long i=0;
	while(1) {
        if(AD5668_DEV->WRITE_CNT < 128) {
		    i= i+200;
		    AD5668_OP(channel,i);
		    if(i == 4000) i = 0;
		}
    }
}
