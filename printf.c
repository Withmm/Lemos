#include <stdarg.h>

#include "types.h"
#include "defs.h"
#include "string.h"

int
vsprintf(char *buf, const char *fmt, va_list ap)
{
	const char *p = fmt;
	size_t cnt = 0;
	while (*p) {
		if (*p != '%') {
			buf[cnt++] = *p++;
			continue;
		}

		// *p = '%'
		p++;
		if (*p == '%') { // "%%"
			buf[cnt++] = *p++;
			continue;
		}
		//  "%?"
		switch (*p) {
		case 's': // "%s"
			char *src = va_arg(ap, char *);
			size_t l = strlen(src);
			strncpy(buf, src, l);
			cnt += l;
			break;
		case 'd': // "%d"
			int num = va_arg(ap, int);
			char num_buf[32] = { 0 };
			l = atoi(num_buf, num);
			strncpy(buf, num_buf, l);
			cnt += l;
			break;
		default:  // not implement yet
			uart_puts("parse ");
			uart_puts(fmt);
			uart_puts(": failed\n");
		}
		p++;
	}
	return cnt;
}
int
printf(const char *fmt, ...)
{
	char buf[1024] = { 0 };
	va_list ap;
	va_start(ap, fmt);
	size_t i = vsprintf(buf, fmt, ap);
	va_end(ap);
	uart_puts(buf);
	return i;
}

