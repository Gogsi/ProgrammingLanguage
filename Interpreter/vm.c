#include "vm.h"
#include "opcodes.h"

#include <stdio.h>
#include <string.h>

const unsigned char  VM_VERSION_MAJOR = 0x00;
const unsigned char  VM_VERSION_MINOR = 0x01;
const unsigned char* VM_VERSION = "v0.1";

const unsigned char* VM_HEADER_SIZE = 10;

unsigned char VM_MAGIC_NUMBER[4] = { 0x4C, 0x41, 0x4E, 0x47 };

/*	==BYTECODE FORMAT==
*
*	--HEADER FORMAT--
*
*	(Value - bytes - example)
*	MAGIC_NUMBER		 - (bytes 0->3)	- 4C 41 4E 47
*	VM_VERSION_MAJOR	 - (byte 4)		- 0x01
*	VM_VERSION_MINOR	 - (byte 5)		- 0x01
*	VM_IS_LITTLE_ENDIAN  - (byte 6)		- 0x01
*	VM_CHUNK_COUNT		 - (byte 7)		- 0x01
*	RESERVED_BYTES       - (bytes 8->9) - 00 00 00
*
*	(INSTRUCTIONS START AT (byte 10))
*/

void vmReadHeader(VM * vm)
{
	if (vm->fileContents[4] != VM_VERSION_MAJOR || vm->fileContents[5] != VM_VERSION_MINOR) {
		printf("ERROR: This file is compiled for a different version of the intepreter ( VM version: %d.%d; File version %d.%d)\n", 
				VM_VERSION_MAJOR, VM_VERSION_MINOR, vm->fileContents[4], vm->fileContents[5]);
		exit(1);
	}

	if (vm->fileContents[0] != VM_MAGIC_NUMBER[0] || vm->fileContents[1] != VM_MAGIC_NUMBER[1] || vm->fileContents[2] != VM_MAGIC_NUMBER[2] || vm->fileContents[3] != VM_MAGIC_NUMBER[3])
	{
		printf("ERROR: Magic number mismatch. Are you sure this is a valid compiled file. ");
		exit(1);
	}

	if (vm->fileContents[6] == 0x01) {
		vm->isLittleEndian = 1; //The file format is little endian
	}
	else if (vm->fileContents[6] == 0x00) {
		vm->isLittleEndian = 0 ; //The file format is big endian
	}


	else {
		printf("ERROR: This file does not contain a definition for the endianness format", VM_VERSION);
		exit(1);
	}



	printf(" Interpreter %s loaded. \n",VM_VERSION);
}




void vmInit(VM* vm, unsigned char* fileContents, unsigned long fileSize) {
	//vm = malloc( sizeof(vm) );

	vm->fileContents = malloc(fileSize);
	for (int i = 0; i < fileSize; i++) {
		vm->fileContents[i] = fileContents[i];
	}

	vm->fileSize = fileSize;
	vm->fileIndex = 0;

	vmReadHeader(vm);
}

void vmMain(VM* vm) {
	vm->fileIndex = VM_HEADER_SIZE; // The instructions start after bytes [0;VM_HEADER_SIZE]
	while (vm->fileIndex < vm->fileSize) {  //MAIN LOOP

		unsigned char instruction = vm->fileContents[vm->fileIndex++];
		unsigned char tmp;
		switch (instruction) {
		case CONST:
			instructionConst(vm);
			break;
		case VAR:
			instructionVar(vm);
			break;
		}

	}
}

void vmFree(VM * vm)
{
	free(vm->fileContents);
	free(vm);
}

unsigned char vmNextByte(VM * vm)
{
	return vm->fileContents[vm->fileIndex++];
}

int vmNextInt32(VM * vm)
{
	signed char c1 = vm->fileContents[vm->fileIndex++];
	signed char c2 = vm->fileContents[vm->fileIndex++];
	signed char c3 = vm->fileContents[vm->fileIndex++];
	signed char c4 = vm->fileContents[vm->fileIndex++];
	if (vm->isLittleEndian == 1) {
		return c1 | c2 << 8 | c3 << 16 | c4 << 24;
	}
	else {
		return c1 << 24 | c2 << 16 | c3 << 8 | c4;
	}
}

unsigned int vmNextUInt32(VM * vm)
{
	unsigned char c1 = vm->fileContents[vm->fileIndex++];
	unsigned char c2 = vm->fileContents[vm->fileIndex++];
	unsigned char c3 = vm->fileContents[vm->fileIndex++];
	unsigned char c4 = vm->fileContents[vm->fileIndex++];
	if (vm->isLittleEndian == 1) {
		return c1 | c2 << 8 | c3 << 16 | c4 << 24;
	}
	else {
		return c1 << 24 | c2 << 16 | c3 << 8 | c4;
	}
}
