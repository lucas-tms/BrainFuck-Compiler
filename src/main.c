#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#include "list.h"
#include "parser.h"
#include "asm.h"

int main(int argc, char const *argv[]) {
  List l;
  int minshift, maxshift;

  if(argc == 4) {
    if(strcmp(argv[2], "-o") != 0) {
      fprintf(stderr, "Usage: brain <input> -o <output>\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Usage: brain <input> -o <output>\n");
    exit(EXIT_FAILURE);
  }

  if(strcmp(argv[1], "-") == 0) {
    l = prepareCode(NULL, &minshift, &maxshift);
  }
  else {
    l = prepareCode(argv[1], &minshift, &maxshift);
  }

  int n = strlen(argv[3]);
  char* name = realloc(strdup(argv[3]), sizeof(char)* (n+5));
  strcat(name, ".asm");

  writeCode(l, placeToAllocate(minshift, maxshift), minshift, name);

  if(fork() == 0) {
    execlp("nasm", "nasm", "-f", "elf", name, NULL);
    exit(EXIT_SUCCESS);
  }
  else {
    wait(NULL);
  }
  name[n+1] = 'o';
  name[n+2] = '\0';

  if(fork() == 0) {
    execlp("ld", "ld", "-s", "-m", "elf_i386", "-o", argv[3], name, NULL);
    exit(EXIT_SUCCESS);
  }
  else {
    wait(NULL);
  }
  free(name);

  return 0;
}
