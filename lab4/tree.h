#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <stdio.h>

#include "expressiontree.h"

//enums

typedef enum {
    decStmnt, assStmnt, funcCallStmnt, procCallStmnt, readCallStmnt, writeCallStmnt, ifStmnt, doStmnt
} StmntKind;

typedef enum {
    constant, variable
} IDType;

typedef enum {
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

typedef struct IfStatement *If;

typedef struct DoStatement *Do;

typedef struct GuardedCommand *GCommand;

//struct defs

struct FunctionDefinition {
    ID id;
    int numParams;
    ID *params;
    int numStmnts;
    Stmnt *stmnts;
};

struct ProcedureDefinition {
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
        If ifStmnt;
        Do doStmnt;
    };
};

struct Declaration {
    ID id;
    IDType idType;
    ExpTree expTree;
};

struct Assignment {
    ID id;
    ExpTree expTree;
};

struct ReadCall {
    ID *ids;
};

struct WriteCall {
    Printable *items;
};

struct PrintableItem {
    PrintKind kind;

    union {
        char *string;
        Exp exp;
    };
};

struct ProcedureCall {
    char *name;
    int numParams;
    Exp *params;
};

struct IfStatement {
    int numGCommands;
    GCommand *gCommands;
};

struct DoStatement {
    int numGCommands;
    GCommand *gCommands;
};

struct GuardedCommand {
    Exp condition;
    int numStmnts;
    Stmnt *stmnts;
};
// func list

FuncDef makeFuncDef(ID id, int numParams, ID *params, int numStmnts, Stmnt *stmnts);
void freeFuncDef(FuncDef fd);

ProcDef makeProcDef(char *name, int numParams, ID *params, int numStmnts, Stmnt *stmnts);
void freeProcDef(ProcDef pd);

Stmnt makeDecStmnt(Dec d);
Stmnt makeAssStmnt(Ass a);
Stmnt makeFuncCallStmnt(FuncCall fc);
Stmnt makeProcCallStmnt(ProcCall pc);
Stmnt makeRCallStmnt(RCall rc);
Stmnt makeWCallStmnt(WCall wc);
Stmnt makeIfStmnt(If i);
Stmnt makeDoStmnt(Do d);
void freeStmnt(Stmnt s);

Dec makeDec(ID id, IDType idType, ExpTree expTree);
void freeDec(Dec d);

Ass makeAss(ID id, ExpTree expTree);
void freeAss(Ass a);

RCall makeRCall(ID *ids);
void freeRCall(RCall rc);

WCall makeWCall(Printable *p);
freeWCall(WCall wc);

Printable makeStringPrintable(char *string);
Printable makeExpPrintable(Exp exp);
void freePrintable(Printable p);

ProcCall makeProcCall(ID id, int numParams, Exp *params);
void freeProcCall(ProcCall pc);

If makeIf(GCommand *gcs);
void freeIf(If i);

Do makeDo(GCommand *gcs);
void freeDo(Do d);

GCommand makeGCommand(Exp condition, int numStmnts, Stmnt *stmnts);
void freeGCommand(GCommand gc);
#endif //TREE_H