#ifndef READINPUT_H
#define READINPUT_H

#include <stddef.h>

#define MAX_LENGTH 4092

char* readinput(void);
size_t countalpha(const char*);
size_t countnonalpha(const char*);

#define pgdc(a, b) gcd(a, b)
int gcd(int, int);
int coprime(int, int);

#endif
