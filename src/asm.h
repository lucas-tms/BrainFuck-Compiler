#ifndef ASM
#define ASM

#include "list.h"

void writeCode(List l, int place, int minshift, char* name);
void bss(int fd, int place);
void setMemZero(int fd, int place);
void initialShift(int fd, int minshift);
void add(int fd, int nb);
void sub(int fd, int nb);
void leftShift(int fd, int nb);
void rightShift(int fd, int nb);
void openingBracket(int fd, int nb, int* brackets);
void closingBracket(int fd, int nb, int* brackets);
void dot(int fd, int nb);
void comma(int fd, int nb);

#endif
