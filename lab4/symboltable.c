
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"

Stack *symboltable = NULL;

int isMethod(char *name) {
	// TODO: check symboltable not null
	List *l = symboltable->top;
	while (l->nextlist != NULL) {
		l = l->nextlist;
	}
	/* bottom of the stack */
	Node *n = l->first;
	while (n != NULL) {
		if (strcmp(n->name, name) == 0 && n->type == METHOD) {
			return 1;
		}
		n = n->next;
	}
	return 0;
}

int getNumNodes(Node *n) {
	Node *t = n;
	int k = 0;
	while (t != NULL) {
		k++;
		t = t->next;
	}
	return k;
}

int existsInTop(char *name) {
	Node *n = symboltable->top->first;
	while (n != NULL) {
		if (strcmp(name, n->name) == 0) return 1;
		n = n->next;
	}
	return 0;
}


char *getTypeString(int typeval) {
	switch(typeval) {
		case BOOLEAN_TYPE: return "boolean";
		case CONST_BOOLEAN_TYPE: return "constant boolean";
		case REF_BOOLEAN_TYPE: return "boolean as reference";
		case INTEGER_TYPE: return "integer";
		case CONST_INTEGER_TYPE: return "constant integer";
		case REF_INTEGER_TYPE: return "integer reference";
		case VOID_TYPE: return "void";
	}
}

void printList(List *list, int level) {
	Node *n = list->first;
	while (n != NULL) {
		int i;
		for(i = 0; i < level; i++) {
			printf(" ");
		}
		printf("%s : %s", n->name, getTypeString(n->evaltype));
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
		printList(k, 2 * level);
		k = k->nextlist;
		level++;
	}
}

int stringToEvalType(char *typestring) {
	if (strcmp(typestring, "boolean") == 0 ) return BOOLEAN_TYPE;
	if (strcmp(typestring, "integer") == 0 ) return INTEGER_TYPE;
	if (strcmp(typestring, "void") == 0 ) return VOID_TYPE;
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
				return n;
			}
			n = n->next;
		}
		currentlist = currentlist->nextlist;
	}
	return NULL;
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