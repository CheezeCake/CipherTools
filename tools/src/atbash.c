#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void atbash(char *input)
{
	char c;

	while ((c = *input)) {
		if (isupper(c))
			*input = 'Z' - (c - 'A');
		else if (islower(c))
			*input = 'z' - (c - 'a');

		++input;
	}
}

void usage(void)
{
	fprintf(stderr, "usage: atbash [-d]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	char *buffer = NULL;

	(void) argv;
	if (argc != 1)
		usage();


	if ((buffer = readinput()) == NULL) {
		fprintf(stderr, "Error readind input\n");
		return 2;
	}


	atbash(buffer);
	printf("%s\n", buffer);

	free(buffer);

	return 0;
}
