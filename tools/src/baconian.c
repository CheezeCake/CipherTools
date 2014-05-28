#include <ctype.h>
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

char* baconian_encrypt(const char *input)
{
	int c;
	int i;
	int index = 0;
	const int mask = 0x10;
	char *output = NULL;

	output = calloc(countalpha(input) * BITS + countnonalpha(input) + 1, sizeof(char));
	if (!output)
		return NULL;

	while ((c = *input)) {
		if (isalpha(c)) {
			c = toupper(c) - 'A';

			for (i = 0; i < BITS; i++) {
				output[index++] = ((c & mask) == 0) ? 'A' : 'B';
				c <<= 1;
			}
		}
		else {
			output[index++] = c;
		}

		++input;
	}

	output[index] = '\0';

	return output;
}

char* baconian_decrypt(const char *input)
{
	int c;
	int i;
	int index = 0;
	int value[BITS];
	char *output = NULL;

	output = calloc(countalpha(input) / BITS + countnonalpha(input) + 1, sizeof(char));
	if (!output)
		return NULL;

	while ((c = *input)) {
		if (isalpha(c)) {
			c = toupper(c);

			if (!OKCHAR(c))
				unexpected_char(*input);

			value[BITS - 1] = (c == 'A') ? 0 : 1;
			++input;
			for (i = BITS - 2; i >= 0 && *input; i--, input++) {
				c = *input;

				if (isalpha(c)) {
					c = toupper(c);

					if (!OKCHAR(c))
						unexpected_char(*input);

					value[i] = (c == 'A') ? 0 : 1;
				}
				else {
					unexpected_char(*input);
				}
			}

			if (i != -1) {
				fprintf(stderr, "unexpected end of input\n");
				exit(1);
			}

			c = 'A' + decrypt_value(value);
		}
		else {
			++input;
		}

		output[index++] = c;
	}

	output[index] = '\0';

	return output;
}

void usage(void)
{
	fprintf(stderr, "usage: baconian [-d]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int encrypt = 1;
	char *buffer = NULL;
	char *output = NULL;

	if (argc == 2) {
		if (strcmp("-d", argv[1]) == 0)
			encrypt = 0;
		else
			usage();
	}
	else if (argc != 1) {
		usage();
	}

	if ((buffer = readinput()) == NULL) {
		fprintf(stderr, "Error reading input\n");
		return 2;
	}


	if (encrypt)
		output = baconian_encrypt(buffer);
	else
		output = baconian_decrypt(buffer);

	if (output)
		printf("%s\n", output);
	else
		fprintf(stderr, "Memory allocation error\n");

	free(buffer);
	free(output);

	return 0;
}
