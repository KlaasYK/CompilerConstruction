#include <stdlib.h>
#include "symboltable.h"

enum UnOp {
    not, min
}

enum BinOp {
    plus, min, mul, div, mod, pow, and, or, cand, cor
}

enum ExpKind {
    unodeexp, bnodeexp, idexp, funcexp, intexp, boolexp
}

typedef struct identifier{
    int type;
    char* name;
};

typedef struct Expression {

    /* Bin node, un node, identifier, func, integer, boolean*/
    union {
	Unode unode;
	Bnode bnode;

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