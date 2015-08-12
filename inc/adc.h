/*
 * adc.h
 *
 *  Created on: 2015-8-11
 *      Author: zhaopeng
 */

#ifndef ADC_H_
#define ADC_H_

#include "ad5668.h"
#include "ad7951.h"
#include "usb.h"
#include <stdio.h>
#include "includes.h"

void ADC_Continue_Sample();
void ADC_Continue_Sample2();
void ADC_Signal_Samp(int channel);
void protocol_analyze_AD(void *buf,int cnt);
void AD_Samp_task(void* pdata);

#endif /* ADC_H_ */
