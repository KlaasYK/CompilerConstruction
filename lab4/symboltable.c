
#include <stdio.h>
#include <stdlib.h>

#include "symboltable.h"

Node *makeNode(char *name, NodeType ntype, int etype, Node *param) {
	Node *n;
	n = malloc(sizeof(Node));
	if (n == NULL) {
		printf("Allocation error!\n");
		exit(1);
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

/* EOF symboltable.c */