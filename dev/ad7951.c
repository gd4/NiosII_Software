/*
 * ad7951.c
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ad7951.h"
#include "usb.h"

extern FILE* fp;

static unsigned long ADS7951_Channel_Cmd[8] = { 0x1850, 0x18d1, 0x1952, 0x19d3, 0x1a54, 0x1ad5, 0x1b56, 0x1bd7};

unsigned long AD7951_Command(unsigned long mode,unsigned long channel,unsigned long opcode)
{
	unsigned long data = 0;
    if(opcode == 0) //opcode=0 read opcode
    {
        return AD7951_DEV->DATA;
    } else {  //op=1 write
    	if(mode == 0) {
    		        AD7951_DEV->CONFIG = 0;
    	    	    AD7951_DEV->DATA = ADS7951_Channel_Cmd[channel];
    	    	    return 0;
    	}
    	if(mode == 1) {
    		data = ADS7951_Channel_Cmd[channel] << 16;
    		data |= 1;
    		AD7951_DEV->CONFIG = data;
    		return 0;
    	}
    }
    return 0;
}

void AD7951_Init() {
	unsigned long data;
	AD7951_DEV->DATA = 0x40004000;
	usleep(50000);
	data = AD7951_DEV->DATA;  //abandon first
	return;
}
void AD7951_Write(int channel, int cnt) {
	int i;
    //printf("channel: %d",channel);
	//IOWR_32DIRECT(AD7951_BASE , 0, ADS7951Address[channel]);
    for(i = 0; i<cnt; i++){
	    AD7951_DEV->DATA = ADS7951_Channel_Cmd[channel];
    }
	//printf("AD data: %x\n",ADS7951_Channel_Cmd[channel]);
	//usleep(50000);

	return ;
}

void AD7951_Read(void *buf,int cnt) {
	int i;
	unsigned long * data;
	data = (unsigned long *)buf;
	//value = IORD_32DIRECT(AD7951_BASE, 0);
	for(i = 0; i<cnt;i++) {
	    data[i] = AD7951_DEV->DATA;
	    //printf("AD channel is : % d ---AD value: %d\n",(data[i] &0xF000)>>12,((data[i]&0x0FFF)*5000)>>12);
	    //printf("s2f cnt is : %d\n", AD7951_DEV->READ_CNT);
	}
	return;
}

unsigned long GetChannelCmd(int channel) {
	return ADS7951_Channel_Cmd[channel];
}


