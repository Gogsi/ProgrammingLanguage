#ifndef IO_H
#define IO_H

#include <stdio.h>

extern FILE* openFile(char* fileName);
extern void closeFile(FILE* file);

extern unsigned char* readAllBytes(FILE* file, int* fileLength);

//extern int bytesToInt(char* buf);

#endif