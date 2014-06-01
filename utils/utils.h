#ifndef READINPUT_H
#define READINPUT_H

#include <stddef.h>

#define BUFFER_SIZE 512

size_t countalpha(const char*);
size_t countnonalpha(const char*);

#define pgdc(a, b) gcd(a, b)
int gcd(int, int);
int coprime(int, int);

#endif
