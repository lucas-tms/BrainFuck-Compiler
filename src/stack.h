#ifndef STACK
#define STACK

/* Defining the Stack structure
   A Stack points to a cell ... */

struct cellS {
	struct cellS *sp;
	int val;
};
typedef struct cellS* Stack;


Stack createStack();
int isEmptyStack(Stack s);
Stack stack(Stack s, int val);
Stack popStack(Stack s);
void deleteStack(Stack s);
void displayStack(Stack s);

#endif
