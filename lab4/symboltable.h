/* Symboltable
 * Stack of linked lists
 */
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define BOOLEAN 10
#define CONST_BOOLEAN 11;
#define INTEGER 20
#define CONST_INTEGER 21;
#define VOID 30

typedef enum { VARIABLE, METHOD } NodeType;

/* Stores the evaltype for each identifier */
typedef struct Node {
	char *name;
	NodeType type;
	int evaltype;
	Node *paramaters;
	Node *next;
} Node;

/* a list of nodes */
typedef struct List {
	Node *first;
	List *nextlist;
} List;

/* a stack of lists */
typedef struct Stack {
	List *top;
}

Stack *symboltable = NULL;

/* initialise the symbol table */
void initSymbolTable();
/* frees the memory of the symboltable*/
void freeSymbolTable();
/* puts an empty block on the stack */
void putBlock();
/* removes the top block from the stack */
void popBlock();
/* inserts an identifier in the current block */
void insertIdentifier(char *name, NodeType ntype, int etype, Node *paramlist);
/* returns identifier type */
NodeType lookupType(char *name);
/* returns the evaltype of the identifier (type or returntype) */
int lookupEvalType(char *name, NodeType ntype);
/* return the paramaterlist of an function */
Node* lookupParams(char *name);

#endif  // SYMBOLTABLE_H
/* EOF symboltable.h */