/*
 * ad5668.c
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ad5668.h"

int AD5668_Command(void *pData,unsigned long cnt,short op)
{
	unsigned long *pbuf = NULL;
	unsigned long nCount;
    int i = 0;
    nCount = (cnt>127) ? 127 : cnt;
    if(op == 0) //op=0 read op
    {
    	pbuf = (unsigned long *)pData;
        for(i = 0; i<nCount; i++)
        {
            pbuf[i] = AD5668_DEV->DATA;
        }
    }
    else  //op=0 write op
    {
    	pbuf = (unsigned long *)pData;
        for(i = 0; i < nCount;i++)
        {
        	AD5668_DEV->DATA = pbuf[i];
        }
    }
    return i;
};

void AD5668_OP(unsigned long channel,unsigned long value) {
	//int i;
	unsigned long cmd;
	unsigned long setvalue = 0;
	unsigned long long mid=0;
	//printf("DA value : %d\n",value);
	mid = (value << 4);
	//printf("mid : %x\n",mid);
	cmd =3;
	//AD5668_DEV->SETUSEDW = 1;
	setvalue =  (cmd <<24 | channel<<20 | mid << 4)&0x0ffffff0;
	//IOWR_32DIRECT(AD5668_BASE , 0, setvalue);
	//for (i = 0; i<6;i++) {
    AD5668_DEV->DATA = setvalue;
	//}
	return;
}
void calibration_DA(unsigned long *value) {
	if(value == NULL) return;
	*value = *value - 7;
	return;
}
void protocol_analyze_DA(void *buf) {
	unsigned long channel;
	unsigned long value;
	unsigned char head = 0x5A;
	unsigned long i=0;
	unsigned char* buffer;
	unsigned long long mid=0;
	unsigned long cmd;
	unsigned long setvalue = 0;
	buffer = (unsigned char*)buf;
	while(1) {
		if(i > 512) return;
	    if(buffer[i] == head) break;
	    i++;
	}
	while(1){
		if(buffer[i] == head) {
			i++;
		} else {
		    memcpy(&channel,buffer+i,4);
		    memcpy(&value,buffer+i+4,4);
		    break;
		}
	}
	//printf("%x,%x\n",channel,value);
	//calibration_DA(&value);
	//printf("%x,%x\n",channel,value);
	mid = (value << 4);
	cmd =3;
	setvalue =  (cmd <<24 | channel<<20 | mid << 4)&0x0ffffff0;
	AD5668_DEV->DATA = setvalue;
    return;
}
