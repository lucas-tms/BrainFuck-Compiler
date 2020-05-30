#ifndef LIST
#define LIST

/* Defining the Pair structure
   A pair is able to store a symbol : symb encountered and
   the number of repetition of this symbol : nb */

struct pair {
  char symb;
  int nb;
};
typedef struct pair* Pair;

/* Defining the List structure
   A List points to a cell
   A cell is defined as containing a follower : fo and a value : val

   - fo points to the next cell, is NULL if it is the last element of the list
   - val stores the value to keep in the list */

struct cell {
	struct cell *fo;
	Pair val;
};
typedef struct cell* List;


List createList();
int isEmpty(List l);
List append(List l, Pair p);
List pop(List l);
void deleteList(List l);
void displayList(List l);
int size(List l);
void displayPair(Pair p);
Pair createPair(char symb, int nb);

#endif
