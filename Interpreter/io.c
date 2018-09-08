#include "io.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef _WIN32 
#define _CRT_SECURE_NO_DEPRECATE 
#endif 

FILE* openFile(char* fileName) {
	FILE* fs = malloc(sizeof(*fs));
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


unsigned char* readAllBytes(FILE* file, int *fileLength) {
	fseek(file, 0, SEEK_END);
	*fileLength = ftell(file);
	rewind(file);

	unsigned char* byteArray = NULL;
	byteArray = (unsigned char*)malloc(sizeof(*byteArray) * (*fileLength + 1));
	fread(byteArray, *fileLength, 1, file);

	return byteArray;
}