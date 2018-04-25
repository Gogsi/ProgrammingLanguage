/*
	STACK.H - defines two structures
	1) ValueStack - used for interpreting instructions
	2) CallStack - used for keeping track of subroutines and their variables
	Both stacks should only have ONE instance per interpreter.
*/

#ifndef STACK_H
#define STACK_H

#include "value.h"
#include "dictionary.h"
#include <stdio.h>

/*
* VALUE STACK
*/

///<summary>
///Defines the values stack which is used for interpreting instruction (eg. doing calculations)
///</summary>
typedef struct ValueStack {
	VALUE* values;
	int top;
	int maxSize;
} ValueStack;

extern void valueStackInit(ValueStack* currentStack, int maxSize);

extern int valueStackIsEmpty(ValueStack* currentStack);
extern int valueStackIsFull(ValueStack* currentStack);

extern void valueStackPush(ValueStack* currentStack, VALUE newValue);

extern VALUE valueStackTop(ValueStack* currentStack);

extern void valueStackPop(ValueStack* currentStack);

/*
* CALL STACK
*/

///<summary>
///Defines the stack frame, which keeps track of the variables in a subroutine
///</summary>
typedef struct StackFrame {
	HashTable* variableDictionary;
} StackFrame;

///<summary>
///Defines the call stack which is used for keeping track of subroutines and their variables
///</summary>
typedef struct CallStack {
	StackFrame* stackFrames;
	int top;
	int maxSize;
} CallStack;

extern void callStackInit(CallStack* currentStack, int maxSize);

extern int callStackIsEmpty(CallStack* currentStack);
extern int callStackIsFull(CallStack* currentStack);

extern void callStackPush(CallStack* currentStack, StackFrame newValue);

extern StackFrame callStackTop(CallStack* currentStack);

extern void callStackPop(CallStack* currentStack);


#endif
