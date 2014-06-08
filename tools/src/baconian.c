#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define OKCHAR(c) (c == 'A' || c == 'B')
#define BITS 5

int decrypt_value(const int value[BITS])
{
	int i;
	int ret = 0;

	for (i = 0; i < BITS; i++)
		ret |= value[i] << i;

	return ret;
}

void unexpected_char(int c)
{
	fprintf(stderr, "unexpected character '%c'\n", c);
	exit(1);
}

void baconian_encrypt(FILE *input)
{
	uint8_t buffer[BUFFER_SIZE];
	int c;
	int i;
	int j;
	int output_index = 0;
	const int mask = 0x10;
	char output[BUFFER_SIZE];
	int size;

	while ((size = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
		for (i = 0; i < size; i++) {
			c = buffer[i];

			if (isalpha(c)) {
				c = toupper(c) - 'A';

				for (j = 0; j < BITS; j++) {
					output[output_index++] = ((c & mask) == 0) ? 'A' : 'B';
					c <<= 1;
				}
			}
			else {
				output[output_index++] = c;
			}

			if (output_index > BUFFER_SIZE - BITS - 1) {
				output[output_index] = '\0';
				printf("%s", output);
				output_index = 0;
			}
		}

		output[output_index] = '\0';
		printf("%s", output);
	}

	if (ferror(input)) {
		fprintf(stderr, "error reading input\n");
		exit(EXIT_FAILURE);
	}
}

void baconian_decrypt(FILE *input)
{
	int c;
	int _c;
	int i;
	int value[BITS];

	while ((c = fgetc(input)) != EOF) {
		_c = c;

		if (isalpha(c)) {
			c = toupper(c);

			if (!OKCHAR(c))
				unexpected_char(_c);

			value[BITS - 1] = (c == 'A') ? 0 : 1;

			for (i = BITS - 2; i >= 0; i--) {
				c = fgetc(input);

				if (c == EOF) {
					fprintf(stderr, "unexpected end of input\n");
					exit(1);
				}

				_c = c;

				if (isalpha(c)) {
					c = toupper(c);

					if (!OKCHAR(c))
						unexpected_char(_c);

					value[i] = (c == 'A') ? 0 : 1;
				}
				else {
					unexpected_char(_c);
				}
			}

			c = 'A' + decrypt_value(value);
		}

		fputc(c, stdout);
	}
}

void usage(void)
{
	fprintf(stderr, "usage: baconian [-d]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int encrypt = 1;

	if (argc == 2) {
		if (strcmp("-d", argv[1]) == 0)
			encrypt = 0;
		else
			usage();
	}
	else if (argc != 1) {
		usage();
	}


	if (encrypt)
		baconian_encrypt(stdin);
	else
		baconian_decrypt(stdin);

	return 0;
}
