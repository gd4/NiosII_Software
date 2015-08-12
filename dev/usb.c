#include <unistd.h>
#include "usb.h"

void USB_Init() {
	//消除上电残余数据
    unsigned long data[512];
    unsigned long cnt= 0;
	usleep(1000000);
	cnt = USB_DEV->READ_COUNT;
	if(cnt > 500) {
	    U2F_ReadFIFO((void*)data);
	}
}
int USB_Command(void *pData,unsigned long cnt,short op)
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
            pbuf[i] = USB_DEV->DATA;
        }
    }
    else  //op=0 write op
    {
    	pbuf = (unsigned long *)pData;
        for(i = 0; i < nCount;i++)
        { 
        	USB_DEV->DATA = pbuf[i];
        }
    } 
    return i;
};

unsigned int U2F_ReadFIFO(void* buf)
{
    unsigned long Count;
    unsigned long nCount;
    unsigned long data;
    Count=USB_DEV->READ_COUNT;
    nCount = (Count>511) ? 512 : Count;
    int n;
    if(buf == NULL){
    	return 0;
    }
    for(n=0;n<nCount;n++)
    {
        data=USB_DEV->DATA;
        memcpy(buf+4*n,&data,4);
    }
    return nCount;
};

unsigned int F2U_FullFIFO(unsigned long data)
{
    unsigned int Count=128-USB_DEV->WITRE_COUNT;
    unsigned long buf= data;
    int n;
    for(n=0;n<Count;n++)
    {
    	USB_DEV->DATA=buf;
    }
    return Count;
};


