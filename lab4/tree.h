#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <stdio.h>

#include "expressiontree.h"

//enums

typedef enum {
    decStmnt, assStmnt, funcCallStmnt, procCallStmnt, readCallStmnt, writeCallStmnt, ifStmnt, doStmnt
} StmntKind;

typedef enum{
    constant, variable;
} IDType;

typedef enum{
    stringPrint, expPrint
} PrintKind;
//ref defs

typedef struct FunctionDefinition *FuncDef;

typedef struct ProcedureDefinition *ProcDef;

typedef struct Statement *Stmnt;

typedef struct Declaration *Dec;

typedef struct Assignment *Ass;

typedef struct ReadCall *RCall;

typedef struct WriteCall *WCall;

typedef struct PrintableItem *Printable;

// function call defined in expressiontree.h

typedef struct ProcedureCall *ProcCall;

typedef struct IfStatement *IfStmnt;

typedef struct DoStatement *DoStmnt;


//struct defs
struct FunctionDefinition{
    ID id;
    int numParams;
    ID *params;
    int numStmnts;
    Stmnt *stmnts;
};

struct ProcedureDefinition{
    char *name;
    int numParams;
    ID *params;
    int numStmnts;
    Stmnt *stmnts;
};

struct Statement {
    StmntKind kind;

    union {
        Dec dec;
        Ass assignment;
        FuncCall funcCall;
        ProcCall procCall;
        RCall rCall;
        WCall wCall;
        IfStmnt ifStmnt;
        DoStmnt doStmnt;
    };
};

struct Declaration{
    ID id;
    IDType idType;
    ExpTree expTree;
};

struct Assignment{
    ID id;
    ExpTree expTree;
};

struct ProcedureCall{
    ID id;
    int numParams;
    Exp *params;
    
};

struct ReadCall{
    ID *ids;
};

struct WriteCall{
    Printable *items;
};

struct PrintableItem{
    PrintKind kind;
    
    union{
        char *string;
        Exp exp; 
    };
};

struct ProcedureCall {
    char *name;
    int numParams;
    Exp *params;
};

// func list

#endif //TREE_H