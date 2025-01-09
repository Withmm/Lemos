#include "types.h"
#include "defs.h"

char stack0[4096];

int 
kernel_main(void)
{
	uart_init();
	uart_puts("Hello, Lemos!\n");
	while (1)
		;
}
