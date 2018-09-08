#include "opcodes.h"
#include "value.h"
#include "stack.h"
#include "io.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

void main(void) {
	DEBUG_LOG("Variable size: %d\n", sizeof(VALUE));

	FILE* file = openFile("file.bin");

	int fileLength = 0;
	unsigned char* arr = readAllBytes(file, &fileLength);
	closeFile(file);
	free(file);


	VM* vm = malloc(sizeof(vm));
	vmInit(vm, arr, fileLength);
	vmMain(vm);

	getchar(); // Wait for keyboard input and exit

	free(arr);
	vmFree(vm);
	free(vm);

}
