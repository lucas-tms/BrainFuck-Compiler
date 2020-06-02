#include <stdio.h>

#include "list.h"
#include "parser.h"

int main(int argc, char const *argv[]) {
  List l;
  int minshift, maxshift;
  if(argc > 1)
    l = prepareCode(argv[1], &minshift, &maxshift);
  else
    l = prepareCode(NULL, &minshift, &maxshift);
  displayList(l);
  printf("%d, %d\n", minshift, maxshift);
  return 0;
}
