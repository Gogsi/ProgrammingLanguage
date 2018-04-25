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
	//int x = bytesToInt(&arr[8]);
	//printf("%d\n", x);

	for (int i = 0; i < fileLength; i++) {
		printf("%02X ", arr[i]);
	}
	getchar();

	free(arr);
	vm_free(vm);
	//free(vm.fileSize);
	//free(vm.fileIndex);
}

/*
Variable v;

//v.value = createValue();

setValue_Char(&v.value, 'a'); // Sets the value to character 'a'

printf("%c\n", v.value.valueContainer.c);

VALUE_CONTAINER value;
value.i = 3;
VALUE_TYPE type = INT32;
setValue(&v.value, value, type); // Sets the value to int 3

printf("%d\n", v.value.valueContainer.i);



Stack st;

stackInit(&st, 65535);

VALUE val1;
setValue_Int(&val1, 4);
stackPush(&st, val1);

VALUE val2;
setValue_Int(&val2, 10);
stackPush(&st, val2);


printf("%d\n", stackTop(&st).valueContainer.i);
stackPop(&st);
printf("%d\n", stackTop(&st).valueContainer.i);
*/