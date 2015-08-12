/*
 * ad5668.h
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */

#ifndef AD5668_H_
#define AD5668_H_

#include "system.h"
#include "string.h"

typedef struct
{
    unsigned long int DATA;
    unsigned long int WRITE_CNT;
    unsigned long int SETUSEDW;
}AD5668_STRUCT;

#define AD5668_DEV ((AD5668_STRUCT *)(AD5668_BASE  | (1 << 31)))

void AD5668_OP(unsigned long channel,unsigned long value);
int AD5668_Command(void *pData,unsigned long cnt,short op);
void protocol_analyze_DA(void *buf) ;
#endif /* AD5668_H_ */
