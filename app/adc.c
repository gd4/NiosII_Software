/*
 * adc.c
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */

#include "adc.h"

extern int samp_start;
void ADC_Continue_Sample() {
	int i = 0;
	int ads_read_cnt;
	unsigned long mode,channel,opcode;
	unsigned long pdata[512];
	unsigned long value;
	mode = 1;
	channel = 0;
	opcode = 1;
	AD7951_Command(mode,channel,opcode);
	while (1) {
		if(AD7951_DEV->READ_CNT > 127) {
			mode = 0;
			AD7951_Command(mode,channel,opcode);
			break;
		}
	}
	ads_read_cnt = AD7951_DEV->READ_CNT;
	AD7951_Read((void *)pdata,AD7951_DEV->READ_CNT);

	for(i = 0; i<ads_read_cnt; i++){
		//channel = (pdata[i] &0xF000)>>12;
		value = ((pdata[i]&0x0FFF)*5000)>>12;
		USB_DEV->DATA= value;
	    //printf("AD channel is : % d ---AD value: %d\n",channel, value);
	}

	//USB_DEV->PKEND = 1;
	//USB_DEV->PKEND = 0;
    return;
}

void ADC_Continue_Sample2() {
	int i = 0;
	unsigned long mode = 1,channel = 0,opcode = 1;
	unsigned long value;

	if(samp_start == 1) {
		mode = 1;
		channel = 0;
		opcode = 1;
		AD7951_Command(mode,channel,opcode);
		if(AD7951_DEV->READ_CNT > 50){
		    for(i = 0; i<50; i++){
                value = (((AD7951_DEV->DATA)&0x0FFF)*5000)>>12;
	            USB_DEV->DATA = value;
	            //printf("value: %d\n",value);
	        }
		    USB_DEV->PKEND = 1;
		    USB_DEV->PKEND = 0;
		}
	}else if(samp_start == 0){
		mode = 0;
		AD7951_Command(mode,channel,opcode);
	}
}

void ADC_Signal_Samp(int channel)
{
	int i;
    unsigned long pdata[512];
    unsigned long value;
    // AD5668
    //AD5668_OP(1,2000);
    //IOWR_32DIRECT(AD7951_BASE , 0, 0x4000);
    //AD7951_Init();
    AD7951_Write(channel, 1);
    //AD7951_Read((void *)pdata,1);
    value = (((AD7951_DEV->DATA)&0x0FFF)*5000)>>12;
    USB_DEV->DATA = value;
    USB_DEV->PKEND = 1;
    USB_DEV->PKEND = 0;
    //for(i = 0; i<1; i++){
    //    printf("AD channel is : % d ---AD value: %d\n",(pdata[i] &0xF000)>>12,((pdata[i]&0x0FFF)*5000)>>12);
    //}
    return;
}

void protocol_analyze_AD(void *buf,int cnt) {
	unsigned long channel;
	unsigned long value;
	unsigned char head = 0x6A;
	unsigned long i=0,n=0;
	unsigned char* buffer;
	unsigned long* pbuf;
	float fvalue;
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
		    break;
		}
	}
	//printf("A/D:%x\n",channel);
	AD7951_Write(channel, cnt);
	AD7951_Read((void *)pbuf,cnt);

	for(i = 0; i<cnt; i++){
		if (channel ==  (pbuf[i] &0xF000)>>12) {
		    value = ((pbuf[i]&0x0FFF)*5000)>>12;
		}
	    //printf("AD channel is : % d ---AD value: %d\n\r",channel,value);
	}
    //fvalue = value + value*value*0.0056  - value*2.6487 + 705.1047;
    //value = (int) fvalue;
    printf("AD channel is : %d ---AD value: %d\n",channel,value);
	for(n=0;n<2;n++)
	{
		USB_DEV->DATA=0x6A6A6A6A;
	}

	USB_DEV->DATA= channel;
	USB_DEV->DATA= value;
	USB_DEV->PKEND = 1;
	USB_DEV->PKEND = 0;
	return;
}

void AD_Samp_task(void* pdata)
{
    //OS_EVENT * flags = (OS_EVENT *)pdata;
    //OSTimeDlyHMSM(0, 0, 3, 0);
    while (1)
    {
    	if(samp_start == 1){
    	    //ADC_Continue_Sample();
    		ADC_Continue_Sample2();
    		//ADC_Signal_Samp(0);
    	    //OSTimeDly(1);
    	} else {
    		printf("AD_Samp_task\n");
    		OSTimeDly(1000);
    	}
    }
}
