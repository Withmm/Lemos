#ifndef __STRING_H__
#define __STRING_H__

#include "types.h"

size_t strlen(const char *str);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

/* Finds the first occurrence of a character in a string. */
char *strchr(const char *s, int c);

/* Finds the position of the last occurrence of a character in a string. */
char *strrchr(const char *s, int c);

/* Finds the first occurrence of one string within another. */
char *strstr(const char *s1, const char *needle);

char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

/* Consider overlap */
void *memmove(void *dest, const void *src, size_t n);

int memcmp(const void *str1, const void *str2, size_t n);

int isspace(int c);
int isdigit(int c);
int isalpha(int c);
int isupper(int c);
int islower(int c);
int toupper(int c);
int tolower(int c);
#endif
