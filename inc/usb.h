#ifndef USB_H_
#define USB_H_

#include "system.h"
#include "string.h"
#include "alt_types.h"
#define USB_BUF_MAX_SIZE 256
#define USB_RD_CMD 0
#define USB_WR_CMD 1
typedef struct
{
	unsigned long DATA;
	unsigned long READ_COUNT;
	unsigned long WITRE_COUNT;
	unsigned long PKEND;
}USB_Device;

#define USB_DEV ((USB_Device *)(USB_BASE | (1 << 31)))

void USB_Init();
//USB_Command op:0 for read ,op:1 for write
int USB_Command(void *pData,unsigned long nCount,short op);

unsigned int U2F_ReadFIFO(void* buf);
unsigned int F2U_FullFIFO(unsigned long data);

#endif /*USB_H_*/


