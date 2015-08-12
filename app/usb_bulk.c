/*
 * usb_bulk.c
 *
 *  Created on: 2015-4-4
 *      Author: zhaopeng
 */

#include "usb_bulk.h"

/***************************************************************
 * Read and Write test
 **************************************************************/
void usb_bulk_loop() {
	unsigned long cnt= 0;
	unsigned long data[512];
	int i,k=0;
    while(1)
    {
    	printf("this is usb demo %d\n",k);
        usleep(1000000);

        if(USB_DEV->READ_COUNT > 127)
        {
        	cnt = USB_DEV->READ_COUNT;
        	printf("Before Read USB_DEV->READ_COUNT : %d\n",cnt);
            for(i=0;i<cnt;i++){
                data[i] = USB_DEV->DATA;
                //if(i%10) {
                //printf("USB_DEV->DATA : %d  ",USB_DEV->DATA);
                //}else{
                //	printf("\n",USB_DEV->DATA);
                //}
            }

        	//USB_Command(data,cnt,USB_RD_CMD);
        	printf("After Read USB_DEV->READ_COUNT : %d\n",USB_DEV->READ_COUNT);
            printf("Before Write USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
            if(USB_DEV->WITRE_COUNT<385)
            {
            	//USB_Command(data,cnt,USB_WR_CMD);
                for(i=0;i<cnt;i++){
                	USB_DEV->DATA=data[i];
                	//printf("USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
                }
                printf("After Write USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
            	//printf("Before PKTEND USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
            	//USB_DEV->PKEND = 1;
                //USB_DEV->PKEND = 0;
                usleep(2000);
                //printf("After PKTEND USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
            }
        }
        k++;
    }
}
/***************************************************************************
 * Bulk Test
 **************************************************************************/
void usb_bulk_EP2() {
    int cnt;
    int i = 0,k = 0;
    unsigned long buf[512];
    unsigned long dat;
    while(1) {
    	//printf("this is usb demo %d\n",k++);
        //usleep(1000000);
        if(USB_DEV->READ_COUNT > 0){
            cnt = U2F_ReadFIFO(buf);
            printf("USB Data:");
            for(i=0;i<cnt;i++){
               if((i%8)==7) {
                   printf("0x%x \n",buf[i]);
               }else{
               	printf("0x%x ",buf[i]);
               }
            }
            printf("\n");
        }
    }
}

/*************************************************************************
 * Pktend test
 ************************************************************************/
void usb_bulk_pktend(){
	int cnt;
	int i;
	//cnt = USB_DEV->READ_COUNT;
    while(1) {
        cnt = 12;
        for(i=0;i<cnt;i++){
            USB_DEV->DATA=0x12345678;
        }
        printf("After Write USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
        printf("Before PKTEND USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
        USB_DEV->PKEND = 1;
        USB_DEV->PKEND = 0;
        usleep(2000000);
        printf("After PKTEND USB_DEV->WITRE_COUNT : %d\n",USB_DEV->WITRE_COUNT);
    }
    return ;
}

extern int samp_start;
void USB_Recv_task(void* pdata)
{
	unsigned char head;
	int i;
	unsigned long cnt= 0;
	unsigned char buf[2048];
	while(1) {
		//OSTimeDlyHMSM(0, 0, 0, 50);
		//usleep(100);
		OSTimeDly(100);
		cnt = USB_DEV->READ_COUNT;
		if(cnt > 127){
			U2F_ReadFIFO((void*)buf);
		} else {
			continue;
		}
		i = 0;
		while(1) {
			if(i > 512) break;
			if(buf[i] == 0x5A) {
			  	i++;
			   	if(buf[i] == 0x5A) {
			   	    head = 0x5A;
			    }
			   	break;
			}
			if(buf[i] == 0x6A) {
			  	i++;
			    if(buf[i] == 0x6A) {
			        head = 0x6A;
			    }
			    break;
		    }
			if(buf[i] == 0x7A) {
			    i++;
			    if(buf[i] == 0x7A) {
			    	head = 0x7A;
			    }
			    break;
			}
			if(buf[i] == 0x7B) {
			    i++;
			    if(buf[i] == 0x7B) {
				    head = 0x7B;
				}
				break;
			}
			i++;
		}
		if(head == 0x5A) {
			samp_start = 0;
			protocol_analyze_DA((void*)buf);
		}
		if(head == 0x6A) {
			samp_start = 0;
			protocol_analyze_AD((void*)buf,5);
		}
		if(head == 0x7A) {
			samp_start = 1;
			printf("samp_start = 1\n");
		}
		if(head == 0x7B) {
			samp_start = 0;
			printf("samp_start = 0\n");
		}
	}
}
