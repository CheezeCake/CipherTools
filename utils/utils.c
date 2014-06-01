#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

size_t countalpha(const char *str)
{
	size_t ret = 0;

	while (*str) {
		if (isalpha(*str))
			++ret;

		++str;
	}

	return ret;
}

size_t countnonalpha(const char *str)
{
	size_t ret = 0;

	while (*str) {
		if (!isalpha(*str))
			++ret;

		++str;
	}

	return ret;
}

int gcd(int a, int b)
{
	int r;

	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

int coprime(int a, int b)
{
	return (gcd(a, b) == 1);
}
