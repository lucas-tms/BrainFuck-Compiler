#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "parser.h"
#include "list.h"

/* This function creates a list of the symbols that are repeated and exit
   the process if there is not the same number of opening and closing
   brackets */

List prepareCode(const char* file, int* minshift, int* maxshift) {
  int fd;
  if(file != NULL) {
    fd = open(file, O_RDONLY);
  }
  else {
    fd = 0;
  }

  List l = createList();
  char c, previousSymb = 0;
  int nb = 0, bracketCounter = 0, shift = 0;
  *minshift = 0, *maxshift = 0;

  /* Reading the program and creating the associated list */
  while(read(fd, &c, 1) > 0) {
    switch (c) {
      case '[':
      case ']':
      case '+':
      case '-':
      case '<':
      case '>':
      case '.':
      case ',':
        if (c == '[')
          bracketCounter++;
        else if(c == ']')
          bracketCounter--;
        else if(c == '>') {
          shift++;
          *maxshift = (*maxshift > shift) ? *maxshift : shift;
        }
        else if(c == '<') {
          shift--;
          *minshift = (*minshift < shift) ? *minshift : shift;
        }

        if(c != previousSymb && nb != 0) {
          l = append(l, createPair(previousSymb, nb));
          nb = 1;
        }
        else {
          nb++;
        }
        previousSymb = c;
        break;
      default:
        break;
    }
  }
  l = append(l, createPair(previousSymb, nb));
  // displayList(l);

  /* Closing the file descriptor */
  if(fd > 0)
    close(fd);

  /* Checking the number of brackets */
  if(bracketCounter != 0) {
    fprintf(stderr, "\033[1mbrain: \033[1;31merror: \033[0mexpected same number of opening and closing brackets\n");
    exit(EXIT_FAILURE);
  }

  return l;
}


/* This functions works out the number of bytes to allocate to give to the
  program */

int placeToAllocate(int min, int max) {
  return max - min + 1;
}
