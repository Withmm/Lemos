#include "types.h"
#include "defs.h"
#include "assert.h"
#include "riscv.h"
char stack0[4096];

int 
kernel_main(void)
{

	
	uart_init();
	printf("printf: %s %s %d %d\n", "Hello", "Lemos!", 10, -100);
	assert(1);
	while (1)
		;
}
