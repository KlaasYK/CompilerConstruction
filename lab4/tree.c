#include <stdlib.h>
#include "symboltable.h"



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