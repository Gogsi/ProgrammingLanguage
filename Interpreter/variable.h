#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdlib.h>

#include "value.h"


/*
Variables are used in the variable dictionary "dictionary.h"
*/
typedef struct {
	char* key;
	//int number;
	VALUE value;
} Variable;


#endif