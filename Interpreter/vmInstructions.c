#include "vm.h"
#include "io.h"
#include "value.h"
#include <stdlib.h>


void instructionStackFrame(VM * vm)
{
	unsigned char nameLength = vmNextByte(vm);
	char* frameName = vmNextString(vm, nameLength);

	unsigned short varArraySize = vmNextUShort(vm);

	StackFrame* frame = malloc(sizeof(StackFrame));
	stackFrameInit(frame, frameName, varArraySize);
	callStackPush(vm->callStack, *frame);

	DEBUG_LOG("==StackFrame %s(%d local vars)==\n", frameName, varArraySize);

}


//Stack operations
void instructionStore(VM * vm)
{
	unsigned short varId = vmNextUShort(vm);

	StackFrame* stackFrame = callStackTop(vm->callStack);
	if (stackFrame == NULL) {
		ERROR_LOG("Top stack frame is null\n");
		return;
	}

	if (varId >= stackFrame->varArraySize) {
		ERROR_LOG("Attempted to access local variable that does not exist\n");
		return;
	}

	VALUE* v = &stackFrame->varArray[varId];

	if (valueStackIsEmpty(vm->valueStack) == true) {
		ERROR_LOG("Value stack is empty\n");
		return;
	}

	// Create a new copy of the value since we are going to pop it from the stack and it will get replaced after the next push.
	memcpy(v, valueStackTop(vm->valueStack), sizeof(VALUE)); 

	valueStackPop(vm->valueStack);

	DEBUG_LOG("var %d = %d\n", varId, v->i);
}

void instructionLoad(VM * vm)
{
	unsigned short varId = vmNextUShort(vm);


	StackFrame* stackFrame = callStackTop(vm->callStack);
	if (stackFrame == NULL) {
		ERROR_LOG("Top stack frame is null\n");
		return;
	}


	VALUE* v = &stackFrame->varArray[varId];

	valueStackPush(vm->valueStack, *v);

}

void instructionPush_Int(VM * vm)
{
	VALUE v;
	int i;

	i = vmNextInt32(vm);
	v.i = i;
		
	valueStackPush(vm->valueStack, v);
}

void instructionPush_UInt(VM * vm)
{
	VALUE v;
	unsigned int ui;

	ui = vmNextInt32(vm);
	v.ui = ui;

	valueStackPush(vm->valueStack, v);
}


// Arithmetic operations
void instructionAdd_Int(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->i = v2->i + v1->i;
}

void instructionAdd_UInt(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->ui = v2->ui + v1->ui;
}


void instructionSub_Int(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->i = v2->i - v1->i; //Subtract the top value from the second-top (v2-v1)
}

void instructionSub_UInt(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->ui = v2->ui - v1->ui;
}


void instructionMul_Int(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->i = v2->i * v1->i; 
}

void instructionMul_UInt(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->ui = v2->ui * v1->ui;
}


void instructionDiv_Int(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->i = v2->i / v1->i;
}

void instructionDiv_UInt(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->ui = v2->ui / v1->ui;
}


void instructionMod_Int(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->i = v2->i % v1->i;
}

void instructionMod_UInt(VM * vm)
{
	if (valueStackLength(vm->valueStack) < 2) {
		ERROR_LOG("Value stack doesn't have 2 elements\n");
		return;
	}

	VALUE* v1 = valueStackTop(vm->valueStack);
	valueStackPop(vm->valueStack);

	VALUE* v2 = valueStackTop(vm->valueStack);

	v2->ui = v2->ui % v1->ui;
}
