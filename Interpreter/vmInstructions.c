#include "vm.h"
#include "io.h"
#include "value.h"
#include "variable.h"

void instructionConst(VM* vm) {
	unsigned char nameLength = vmNextByte(vm);
	char* variableName = vmNextString(vm, nameLength);

	Variable* v = malloc(sizeof(Variable));
	varInit(v);
	v->key = variableName;
	v->isConstant = true;

	unsigned char variableType = vmNextByte(vm);

	int i;
	unsigned int ui;
	switch (variableType) {
	case INT32:
		i = vmNextInt32(vm);
		setValue_Int(v->value, i);
		DEBUG_LOG("const int %s = %d\n", variableName, i);
		break;
	case UINT32:
		ui = vmNextUInt32(vm);
		setValue_UInt(v->value, ui);
		DEBUG_LOG("const uint %s = %u\n", variableName, ui);
		break;
	}

	HTEntry* entry = malloc(sizeof(HTEntry));
	entry->key = variableName;
	entry->next = NULL;
	entry->v = v;

	StackFrame* stackFrame = callStackTop(vm->callStack);
	if (stackFrame == NULL) {
		ERROR_LOG("Top stack frame is null");
		return;
	}

	ht_set(stackFrame->variableDictionary, variableName, entry);

}

void instructionVar(VM* vm) {
	unsigned char nameLength = vmNextByte(vm);
	char* variableName = vmNextString(vm, nameLength);

	Variable* v = malloc(sizeof(Variable));
	varInit(v);
	v->key = variableName;
	v->isConstant = false;
	
	HTEntry* entry = malloc(sizeof(HTEntry));
	entry->key = variableName;
	entry->next = NULL;
	entry->v = v;

	StackFrame* stackFrame = callStackTop(vm->callStack);
	if (stackFrame == NULL) {
		ERROR_LOG("Top stack frame is null");
		return;
	}

	ht_set(stackFrame->variableDictionary, variableName, entry);

	DEBUG_LOG("var %s\n", variableName);

	/*int a;
	switch (type) {
	case INT32:
		a = vmNextUInt32(vm);
		printf("var int:%d", a);
		break;
		//case
	}*/
}

void instructionStore(VM * vm)
{
	unsigned char nameLength = vmNextByte(vm);
	char* variableName = vmNextString(vm, nameLength);

	StackFrame* stackFrame = callStackTop(vm->callStack);
	if (stackFrame == NULL) {
		ERROR_LOG("Top stack frame is null\n");
		return;
	}


	Variable* v = ht_get(stackFrame->variableDictionary, variableName);
	if (v->isConstant == true) {
		ERROR_LOG("Atempted to change value of constant\n");
		return;
	}

	if (valueStackIsEmpty(vm->valueStack) == true) {
		ERROR_LOG("Value stack is empty\n");
		return;
	}
	VALUE* newValue = malloc(sizeof(VALUE));
	memcpy(newValue, valueStackTop(vm->valueStack), sizeof(VALUE)); // Create a new copy of the value since we are going to pop it from the stack and it will get replaced after the next push.

	varSetValue(v, newValue);
	valueStackPop(vm->valueStack);

	//TODO: sortof cheating since we get a pointer to the entry and change the data without using ht_set

	/*
	HTEntry* entry = malloc(sizeof(HTEntry));
	entry->key = variableName;
	entry->next = NULL;
	entry->v = v;

	ht_set(stackFrame->variableDictionary, variableName, entry);
	*/

	switch (v->value->valueType) {
	case INT32:
		DEBUG_LOG("%s = (int) %d\n", variableName, v->value->valueContainer.i);
		break;
	case UINT32:
		DEBUG_LOG("%s = (uint) %u\n", variableName, v->value->valueContainer.ui);
		break;

	}
}

void instructionLoad(VM * vm)
{
	unsigned char nameLength = vmNextByte(vm);
	char* variableName = vmNextString(vm, nameLength);

	StackFrame* stackFrame = callStackTop(vm->callStack);
	if (stackFrame == NULL) {
		ERROR_LOG("Top stack frame is null\n");
		return;
	}


	Variable* v = ht_get(stackFrame->variableDictionary, variableName);

	valueStackPush(vm->valueStack, *v->value);

	DEBUG_LOG("stackPush %s (%d)\n", variableName, v->value->valueContainer.i);
}

void instructionPush(VM * vm)
{
	unsigned char variableType = vmNextByte(vm);

	VALUE v;
	v.valueType = variableType;
	int i;
	unsigned int ui;

	switch (variableType) {
	case INT32:
		i = vmNextInt32(vm);
		v.valueContainer.i = i;
		DEBUG_LOG("stackPush (int) %d\n", i);
		break;
	case UINT32:
		ui = vmNextUInt32(vm);
		v.valueContainer.ui = ui;
		DEBUG_LOG("stackPush (uint) %u\n", ui);
		break;
	}

	valueStackPush(vm->valueStack, v);
}
