#include "stack.h"

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

int valueStackIsEmpty(ValueStack * currentStack)
{
	return currentStack->top == -1;
}

int valueStackIsFull(ValueStack * currentStack)
{
	return currentStack->top == currentStack->maxSize -1;
}

void valueStackPush(ValueStack* currentStack, VALUE newValue)
{
	if (valueStackIsFull(currentStack)) { //TODO: automaticaly create a bigger value stack?
		printf("Value stack is full");
		exit(1);
	}
	currentStack->values[++currentStack->top] = newValue;
}

VALUE valueStackTop(ValueStack * currentStack)
{
	return currentStack->values[currentStack->top];
}

void valueStackPop(ValueStack* currentStack)
{
	if (valueStackIsEmpty(currentStack)) {
		printf("Value stack is empty");
		exit(1);
	}
	currentStack->top--;

}

/*
CALL STACK
*/

void callStackInit(CallStack* currentStack, int maxSize)
{
	StackFrame* valueArray = malloc(sizeof(StackFrame) * maxSize);

	//currentStack = malloc(sizeof(currentStack));

	currentStack->maxSize = maxSize;
	currentStack->top = -1;
	currentStack->stackFrames = valueArray;
}

int callStackIsEmpty(CallStack * currentStack)
{
	return currentStack->top == -1;
}

int callStackIsFull(CallStack * currentStack)
{
	return currentStack->top == currentStack->maxSize - 1;
}

void callStackPush(CallStack* currentStack, StackFrame newValue)
{
	if (callStackIsFull(currentStack)) { //TODO: automaticaly create a bigger call stack?
		printf("Call stack is full");
		exit(1);
	}
	currentStack->stackFrames[++currentStack->top] = newValue;
}

StackFrame callStackTop(CallStack * currentStack)
{
	return currentStack->stackFrames[currentStack->top];
}

void callStackPop(CallStack* currentStack)
{
	if (callStackIsEmpty(currentStack)) {
		printf("Call stack is empty");
		exit(1);
	}
	currentStack->top--;

}