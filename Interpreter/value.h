#ifndef VALUE_H
#define VALUE_H

///<summary>The value type enum which list all available types.</summary>
typedef enum  VALUE_TYPE {
	INT32 = 0x0,
	UINT32 = 0x1,

	INT64 = 0x2,
	UINT64 = 0x3,

	CHAR = 0x4,
	UCHAR = 0x5,

	FLOAT = 0x6,
	DOUBLE = 0x7,

	STRING = 0x8 //TODO: Maybe string shouldn't be a value type?
} VALUE_TYPE;

///<summary>The value container which will take 8 bytes for every variable type.</summary>
typedef union VALUE_CONTAINER {
	int i; // Integer
	unsigned int ui; //Unsigned integer

	long long ll;
	unsigned long long ull;

	char c; //Character
	unsigned char uc; //Unsigned character

	float f;
	double d; //Float

	char* s;//String
} VALUE;



extern void setValue_Int(VALUE* v, int value);
extern void setValue_UInt(VALUE* v, unsigned int value);

extern void setValue_Int64(VALUE* v, long long value);
extern void setValue_UInt64(VALUE* v, unsigned long long value);

extern void setValue_Char(VALUE* v, char value);
extern void setValue_UChar(VALUE* v, unsigned char value);


extern void setValue_Float(VALUE* v, float value);
extern void setValue_Double(VALUE* v, double value);

extern void setValue_String(VALUE* v, char* value);

#endif