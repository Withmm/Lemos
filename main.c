#include "types.h"
#include "defs.h"

int
main(void)
{
	uart_init();
	printf("Hello, supervisor!\n");
	while (1)
		;
}
