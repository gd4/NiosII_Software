#ifndef PIO_H_
#define PIO_H_
#include "system.h"
#include "string.h"

typedef struct
{
    unsigned long int DATA;
    unsigned long int DIRECTION;
    unsigned long int INTERRUPT_MASK;
    unsigned long int EDGE_CAPTURE;
}PIO_STR;

#define LED ((PIO_STR *)(LED_BASE  | (1 << 31)))

#define KEY ((PIO_STR *)(KEY_BASE  | (1 << 31)))

#endif /*LED_H_*/
