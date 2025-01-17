#ifndef __DEFS_H__
#define __DEFS_H__

#include "types.h"

/* uart.c */
void uart_init(void);
int uart_putc(char c);
void uart_puts(const char *s);

/* print.c */
int printf(const char *fmt, ...);

#endif
