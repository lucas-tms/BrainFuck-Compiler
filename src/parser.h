#ifndef PARSER
#define PARSER

#include "list.h"

List prepareCode(const char* file, int* minshift, int* maxshift);
int placeToAllocate(int min, int max);

#endif
