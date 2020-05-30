#include <stdio.h>

#include "list.h"
#include "parser.h"

int main(int argc, char const *argv[]) {
  List l;
  if(argc > 1)
    l = prepareCode(argv[1]);
  else
    l = prepareCode(NULL);
  displayList(l);
  return 0;
}
