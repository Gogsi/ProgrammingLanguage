#include "vm.h"

#include "value.h"


void instructionConst(VM* vm) {
	unsigned char type = vmNextByte(vm);

	int a;
	unsigned int b;
	switch (type) {
	case INT32:
		a = vmNextInt32(vm);
		printf("next int:%d\n", a);
		break;
	case UINT32:
		b = vmNextUInt32(vm);
		printf("next uint:%u\n", b);
		break;
	}
}

void instructionVar(VM* vm) {
	unsigned char type = vmNextByte(vm);

	int a;
	switch (type) {
	case INT32:
		a = vmNextUInt32(vm);
		printf("next int:%d", a);
		break;
		//case
	}
}