
#include <stdio.h>
#include <stdlib.h>

#include "symboltable.h"

Stack *symboltable = NULL;


void printList(List *list, int level) {
	Node *n = list->first;
	while (n != NULL) {
		int i;
		for(i = 0; i < level; i++) {
			printf(" ");
		}
		printf("%s : %d", n->name, n->evaltype);
		printf("\n");
		n = n->next;
	}
}

void printSymbolTable() {
	int level = 0;
	if (symboltable == NULL) {
		printf("Symboltable not initialised!\n");
		exit(EXIT_FAILURE);
	}
	List *k = symboltable->top;
	while (k != NULL) {
		List *nextlist = k->nextlist;
		printList(k, 2 * level);
		k = nextlist;
		level++;
	}
}

int stringToEvalType(char *typestring) {
	if (strcmp(typestring, "boolean") == 0 ) return BOOLEAN_TYPE;
	return -1;
}

Node *makeNode(char *name, NodeType ntype, int etype, Node *param) {
	Node *n;
	n = malloc(sizeof(Node));
	if (n == NULL) {
		printf("Allocation error!\n");
		exit(EXIT_FAILURE);
	}
	n->name = name;
	n->type = ntype;
	n->evaltype = etype;
	n->parameters = param;
	n->next = NULL;
	return n;
}

void freeNode(Node *nodeptr) {
	// free the parameters list (if present)
	Node *param = nodeptr->parameters;
	while (param != NULL) {
		Node *nextparam = param->next;
		free(param);
		param = nextparam;
	}
	// Free the name here
	free(nodeptr->name);
	free(nodeptr);
}

void initSymbolTable() {
	symboltable = malloc(sizeof(Stack));
	List *top =  malloc(sizeof(List));
	if (top == NULL || symboltable == NULL) {
		printf("Allocation error!\n");
		exit(EXIT_FAILURE);
	}
	/* make the first (global) scope empty */
	top->first = NULL;
	top->nextlist = NULL;
	symboltable->top = top;
}

void freeList(List *list) {
	// free all list items
	while (list->first != NULL) {
		Node *n = (list->first)->next;
		freeNode(list->first);
		list->first = n;
	}
	// free the list itself
	free(list);
}

void freeSymbolTable() {
	if (symboltable == NULL) {
		printf("Symboltable not initialised!\n");
		exit(EXIT_FAILURE);
	}
	while (symboltable->top != NULL) {
		List *top = symboltable->top;
		List *nextlist = top->nextlist;
		freeList(top);
		symboltable->top = nextlist;
	}
	// free the symboltable
	free(symboltable);
}

void putBlock() {
	if (symboltable == NULL) {
		printf("Symboltable not initialised!\n");
		exit(EXIT_FAILURE);
	}
	List *newtop = malloc(sizeof(List));
	if (newtop == NULL) {
		printf("Allocation error!\n");
		exit(EXIT_FAILURE);
	}
	newtop->first = NULL;
	newtop->nextlist = symboltable->top;
	symboltable->top = newtop;
}

void popBlock() {
	if (symboltable == NULL) {
		printf("Symboltable not initialised!\n");
		exit(EXIT_FAILURE);
	}
	if (symboltable->top == NULL) {
		printf("Symboltable empty!\n");
		exit(EXIT_FAILURE);
	}
	List *oldtop = symboltable->top;
	symboltable->top = oldtop->nextlist;
	freeList(oldtop);
	free(oldtop);
}

void insertIdentifier(char *name, NodeType ntype, int etype, Node *paramlist) {
	Node *n = malloc(sizeof(Node));
	if (n == NULL) {
		printf("Allocation eror!\n");
		exit(EXIT_FAILURE);
	}
	n->name = name;
	n->type = ntype;
	n->evaltype = etype;
	n->parameters = paramlist;
	n->next = (symboltable->top)->first;
	(symboltable->top)->first = n;
}

/* return the node with the given name or NULL when not found */
Node* getNode(char *name) {
	Node *n = NULL;
	List *currentlist = symboltable->top;
	while (currentlist != NULL) {
		n = currentlist->first;
		while(n != NULL) {
			if (strcmp(n->name, name) == 0 ) {
				// Found it!
				continue;
			}
			n = n->next;
		}
		if (n == NULL) {
			// Reached end of current list
			currentlist = currentlist->nextlist;
		}
	}
	return n;
}

NodeType lookupType(char *name) {
	Node *n = getNode(name);
	if (n != NULL) {
		return n->type;
	}
	return -1;

}

int lookupEvalType(char *name, NodeType ntype) {
	Node *n = getNode(name);
	if (n != NULL) {
		if (n->type != ntype) {
			// identifier of wrong type (function is not a variable! or vice versa)
			return -1;
		}
		return n->evaltype;
	}
	return -1;
}

Node* lookupParams(char *name) {
	Node *n = getNode(name);
	if (n != NULL) {
		return n->parameters;
	}
	return NULL;
}
/* EOF symboltable.c */