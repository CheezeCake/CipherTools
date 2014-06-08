#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define BASE 64
#define BLOCK_SIZE 3
#define ENCODED_SIZE 4

#define BUF_SIZE (BUFFER_SIZE - (BUFFER_SIZE % BLOCK_SIZE))
#define OUT_SIZE ((BUF_SIZE / BLOCK_SIZE) * ENCODED_SIZE)

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

void encode_block(const uint8_t *block, char *output, size_t pos)
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

uint8_t get_index_value(uint8_t encoded)
{
	int i;

	if(encoded == '=')
		return 0;

	for (i = 0; i < BASE; i++) {
		if (table[i] == encoded)
			return i;
	}

	fprintf(stderr, "incorect input\n");
	exit(EXIT_FAILURE);
}

void decode_block(uint8_t *block, uint8_t *output, size_t pos)
{
	int i;

	for (i = 0; i < ENCODED_SIZE; i++)
		block[i] = get_index_value(block[i]);

	memset(output + pos, 0, BLOCK_SIZE);


	output[pos] |= (block[0] << 2) | (block[1] >> 4);

	output[pos + 1] |= ((block[1] & 0x0f) << 4) | (block[2] >> 2);

	output[pos + 2] |= ((block[2] & 0x03) << 6) | (block[3] & 0x3f);
}

void base64_encode(FILE *input)
{
	int blocks_left;
	uint8_t buffer[BUF_SIZE];
	int i;
	int j;
	char output[OUT_SIZE + 1];
	uint8_t block[BLOCK_SIZE] = {0};
	int size;

	while ((size = fread(buffer, 1, BUF_SIZE, input))) {
		i = 0;
		j = 0;

		while (i + BLOCK_SIZE <= size) {
			encode_block(buffer + i, output, j);

			i += BLOCK_SIZE;
			j += ENCODED_SIZE;
		}

		if (i < size) {
			for (blocks_left = 0; i < size; i++, blocks_left++)
				block[blocks_left] = buffer[i];

			encode_block(block, output, j);

			for (i = j + blocks_left + 1; i < j + ENCODED_SIZE; i++)
				output[i] = '=';

			j += ENCODED_SIZE;
		}

		output[j] = '\0';
		printf("%s", output);
	}

	if (ferror(input)) {
		fprintf(stderr, "error reading input");
		exit(EXIT_FAILURE);
	}
}

void base64_decode(FILE *input)
{
	uint8_t buffer[OUT_SIZE];
	int i;
	int j;
	uint8_t output[BUF_SIZE + 1];
	int size;

	while ((size = fread(buffer, 1, OUT_SIZE, input))) {
			i = 0;
			j = 0;

			while (i + ENCODED_SIZE <= size) {
				decode_block(buffer + i, output, j);

				i += ENCODED_SIZE;
				j += BLOCK_SIZE;
			}

			if(i < size) {
				fprintf(stderr, "incorrect input\n");
				exit(EXIT_FAILURE);
			}

			output[j] = '\0';
			printf("%s", output);
	}

	if (ferror(input)) {
		fprintf(stderr, "error reading input\n");
		exit(EXIT_FAILURE);
	}
}

void usage()
{
	fprintf(stderr, "usage: base64 [-d]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int encode = 1;

	if (argc == 2) {
		if (strcmp("-d", argv[1]) == 0)
			encode = 0;
		else
			usage();
	}
	else if (argc != 1) {
		usage();
	}


	if (encode)
		base64_encode(stdin);
	else
		base64_decode(stdin);

	return 0;
}
