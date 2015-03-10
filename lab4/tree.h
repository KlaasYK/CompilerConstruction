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