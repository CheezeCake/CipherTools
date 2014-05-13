#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void affine(char *input, long int a, int b, int encrypt)
{
	char alpha;
	char c, x;
	int i;

	if(!encrypt) {
		i = 1;
		while ((a * i) % 26 != 1)
			i += 2;
		a = i;
		b = a * (26 - b) % 26;
	}

	while ((c = *input)) {
		if (isupper(c))
			alpha = 'A';
		else if (islower(c))
			alpha = 'a';
		else
			alpha = 0;

		if (alpha != 0) {
			x = c - alpha;

			/*
			if (encrypt)
			*/
				*input = alpha + ((a * x + b) % 26);
			/*
			else
				*input = alpha + (((x - b) / a) % 26);
				*/
		}

		++input;
	}
}

void usage(void)
{
	fprintf(stderr, "usage: affine [-d] a b\n"
			"a: integer > 0 and coprime with 26\n"
			"b: integer between 0 and 25\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int encrypt = 1;
	int arg = 1;

	char *buffer = NULL;
	long int a = 0;
	int b = 0;

	if (argc == 4) {
		if (strcmp(argv[arg++], "-d") == 0)
			encrypt = 0;
		else
			usage();
	}
	else if (argc != 3) {
		usage();
	}

	errno = 0;
	a = strtol(argv[arg], NULL, 10);

	if (errno != 0 || a < 0 || !coprime(a, 26))
		usage();

	errno = 0;
	b = strtol(argv[++arg], NULL, 10);

	if (errno != 0 || b < 0 || b > 25)
		usage();


	if ((buffer = readinput()) == NULL) {
		fprintf(stderr, "Error reading input\n");
		return 3;
	}


	affine(buffer, a, b, encrypt);
	printf("%s\n", buffer);

	free(buffer);

	return 0;
}
