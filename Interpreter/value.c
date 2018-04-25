#include "value.h"

VALUE_CONTAINER createValueContainer()
{
	VALUE_CONTAINER vc;
	vc.i = 0;
	return vc;
}

VALUE createValue()
{
	VALUE v;
	v.valueType = INT32;
	v.valueContainer = createValueContainer();

	return v;
}

void setValue(VALUE* v, VALUE_CONTAINER value, VALUE_TYPE type) {
	v->valueType = type;
	v->valueContainer = value;
}

void setValue_Int(VALUE* v, int value) {
	v->valueType = INT32;
	v->valueContainer.i = value;
}

void setValue_UInt(VALUE* v, unsigned int value) {
	v->valueType = UINT32;
	v->valueContainer.ui = value;
}

void setValue_Int64(VALUE * v, long long  value)
{
	v->valueType = INT64;
	v->valueContainer.ll = value;
}

void setValue_UInt64(VALUE * v, unsigned long long  value)
{
	v->valueType = UINT64;
	v->valueContainer.ull = value;
}

void setValue_Char(VALUE* v, char value) {
	v->valueType = CHAR;
	v->valueContainer.c = value;
}

void setValue_UChar(VALUE* v, unsigned char value) {
	v->valueType = UCHAR;
	v->valueContainer.uc = value;
}



void setValue_Float(VALUE* v, float value) {
	v->valueType = FLOAT;
	v->valueContainer.f = value;
}

void setValue_Double(VALUE * v, double value)
{
	v->valueType = DOUBLE;
	v->valueContainer.d = value;
}

void setValue_String(VALUE* v, char* value) {
	v->valueType = STRING;
	v->valueContainer.s = value;
}