#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void affine(FILE *input, long int a, int b, int encrypt)
{
	char alpha;
	uint8_t buffer[BUFFER_SIZE];
	char c;
	int i;
	char output[BUFFER_SIZE + 1];
	int size;
	char x;

	if (!encrypt) {
		i = 1;

		while ((a * i) % 26 != 1)
			i += 2;

		a = i;
		b = a * (26 - b) % 26;
	}

	while ((size = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
		for (i = 0; i < size; i++) {
			c = buffer[i];

			if (isupper(c))
				alpha = 'A';
			else if (islower(c))
				alpha = 'a';
			else
				alpha = 0;

			if (alpha != 0) {
				x = c - alpha;

				c = alpha + ((a * x + b) % 26);
			}

			output[i] = c;
		}

		output[size] = '\0';
		printf("%s", output);
	}

	if (ferror(input)) {
		fprintf(stderr, "error reading input\n");
		exit(EXIT_FAILURE);
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


	affine(stdin, a, b, encrypt);

	return 0;
}
