/* Symboltable
 * Stack of linked lists
 */
#ifndef __SYMBOLTABLE_H
#define __SYMBOLTABLE_H

#define BOOLEAN_TYPE 10
#define CONST_BOOLEAN_TYPE 11
#define REF_BOOLEAN_TYPE 12
#define INTEGER_TYPE 20
#define CONST_INTEGER_TYPE 21
#define REF_INTEGER_TYPE 22
#define VOID_TYPE 30

typedef enum { VARIABLE, METHOD } NodeType;

/* Stores the evaltype for each identifier */


typedef struct Node {
	char *name;
	NodeType type;
	int evaltype;
	struct Node *parameters;
	struct Node *next;
} Node;

/* a list of nodes */
typedef struct List {
	Node *first;
	struct List *nextlist;
} List;

/* a stack of lists */
typedef struct Stack {
	List *top;
} Stack;

/* convert input type string to integer for faster comparisson */
int stringToEvalType(char *typestring);

void printSymbolTable();

/* returns whetere the current name is found in the top of the symboltable */
int existsInTop(char *name);

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