#include <stdlib.h>
#include "symboltable.h"

enum Boolval {
    true, false
}

enum UnOp {
    not, min
}

enum BinOp {
    plus, min, mul, div, mod, pow, and, or, cand, cor
}

enum ExpKind {
    unodeexp, bnodeexp, idexp, funcexp, intexp, boolexp
}

typedef struct identifier {
    int type;
    char* name;
} *ID;

typedef struct functioncall {
    ID id;
    Exp *params;
} *FuncCall;

typedef struct integer {
    int value;
} *Int;

typedef struct boolean {
    Boolval value;
} *Bool;

typedef struct Expression {
    ExpKind kind;

    union {
	Unode unode;
	Bnode bnode;
	ID id;
	FuncCall funcCall;
	Int intval;
	Bool boolval;
    };
} *Exp;

typedef struct UnNode {
    Exp e;
    UnOp operator;
} *Unode;

typedef struct BinNode {
    Exp l, r;
    Binop operator;
} *Bnode;

Bnode makeBinNode(Exp l, Exp r, BinOp op) {
    Bnode bin = malloc(sizeof (Bnode));
    bin->l = l;
    bin->r = r;
    bin->operator = op;
    return bin;
}

Unode makeUnNode(Exp e, UnOp op) {
    Unode un = malloc(sizeof (Unode));
    un->e = e;
    un->operator = op;
    return un;
}

void freeExp(Exp e);

void freeBinNode(Bnode bin) {
    freeExp(bin->l);
    freeExp(bin->r);
    free(bin);
}

void freeUnNode(Unode un) {
    freeExp(un->e);
    free(un);
}