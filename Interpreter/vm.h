#ifndef VM_H
#define VM_H
#include "stack.h"
#include <stdbool.h>

extern const unsigned char  VM_VERSION_MAJOR;
extern const unsigned char  VM_VERSION_MINOR;
extern const unsigned char* VM_VERSION;

extern const unsigned char* VM_HEADER_SIZE;
extern unsigned char VM_MAGIC_NUMBER[4];

typedef struct {
	unsigned char* fileContents;

	///<summary>Decides the endianness in the file format(1 - little-endian, 0 - big-endian)</summary>
	bool isLittleEndian;

	unsigned long fileSize;

	ValueStack* valueStack;
	CallStack* callStack;

	///<summary>The current position in the VM content array</summary>
	unsigned long fileIndex;

} VM;

///<summary> Allocates memory for the VM object and reads the file header </summary>
///	<param name="vm"> A pointer to the VM object </param>
///	<param name="fileContents"> A C string (char array) that contains the entire bytecode file </param>
///	<param name="fileSize"> This size of the bytecode file </param>
extern void vmInit(VM* vm, unsigned char* fileContents, unsigned long fileSize);

///<summary> The main VM interpreter function </summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void vmMain(VM* vm);

///<summary> Deallocates all memory, used by the VM </summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void vmFree(VM* vm);

///<summary> Reads the next byte as an unsigned char </summary>
///	<param name="vm"> A pointer to the VM object </param>
extern unsigned char vmNextByte(VM* vm);

///<summary> Reads the next 2 bytes as an unsigned short </summary>
///	<param name="vm"> A pointer to the VM object </param>
extern unsigned short vmNextUShort(VM* vm);

///<summary> Reads the next 4 bytes as an int </summary>
///	<param name="vm"> A pointer to the VM object </param>
extern int vmNextInt32(VM * vm);

///<summary> Reads the next 4 bytes as an unsigned int </summary>
///	<param name="vm"> A pointer to the VM object </param>
extern unsigned int vmNextUInt32(VM * vm);

///<summary> Reads the next length bytes as an char array </summary>
///	<param name="vm"> A pointer to the VM object </param>
///	<param name="length"> The amount of bytes to read </param>
extern char* vmNextString(VM * vm, unsigned char length);

// The instructions are implemented in vmInstructions.c

///<summary> Adds a new StackFrame to the call stack
///<para>Followed by 2 bytes (varArraySize)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionStackFrame(VM* vm);

///<summary> Stores the value at the top of the stack to a variable 
///<para>Followed by 2 bytes (varId)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionStore(VM* vm);

///<summary> Pushes the value of a variable to the stack
///<para>Followed by 2 bytes (varId)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionLoad(VM* vm);

///<summary> Pushes a INT32 value to the stack
///<para>Followed by 4 bytes for the value</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionPush_Int(VM* vm);

///<summary> Pushes a UINT32 value to the stack
///<para>Followed by 4 bytes for the value</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionPush_UInt(VM* vm);

///<summary> Pops the top two values of the stack and adds them as INT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionAdd_Int(VM* vm);

///<summary> Pops the top two values of the stack and adds them as UINT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionAdd_UInt(VM* vm);

///<summary> Pops the top two values of the stack and subtracts them as INT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionSub_Int(VM* vm);

///<summary> Pops the top two values of the stack and subtracts them as UINT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionSub_UInt(VM* vm);

///<summary> Pops the top two values of the stack and multiplies them as INT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionMul_Int(VM* vm);

///<summary> Pops the top two values of the stack and multiplies them as UINT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionMul_UInt(VM* vm);

///<summary> Pops the top two values of the stack and divides them as INT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionDiv_Int(VM* vm);

///<summary> Pops the top two values of the stack and divides them as UINT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionDiv_UInt(VM* vm);

///<summary> Pops the top two values of the stack and calculates the remainder after division as INT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionMod_Int(VM* vm);

///<summary> Pops the top two values of the stack and divides them as UINT32
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionMod_UInt(VM* vm);
#endif