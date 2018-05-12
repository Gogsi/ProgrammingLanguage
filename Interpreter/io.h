#ifndef IO_H
#define IO_H

#include <stdio.h>

#define ERROR_LOG(x, ...) fprintf(stderr, "Error: "); fprintf(stderr, x, __VA_ARGS__)

#if defined(_DEBUG) || defined(DEBUG)
#define DEBUG_LOG(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_LOG 
#endif// _DEBUG


extern FILE* openFile(char* fileName);
extern void closeFile(FILE* file);

extern unsigned char* readAllBytes(FILE* file, int* fileLength);

//extern int bytesToInt(char* buf);

#endif