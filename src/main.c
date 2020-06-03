#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  writeCode(l, placeToAllocate(minshift, maxshift), minshift, strdup(argv[3]));
  return 0;
}
