#include <stdio.h>

#include "list.h"
#include "parser.h"
#include "asm.h"

int main(int argc, char const *argv[]) {
  List l;
  int minshift, maxshift;
  if(argc > 1) l = prepareCode(argv[1], &minshift, &maxshift);
  else l = prepareCode(NULL, &minshift, &maxshift);
  displayList(l);

  writeCode(l, placeToAllocate(minshift, maxshift), minshift);
  return 0;
}
