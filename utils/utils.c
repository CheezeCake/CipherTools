#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char* readinput(void)
{
	char *buffer = NULL;

	if ((buffer = calloc(MAX_LENGTH, sizeof(char))) == NULL)
		return NULL;

	fgets(buffer, MAX_LENGTH, stdin);

	return buffer;
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
