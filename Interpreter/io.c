#include "io.h"
#include "vm.h"
#include <stdio.h>
#include <errno.h>

FILE* openFile(char* fileName) {
	FILE* fs = malloc(sizeof(fs));
	fs = fopen(fileName, "rb");

	if (fs == NULL) {
		ERROR_LOG("ERROR: %s", strerror(errno));
		exit(1);
	}

	return fs;
}

void closeFile(FILE * file)
{
	fclose(file);
}

/*int bytesToInt(char * buf)
{
	if (VM_IS_LITTLE_ENDIAN) {
		return (buf[0]) | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
	}
	return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]);
}*/

unsigned char* readAllBytes(FILE* file, int* fileLength) {
	fseek(file, 0, SEEK_END);
	*fileLength = ftell(file);
	rewind(file);

	unsigned char* byteArray = malloc(sizeof(byteArray) * (*fileLength));

	fread(byteArray,  1, *fileLength, file);

	return byteArray;
}