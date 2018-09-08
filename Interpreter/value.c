#include "value.h"


VALUE createValue()
{
	VALUE v;
	v.i = 0;
	return v;
}



void setValue_Int(VALUE* v, int value) {
	
	v->i = value;
}

void setValue_UInt(VALUE* v, unsigned int value) {
	v->ui = value;
}

void setValue_Int64(VALUE * v, long long  value)
{
	v->ll = value;
}

void setValue_UInt64(VALUE * v, unsigned long long  value)
{
	v->ull = value;
}

void setValue_Char(VALUE* v, char value) {
	v->c = value;
}

void setValue_UChar(VALUE* v, unsigned char value) {
	v->uc = value;
}

void setValue_Float(VALUE* v, float value) {
	v->f = value;
}

void setValue_Double(VALUE * v, double value)
{
	v->d = value;
}

void setValue_String(VALUE* v, char* value) {
	v->s = value;
}