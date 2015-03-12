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

typedefBinNode *Bnode;

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
