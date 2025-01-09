#include "string.h"
#include "defs.h"
size_t
strlen(const char *str)
{
	size_t cnt = 0;
	if (str == 0) {
		/* TODO : Use assert instead. */
		printf("strlen failed!\n");
		while (1)
			;
	}
	while (*str++)
		++cnt;
	return cnt;
}

char *
strcpy(char *dst, const char *src)
{
	return 0;
}

char *
strncpy(char *dst, const char *src, size_t n)
{
	char *dst_p = dst + strlen(dst);
	const char *src_p = src;
	for (int i = 0; i < n; i++) {
		*dst_p++ = *src_p++;
	}
	return dst;
}

int
strcmp(const char *s1, const char *s2)
{
	return 0;
}

int
strncmp(const char *s1, const char *s2, size_t n)
{
	return 0;
}

/* Finds the first occurrence of a character in a string. */
char *
strchr(const char *s, int c)
{
	return 0;
}

/* Finds the position of the last occurrence of a character in a string. */
char *
strrchr(const char *s, int c)
{
	return 0;
}

/* Finds the first occurrence of one string within another. */
char *
strstr(const char *s1, const char *needle)
{
	return 0;
}

char *
strcat(char *dest, const char *src)
{
	return 0;
}

char *
strncat(char *dest, const char *src, size_t n)
{
	return 0;
}

void *
memset(void *s, int c, size_t n)
{
	for (int i = 0; i < n; i++) {
		*(char *)(s + i) = c;
	}
	return 0;
}

void *
memcpy(void *dest, const void *src, size_t n)
{
	return 0;
}

/* Consider overlap */
void *
memmove(void *dest, const void *src, size_t n)
{
	return 0;
}

int
memcmp(const void *str1, const void *str2, size_t n)
{
	return 0;
}

int
isspace(int c)
{
	return 0;
}

int
isdigit(int c)
{
	return 0;
}

int
isalpha(int c)
{
	return 0;
}

int
isupper(int c)
{
	return 0;
}

int
islower(int c)
{
	return 0;
}

int
toupper(int c)
{
	return 0;
}

int
tolower(int c)
{
	return 0;
}

u8
atoi(char *dst, int num)
{
	int i = 0;
	int is_neg = 0;
	if (num < 0) {
		is_neg = 1;
		num = -num;
	}
	do {
		dst[i++] = (num % 10) + '0';
		num /= 10;
	} while (num);

	if (is_neg)
		dst[i++] = '-';
	dst[i] = 0;

	int start = 0;
	int end = i - 1; // [ ]

	while (start < end) {
		char tmp = dst[start];
		dst[start] = dst[end];
		dst[end] = tmp;
		++start;
		--end;
	}

	return i;
}
