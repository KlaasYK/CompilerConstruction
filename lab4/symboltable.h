/* Symboltable
 * Stack of linked lists
 */

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

/* EOF symboltable.h*/