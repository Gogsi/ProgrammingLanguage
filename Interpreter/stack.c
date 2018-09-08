#include "stack.h"
#include "io.h"
#include <stdlib.h>

/*
VALUE STACK
*/

void valueStackInit(ValueStack* currentStack, int maxSize)
{
	VALUE* valueArray = malloc(sizeof(VALUE) * maxSize);

	//currentStack = malloc(sizeof(currentStack));

	currentStack->maxSize = maxSize;
	currentStack->top = -1;
	currentStack->values = valueArray;
}

bool valueStackIsEmpty(ValueStack * currentStack)
{
	return currentStack->top == -1;
}

bool valueStackIsFull(ValueStack * currentStack)
{
	return currentStack->top == currentStack->maxSize -1;
}

int valueStackLength(ValueStack * currentStack)
{
	return currentStack->top + 1;
}

void valueStackPush(ValueStack* currentStack, VALUE newValue)
{
	if (valueStackIsFull(currentStack)) { 
		//Doubles the stack size
		currentStack->maxSize *= 2;
		currentStack->values = realloc(currentStack->values, currentStack->maxSize * sizeof(VALUE));
		if (currentStack->values == NULL) {
			ERROR_LOG("Couldn't resize value stack");
			exit(1);
		}
		else {
			DEBUG_LOG("Resized value stack to " + currentStack->maxSize);
		}
	}
	currentStack->values[++currentStack->top] = newValue;
}

VALUE* valueStackTop(ValueStack * currentStack)
{
	return &currentStack->values[currentStack->top];
}

void valueStackPop(ValueStack* currentStack)
{
	if (valueStackIsEmpty(currentStack)) {
		ERROR_LOG("Value stack is empty");
		exit(1);
	}
	currentStack->top--;

}

void valueStackFree(ValueStack* currentStack)
{
	free(currentStack->values);
}

/*
STACK FRAME
*/

void stackFrameInit(StackFrame* currentFrame, char* name, unsigned short varArraySize)
{
	currentFrame->frameName = name;
	currentFrame->varArraySize = varArraySize;
	currentFrame->varArray = malloc(sizeof(VALUE) * varArraySize);

	for (int i = 0; i < varArraySize; i++) {
		currentFrame->varArray[i].i = 0;
	}
}

void stackFrameFree(StackFrame * currentFrame)
{
	free(currentFrame->frameName);
	free(currentFrame->varArray);
}

/*
CALL STACK
*/

void callStackInit(CallStack* currentStack, int maxSize)
{
	StackFrame* frames = malloc(sizeof(StackFrame) * maxSize);

	//currentStack = malloc(sizeof(currentStack));

	currentStack->maxSize = maxSize;
	currentStack->top = -1;
	currentStack->stackFrames = frames;
}

bool callStackIsEmpty(CallStack * currentStack)
{
	return currentStack->top == -1;
}

bool callStackIsFull(CallStack * currentStack)
{
	return currentStack->top == currentStack->maxSize - 1;
}

int callStackLength(CallStack * currentStack)
{
	return currentStack->top + 1;
}

void callStackPush(CallStack* currentStack, StackFrame newValue)
{
	if (callStackIsFull(currentStack)) { 
		currentStack->maxSize *= 2;
		currentStack->stackFrames = realloc(currentStack->stackFrames, currentStack->maxSize * sizeof(StackFrame));
		if (currentStack->stackFrames == NULL) {
			ERROR_LOG("Couldn't resize call stack");
			exit(1);
		}
		else {
			DEBUG_LOG("Resized the call stack to " + currentStack->maxSize);
		}
	}
	currentStack->stackFrames[++currentStack->top] = newValue;
}

StackFrame* callStackTop(CallStack * currentStack)
{
	return &currentStack->stackFrames[currentStack->top];
}

void callStackPop(CallStack* currentStack)
{
	if (callStackIsEmpty(currentStack)) {
		ERROR_LOG("Call stack is empty");
		exit(1);
	}
	currentStack->top--;

}

void callStackFree(CallStack * currentStack)
{
	for (int i = 0; i < currentStack->maxSize; i++) {
		if (&currentStack->stackFrames[i] != NULL) {
			stackFrameFree(&currentStack->stackFrames[i]);
		}
	}
	free(currentStack->stackFrames);
}

StackFrame * callStackGlobal(CallStack * currentStack)
{
	return &currentStack->stackFrames[0];
}
