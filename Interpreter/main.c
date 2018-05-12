#include "opcodes.h"
#include "variable.h"
#include "stack.h"
#include "io.h"
#include "vm.h"
#include "dictionary.h"
#include <stdio.h>

void main(void) {
	FILE* file = openFile("D:\\file.bin");

	int fileLength = 0;
	unsigned char* arr = readAllBytes(file, &fileLength);
	closeFile(file);
	free(file);


	VM* vm = malloc(sizeof(vm));
	vmInit(vm, arr, fileLength);
	vmMain(vm);

	/*
	for (int i = 0; i < fileLength; i++) {
		printf("%02X ", arr[i]);
	}
	*/
	getchar();

	free(arr);
	vmFree(vm);
	free(vm);

}
