#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


Stack createStack() {
	Stack s = malloc(sizeof(struct cellS));
	s->val = -1;
	s->sp = NULL;
	return s;
}

int isEmptyStack(Stack s) {
	if(s->sp == NULL && s-> val == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

Stack stack(Stack s, int val) {
	if(isEmptyStack(s)) {
		s->val = val;
		return s;
	}
	else {
		Stack top = createStack();
		top->val = val;
		top->sp = s;
		return top;
	}
}

Stack popStack(Stack s) {
	Stack mem = s;
	if(!isEmptyStack(s)) {
		if(mem->sp == NULL) {
			mem->val = -1;
		}
		else {
			mem = mem->sp;
			free(s);
		}
	}
	return mem;
}

void deleteStack(Stack s) {
	while(!isEmptyStack(s)) {
		s = popStack(s);
	}
	free(s);
}

void displayStack(Stack s) {
	Stack mem;
	printf("(");
	if(!isEmptyStack(s)) {
		for(mem = s; mem != NULL; mem = mem->sp) {
			if(mem->sp != NULL) {
				printf("%d, ", mem->val);
			}
			else {
				printf("%d", mem->val);
			}
		}
	}
	printf(")\n");
}
