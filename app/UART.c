//UART operate
#include <stdlib.h>
#include <stdio.h>

FILE * uart_create() {
	FILE* fp;
    fp = fopen ("/dev/uart", "r+");
    if (fp)
    {
        fprintf(fp, "uart open success.\n");
        return fp;
    }
    return NULL;
}
