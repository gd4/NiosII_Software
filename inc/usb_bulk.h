/*
 * usb_bulk.h
 *
 *  Created on: 2015-8-11
 *      Author: zhaopeng
 */

#ifndef USB_BULK_H_
#define USB_BULK_H_

#include "usb.h"
#include "adc.h"

void usb_bulk_loop();
void usb_bulk_EP2();
void usb_bulk_pktend();
void USB_Recv_task(void* pdata);

#endif /* USB_BULK_H_ */
