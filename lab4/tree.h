#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <stdio.h>

//enums
typedef enum{
    
} StmntKind;

//ref defs
typedef struct Statement *Stmnt;

typedef struct FunctionDefinition *FuncDef;

typedef struct ProcedureDefinition *ProcDef;

typedef struct Assignment *Ass;

typedef struct ReadCall *RCall;

typedef struct WriteCall *WCall;

typedef struct ProcedureCall *ProcCall;


//struct defs
struct Statement{
    StmntKind kind;
    
};


// func list

#endif //TREE_H