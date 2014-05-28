#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define BASE 64
#define BLOCK_SIZE 3
#define ENCODED_SIZE 4

static const char table[BASE] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

void encode_block(const char *block, char *output, size_t pos)
{
	int index;

	index = block[0] >> 2;
	output[pos] = table[index];

	index = (block[1] >> 4) | ((block[0] & 0x3) << 4);
	output[pos + 1] = table[index];

	index = (block[2] >> 6) | ((block[1] & 0x0f) << 2);
	output[pos + 2] = table[index];

	index = block[2] & 0x3f;
	output[pos + 3] = table[index];
}

char* base64_encode(const char *input)
{
	char *output = NULL;
	char block[BLOCK_SIZE] = { 0 };
	int len;
	int i = 0;
	int j = 0;
	int left_blocks;

	len = strlen(input);

	output = calloc(((len / BLOCK_SIZE) + 1) * ENCODED_SIZE + 1,
			sizeof(char));
	if (!output)
		return NULL;


	while (i + BLOCK_SIZE <= len) {
		encode_block(input + i, output, j);

		i += BLOCK_SIZE;
		j += ENCODED_SIZE;
	}


	if (i < len) {
		for (left_blocks = 0; i < len; i++, left_blocks++)
			block[left_blocks] = input[i];

		encode_block(block, output, j);

		for (i = j + left_blocks + 1; i < j + ENCODED_SIZE; i++)
			output[i] = '=';

		j += ENCODED_SIZE;
	}

	output[j] = '\0';

	return output;
}

char* base64_decode(const char *input)
{
	(void)input;
	return NULL;
}

void usage()
{}

int main(int argc, char **argv)
{
	int encode = 1;
	char *buffer = NULL;
	char *output = NULL;

	if (argc == 2) {
		if (strcmp("-d", argv[1]) == 0)
			encode = 0;
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

	if (encode)
		output = base64_encode(buffer);
	else
		output = base64_decode(buffer);

	if (output)
		printf("%s\n", output);
	else
		fprintf(stderr, "Memory allocation error\n");

	free(buffer);
	free(output);

	return 0;
}
