#include <stdio.h>
#include "list.h"

int main(int argc, char const *argv[]) {
  List l = createList();

  displayList(l);
  append(l, createPair('+', 3));
  append(l, createPair('>', 8));
  displayList(l);
  l = pop(l);
  displayList(l);

  deleteList(l);
  return 0;
}
