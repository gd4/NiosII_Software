#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <unistd.h>
#include <altera_avalon_pio_regs.h>
#include "usb.h"
#include "pio.h"
#include <io.h>
#include "system.h"
#include "ad5668.h"
#include "ad7951.h"
#include "altera_avalon_spi.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_pio_regs.h"
#include "includes.h"
#ifndef __ucosii__
  #error This program requires the UCOSII Software Component.
#endif

#define TASK_STK_SIZE 2048

char* msg = "This is GD4 console";

#include "usb_bulk.h"
#include "dac.h"
#include "adc.h"

enum {
	USB_Recv_task_PRIORITY = 2,
	AD_Samp_task_PRIORITY = 3
};

OS_STK AD_Samp_task_stk[TASK_STK_SIZE];
OS_STK USB_Recv_task_stk[TASK_STK_SIZE];

int samp_start = 0;
FILE* fp;

// CFpgaApiApp construction
int  main() {
    //int n,i;
    //unsigned char buf[2048];
    //unsigned long pdata[512];

    OS_EVENT *flags;
    flags = OSSemCreate(0);

    USB_Init();
    AD7951_Init();
//	usb_bulk_loop();
//	usb_bulk_EP2();
//	usb_bulk_pktend();
//	DAC_Test(1);
    AD5668_OP(0,2000);
//  ADC_Signal_Test(2);
    samp_start = 0;
    OSInit( );
    OSTaskCreate(AD_Samp_task,(void*)flags,(void *)&AD_Samp_task_stk[TASK_STK_SIZE-1],AD_Samp_task_PRIORITY);
    OSTaskCreate(USB_Recv_task,(void*)flags,(void *)&USB_Recv_task_stk[TASK_STK_SIZE-1],USB_Recv_task_PRIORITY);
    OSStart();
	return 0;
}
