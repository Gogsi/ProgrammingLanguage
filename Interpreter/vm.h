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

	ValueStack* valueStack; //TODO: malloc these
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

///<summary> Defines a constant 
///<para>Followed by 1 byte (name_length), name_length bytes (variableName), 1 byte (value_type) and the sizeof(value_type) bytes for the value)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionConst(VM* vm);

///<summary> Defines a variable 
///<param>Followed by 1 byte (name_length) and name_length bytes (variableName)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionVar(VM* vm);

///<summary> Stores the value at the top of the stack to a variable 
///<para>Followed by 1 byte (name_length) and name_length bytes (variableName)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionStore(VM* vm);

///<summary> Pushes the value of a variable to the stack
///<para>Followed by 1 byte (name_length) and name_length bytes (variableName)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionLoad(VM* vm);

///<summary> Pushes a value to the stack
///<para>Followed by 1 byte (value_type) and the sizeof(value_type) bytes for the value)</para>
///</summary>
///	<param name="vm"> A pointer to the VM object </param>
extern void instructionPush(VM* vm);
#endif