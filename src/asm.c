#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "asm.h"
#include "list.h"

void writeCode(List l, int place, int minshift) {
  int fd = 1, brackets = 0; // mettre le nom de fichier assembleur en sortie
  bss(fd, place);

  char str[] = "section .text\n\tglobal _start\n\n_start:\n";
  write(fd, str, strlen(str));
}

void bss(int fd, int place) {
  char str[] = "section .bss\n\ttab resb ";
  write(fd, str, strlen(str));

  char nb[10];
  snprintf(nb, 10, "%d", place);
  write(fd, nb, strlen(nb));

  char str2[] = "\t;setting cells size\n\n";
  write(fd, str2, strlen(str2));


  if(place > 30000) {
    fprintf(stderr, "\033[1mbrain: \033[1;35mwarning: \033[0mmore than 30,000 cells are used\n");
  }
}
