#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdlib.h>
#include <stdbool.h>
#include "value.h"


/*
Variables are used in the variable dictionary "dictionary.h"
*/
typedef struct {
	char* key;
	bool isConstant;
	VALUE* value;
} Variable;

extern void varInit(Variable* variable);
extern void varFree(Variable* variable);
extern void varSetValue(Variable* variable, VALUE* value);

#endif