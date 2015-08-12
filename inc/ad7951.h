/*
 * ad7951.h
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */

#ifndef AD7951_H_
#define AD7951_H_

#include "system.h"
#include "string.h"

typedef struct
{
    unsigned long int DATA;
    unsigned long int CONFIG;
    unsigned long int KEEPNUM;
    unsigned long int WRITE_CNT;
    unsigned long int READ_CNT;
}AD7951_STRUCT;

#define AD7951_DEV ((AD7951_STRUCT *)(AD7951_BASE  | (1 << 31)))

void AD7951_Init();
unsigned long AD7951_Command(unsigned long mode,unsigned long channel,unsigned long opcode);
unsigned long GetChannelCmd(int channel) ;
void AD7951_Read(void *buf,int cnt) ;
void AD7951_Write(int channel, int cnt);

#endif /* AD7951_H_ */
