#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void atbash(FILE *input)
{
	uint8_t buffer[BUFFER_SIZE];
	char c;
	int i = 0;
	char output[BUFFER_SIZE + 1];
	int size;

	while ((size = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
		for (i = 0; i < size; i++) {
			c = buffer[i];

			if (isupper(c))
				c = 'Z' - (c - 'A');
			else if (islower(c))
				c = 'z' - (c - 'a');

			output[i] = c;
		}

		output[size] = '\0';
		printf("%s", output);
	}

	if (ferror(input)) {
		fprintf(stderr, "error reading input");
		exit(EXIT_FAILURE);
	}
}

void usage(void)
{
	fprintf(stderr, "usage: atbash [-d]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	(void) argv;
	if (argc != 1 && argc != 2)
		usage();


	atbash(stdin);

	return 0;
}
