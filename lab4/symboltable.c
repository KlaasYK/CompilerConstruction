
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
	List top =  malloc(sizeof(List));
	if (top == NULL) {
		printf("Allocation error!\n");
		exit(EXIT_FAILURE);
	}
	/* make the first (global) scope empty */
	top->first = NULL;
	top->nextlist = NULL;
}

void freeSymbolTable() {
	
}

void insertIdentifier(char *name, NodeType ntype, int etype, Node *paramlist) {
	
}

/* EOF symboltable.c */