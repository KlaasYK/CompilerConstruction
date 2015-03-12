
#include <stdio.h>
#include <stdlib.h>

#include "symboltable.h"

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
		Node *n = (top->first)->next;
		// free the parameters list (if present)
		Node *param = (top->first)->parameters
		while (param != NULL) {
			Node *nextparam = param->next;
			free(param);
			param = nextparam;
		}
		free(list->first);
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
		List nextlist = top->nextlist;
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

/* return the node with the given name */
Node* getNode(char *name) {
	Node *n = NULL;
	List *c = symboltable->top;
	
	return n;
}

NodeType lookupType(char *name) {
	return 0;
}

int lookupEvalType(char *name, NodeType ntype) {
	return 0;
}

Node* lookupParams(char *name) {
	return NULL;
}
/* EOF symboltable.c */