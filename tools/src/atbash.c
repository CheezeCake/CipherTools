#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char* atbash(const char *input)
{
	char c;
	char *output = NULL;
	int i = 0;

	output = calloc(strlen(input) + 1, sizeof(char));
	if (!output)
		return NULL;

	while ((c = *input)) {
		if (isupper(c))
			output[i++] = 'Z' - (c - 'A');
		else if (islower(c))
			output[i++] = 'z' - (c - 'a');

		++input;
	}

	output[i] = '\0';

	return output;
}

void usage(void)
{
	fprintf(stderr, "usage: atbash [-d]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	char *buffer = NULL;
	char *output = NULL;

	(void) argv;
	if (argc != 1 && argc != 2)
		usage();


	if ((buffer = readinput()) == NULL) {
		fprintf(stderr, "Error readind input\n");
		return 2;
	}


	output = atbash(buffer);

	if (output)
		printf("%s\n", output);
	else
		fprintf(stderr, "Memory allocation error\n");

	free(buffer);
	free(output);

	return 0;
}
