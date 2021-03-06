#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <stdlib.h>
#include <stdio.h>

//enums
typedef enum {
    true, false
} BoolVal;

typedef enum {
    notop, negop
} UnOp;

typedef enum {
    plusop, minop, mulop, divop, modop, powop, andop, orop, candop, corop, neqop, eqop, gtop, ltop, geop, leop
} BinOp;

typedef enum {
    unodeexp, bnodeexp, idexp, funcexp, intexp, boolexp
} ExpKind;

//ref defs
typedef struct Expression *ExpTree;

typedef struct Identifier *ID;

typedef struct FunctionCall *FuncCall;

typedef struct Integer *Int;

typedef struct Boolean *Bool;

typedef struct Expression *Exp;

typedef struct UnNode *Unode;

typedef struct BinNode *Bnode;

//struct defs
struct Identifier {
    int type;
    char* name;
};

struct FunctionCall {
    ID id;
    int numParams;
    Exp *params;
};

struct Integer {
    char* value;
};

struct Boolean {
    BoolVal value;
};

struct Expression {
    ExpKind kind;

    union {
        Unode unode;
        Bnode bnode;
        ID id;
        FuncCall funcCall;
        Int intval;
        Bool boolval;
    } node;
};

struct UnNode {
    Exp e;
    UnOp operator;
};

struct BinNode {
    Exp l, r;
    BinOp operator;
};

// func list
ID makeID(int type, char* name);
void freeID(ID id);

FuncCall makeFuncCall(int type, char* name, int numParams, Exp *params);
void freeFuncCall(FuncCall fc);

Int makeInt(char *value);
void freeInt(Int i);

Bool makeBool(BoolVal bv);
void freeBool(Bool b);

Exp makeUnNodeExp(Unode un);
Exp makeBinNodeExp(Bnode bin);
Exp makeIDNodeExp(ID id);
Exp makeFuncCallExp(FuncCall fc);
Exp makeIntExp(Int i);
Exp makeBoolExp(Bool b);
void freeExp(Exp exp);

int getExpType(Exp e);
ExpTree deepCopyExp(Exp e);

Unode makeUnNode(Exp e, UnOp op);
void freeUnNode(Unode un);

Bnode makeBinNode(Exp l, Exp r, BinOp op);
void freeBinNode(Bnode bin);

#endif // EXPRESSIONTREE_H

