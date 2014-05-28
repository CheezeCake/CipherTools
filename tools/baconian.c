#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define OKCHAR(c) (c == 'A' || c == 'B')

int decrypt_value(const int value[5])
{
	int i;
	int ret = 0;

	for (i = 0; i < 5; i++)
		ret |= value[i] << i;

	return ret;
}

void unexpected_char(int c)
{
	fprintf(stderr, "unexpected character '%c'\n", c);
	exit(1);
}

void baconian_encrypt(const char *input)
{
	int c;
	int i;
	const int mask = 0x10;

	while ((c = *input)) {
		if (isalpha(c)) {
			c = toupper(c) - 'A';

			for (i = 0; i < 5; i++) {
				printf("%c", ((c & mask) == 0) ? 'A' : 'B');
				c <<= 1;
			}
		}
		else {
			printf("%c", c);
		}

		++input;
	}

	printf("\n");
}

void baconian_decrypt(const char *input)
{
	int c;
	int i;
	int value[5];

	while ((c = *input)) {
		if (isalpha(c)) {
			c = toupper(c);

			if (!OKCHAR(c))
				unexpected_char(*input);

			value[4] = (c == 'A') ? 0 : 1;
			++input;
			for (i = 3; i >= 0 && *input; i--, input++) {
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

		printf("%c", c);
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
	char *buffer = NULL;

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
		baconian_encrypt(buffer);
	else
		baconian_decrypt(buffer);

	return 0;
}
