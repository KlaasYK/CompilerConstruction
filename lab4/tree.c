#include <stdlib.h>
#include "symboltable.h"
#include "tree.h"
enum Boolval {
    true, false
}

enum UnOp {
    notop, minop
}

enum BinOp {
    plusop, minop, mulop, divop, modop, powop, andop, orop, candop, corop
}

enum ExpKind {
    unodeexp, bnodeexp, idexp, funcexp, intexp, boolexp
}

typedef identifier *ID;

typedef functioncall *FuncCall;

typedef integer *Int;

typedef boolean *Bool;

typedef Expression *Exp;

typedef UnNode *Unode;

typedef BinNode *Bnode;

struct identifier {
    int type;
    char* name;
};

struct functioncall {
    ID id;
    Exp *params;
};

struct integer {
    char* value;
};

struct boolean {
    Boolval value;
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
    Binop operator;
};

ID makeID(int type, char* name){
    ID id = malloc(sizeof(identifier));
    
}


Exp makeUnNodeExp(Unode un){
    Exp exp = malloc(sizeof(expression));
    exp->kind = unodeexp;
    exp->node.unode = un;
}
Exp makeBinNodeExp(Bnode bin){
    Exp exp = malloc(sizeof(expression));
    exp->kind = bnodeexp;
    exp->node.bnode = bin;
}
Exp makeIDNodeExp(Bnode bin){
    Exp exp = malloc(sizeof(expression));
    exp->kind = idexp;
    exp->node.bnode = bin;
}

Bnode makeBinNode(Exp l, Exp r, BinOp op) {
    Bnode bin = malloc(sizeof (BinNode));
    bin->l = l;
    bin->r = r;
    bin->operator = op;
    return bin;
}

Unode makeUnNode(Exp e, UnOp op) {
    Unode un = malloc(sizeof (UnNode));
    un->e = e;
    un->operator = op;
    return un;
}

Exp makeBinNodeExp(Bnode bin)

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
