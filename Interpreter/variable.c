#include "variable.h"
#include "io.h"

void varInit(Variable * variable)
{
	variable->value = malloc(sizeof(VALUE));
}

void varFree(Variable * variable)
{
	free(variable->key);
	free(variable->value);
}

void varSetValue(Variable * variable, VALUE* value)
{
	if (variable->isConstant) { ERROR_LOG("Tried to change the value of a constant."); return; }
	variable->value = value;
}
