#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "asm.h"
#include "list.h"

void writeCode(List l, int place, int minshift) {
  int fd = open("file.asm", O_WRONLY|O_CREAT);
  int brackets = 0;

  /* Intializing place for the cells */
  bss(fd, place);

  /* Beginning of the program */
  char str[] = "section .text\n\tglobal _start\n\n_start:\n";
  write(fd, str, strlen(str));
  setMemZero(fd, place);

  /* Shifting to center the pointer */
  initialShift(fd, minshift);

  /* The program */
  List mem;
  for(mem = l; mem != NULL; mem = mem->fo) {
    switch (mem->val->symb) {
      case '+':
        add(fd, mem->val->nb);
        break;
      case '-':
        sub(fd, mem->val->nb);
        break;
      case '<':
        leftShift(fd, mem->val->nb);
        break;
      case '>':
        rightShift(fd, mem->val->nb);
        break;
      case '[':
        openingBracket(fd, mem->val->nb, &brackets);
        break;
      case ']':
        closingBracket(fd, mem->val->nb, &brackets);
        break;
      case '.':
        dot(fd, mem->val->nb);
        break;
      case ',':
        comma(fd, mem->val->nb);
        break;
    }
  }

  /* Exiting the program */
  dprintf(fd, "\n\tmov eax, 1\t;exiting the program\n\tint 0x80\n");
  deleteList(l);
  close(fd);
}


void bss(int fd, int place) {
  char str[] = "section .bss\n\ttab resb ";
  write(fd, str, strlen(str));

  char nb[10];
  snprintf(nb, 10, "%d", place);
  write(fd, nb, strlen(nb));

  char str2[] = "\t;setting cells number\n\n";
  write(fd, str2, strlen(str2));


  if(place > 30000) {
    fprintf(stderr, "\033[1mbrain: \033[1;35mwarning: \033[0mmore than 30,000 cells are used\n");
  }
}


void setMemZero(int fd, int place) {
  dprintf(fd, "\tmov ecx, %d\ninit:\n\tlea eax, [tab+ecx-1]\n\tmov [eax], 0\n\tloop init\t;setting all memory cells to zero\n\n", place);
}


void initialShift(int fd, int minshift) {
  if(minshift != 0) dprintf(fd, "\tlea eax, [tab+%d]\t;centering the pointer\n\n", -minshift);
}



// +
void add(int fd, int nb) {
  dprintf(fd, "\tadd byte [eax], %d\n", nb);
}

// -
void sub(int fd, int nb) {
  dprintf(fd, "\tsub byte [eax], %d\n", nb);
}

// <
void leftShift(int fd, int nb) {
  dprintf(fd, "\tsub eax, %d\n", nb); // same as lea eax, [tab-nb] ??
}

// >
void rightShift(int fd, int nb) {
  dprintf(fd, "\tadd eax, %d\n", nb); // idem
}

// [
void openingBracket(int fd, int nb, int* brackets) {
  (*brackets)++;
  dprintf(fd, "\nbrack%d:\n", *brackets);
}

// ]
void closingBracket(int fd, int nb, int* brackets) {
  dprintf(fd, "\tcmp [eax], 0\n\tjne brack%d\n\n", *brackets);
  (*brackets)--;
}

// .
void dot(int fd, int nb) {
  for(int i = 0; i < nb; i++) {
    dprintf(fd, "\n\tpush eax\n\n");

    dprintf(fd, "\tmov ecx, eax\n");
    dprintf(fd, "\tmov eax, 4\n");
    dprintf(fd, "\tmov ebx, 1\n");
    dprintf(fd, "\tmov edx, 1\n\n");

    dprintf(fd, "\tint 0x80\n");
    dprintf(fd, "\tpop eax\n\n");
  }
}

// ,
void comma(int fd, int nb) {
}
