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
    stringKind, expKind
} PrintKind;

typedef enum {
    byRef, byVal
} Call;
//ref defs

typedef struct Program *Prog;

typedef struct FunctionDefinition *FuncDef;

typedef struct ProcedureDefinition *ProcDef;

typedef struct Parameter *Param;

typedef struct Statement *Stmnt;

typedef struct Declaration *Dec;

typedef struct Assignment *Ass;

typedef struct ReadCall *RCall;

typedef struct WriteCall *WCall;

typedef struct PrintableItem *Printable;

typedef struct IfStatement *If;

typedef struct DoStatement *Do;

typedef struct GuardedCommand *GCommand;

//struct defs

struct Program {
    char *name;
    int numConstDefs;
    Dec *constDefs;
    int numVarDefs;
    Dec *varDefs;
    int numProcDefs;
    ProcDef *procDefs;
    int numFuncDefs;
    FuncDef *funcDefs;
    int numBodyStmnts;
    Stmnt *bodyStmnts;
};

struct FunctionDefinition {
    ID id;
    int numParams;
    Param *params;
    int numStmnts;
    Stmnt *stmnts;
};

struct ProcedureDefinition {
    char *name;
    int numParams;
    Param *params;
    int numStmnts;
    Stmnt *stmnts;
};

struct Parameter{
    ID id;
    Call call;
};

struct Statement {
    StmntKind kind;

    union {
        Dec dec;
        Ass assignment;
        FuncCall funcCall;
        RCall rCall;
        WCall wCall;
        If ifStmnt;
        Do doStmnt;
    };
};

struct Declaration {
    ID id;
    IDType idType;
    PrintKind decType;
    BoolVal isInitialized;
    union{
        ExpTree expTree;
        char *str;
    };
};

struct Assignment {
    ID id;
    ExpTree expTree;
    int lineNr;
};

struct ReadCall {
    int numids;
    ID *ids;
};

struct WriteCall {
    int numitems;
    Printable *items;
    BoolVal newLine;
};

struct PrintableItem {
    PrintKind kind;

    union {
        char *string;
        ExpTree exp;
    };
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
    ExpTree condition;
    int numStmnts;
    Stmnt *stmnts;
};
// func list

Prog makeProg(char *name, int numConstDefs, Dec *constDefs, int numVarDefs, Dec *varDefs, int numProcDefs, ProcDef *procDefs, int numFuncDefs, FuncDef *funcDefs, int numBodyStmnts, Stmnt *bodyStmnts);
void freeProg(Prog p);

FuncDef makeFuncDef(ID id, int numParams, Param *params, int numStmnts, Stmnt *stmnts);
void freeFuncDef(FuncDef fd);

ProcDef makeProcDef(char *name, int numParams, Param *params, int numStmnts, Stmnt *stmnts);
void freeProcDef(ProcDef pd);

Param makeParam(ID id, Call call);
void freeParam(Param p);

Stmnt makeDecStmnt(Dec d);
Stmnt makeAssStmnt(Ass a);
Stmnt makeFuncCallStmnt(FuncCall fc);
Stmnt makeRCallStmnt(RCall rc);
Stmnt makeWCallStmnt(WCall wc);
Stmnt makeIfStmnt(If i);
Stmnt makeDoStmnt(Do d);
void freeStmnt(Stmnt s);

Dec makeExpUninitDec(ID id, IDType idType);
Dec makeExpDec(ID id, IDType idType, ExpTree expTree);
Dec makeStringDec(ID id, IDType idType, char *str);
void freeDec(Dec d);

Ass makeAss(ID id, ExpTree expTree, int lineNr);
void freeAss(Ass a);

RCall makeRCall(int numids, ID *ids);
void freeRCall(RCall rc);

WCall makeWCall(int numitems, Printable *p, Boolval b);
void freeWCall(WCall wc);

Printable makeStringPrintable(char *string);
Printable makeExpPrintable(ExpTree exp);
void freePrintable(Printable p);

If makeIf(int numGCommands, GCommand *gcs);
void freeIf(If i);

Do makeDo(int numGCommands, GCommand *gcs);
void freeDo(Do d);

GCommand makeGCommand(ExpTree condition, int numStmnts, Stmnt *stmnts);
void freeGCommand(GCommand gc);
#endif //TREE_H