#pragma once

///<summary> An enum containing all bytecode instructions that the VM can interpret</summary>
typedef enum OPCODES{

	STORE = 0x3A, 
	LOAD = 0x4A, 

	I32PUSH = 0x5A, 
	UI32PUSH = 0x5B,

	I32ADD = 0xA0,
	I32SUB = 0xA1,
	I32MUL = 0xA2,
	I32DIV = 0xA3,
	I32MOD = 0xA4,

	UI32ADD = 0xB0,
	UI32SUB = 0xB1,
	UI32MUL = 0xB2,
	UI32DIV = 0xB3,
	UI32MOD = 0xB4,

	SYSCALL = 0x0D,
	CALL = 0x0E,
	STACKFRAME = 0x0F
} opcodes_t;

//extern void opcode_const();

//typedef enum OPCODES Opcodes;
