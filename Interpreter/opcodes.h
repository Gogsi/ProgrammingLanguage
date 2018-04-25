#pragma once

///<summary> An enum containing all bytecode instructions that the VM can interpret</summary>
typedef enum OPCODES{
	CONST = 0x1A,
	VAR = 0x2A,
	STORE = 0x3A,

	ADD = 0xA0,
	SUB = 0xA1,
	MUL = 0xA2,
	DIV = 0xA3,

	CALL = 0xF0,
	SYSCALL = 0xF1
} opcodes_t;

//extern void opcode_const();

//typedef enum OPCODES Opcodes;
