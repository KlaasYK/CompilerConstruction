#include <string.h>
#include "expressiontree.h"
#include "symboltable.h"

ID makeID(int type, char* name) {
	ID id = malloc(sizeof (struct Identifier));
	if(name != NULL){
		int nLength = strlen(name) + 1;
		char *nCopy = malloc(nLength * sizeof (char));
		memcpy(nCopy, name, nLength * sizeof (char));
		id->name = nCopy;
	}
	id->type = type;
	return id;
}

void freeID(ID id) {
	free(id->name);
	free(id);
}

FuncCall makeFuncCall(int type, char* name, int numParams, Exp *params) {
	FuncCall fc = malloc(sizeof (struct FunctionCall));
	fc->id = makeID(type, name);
	fc->numParams = numParams;
	fc->params = params;
	return fc;
}

void freeFuncCall(FuncCall fc) {
	freeID(fc->id);
	for (int i = 0; i < fc->numParams; i++) {
		freeExp(fc->params[i]);
	}
	if(fc->numParams>0){
		free(fc->params);
	}
	free(fc);
}

Int makeInt(char *value) {
	Int i = malloc(sizeof (struct Integer));
	if(value != NULL){
		int vLength = strlen(value) + 1;
		char *vCopy = malloc(vLength * sizeof (char));
		memcpy(vCopy, value, vLength * sizeof (char));
		i->value = vCopy;
	}
	return i;
}

void freeInt(Int i) {
	free(i->value);
	free(i);
}

Bool makeBool(BoolVal bv) {
	Bool b = malloc(sizeof (struct Boolean));
	b->value = bv;
	return b;
}

void freeBool(Bool b) {
	free(b);
}

Exp makeUnNodeExp(Unode un) {
	Exp exp = malloc(sizeof (struct Expression));
	exp->kind = unodeexp;
	exp->node.unode = un;
	return exp;
}

Exp makeBinNodeExp(Bnode bin) {
	Exp exp = malloc(sizeof (struct Expression));
	exp->kind = bnodeexp;
	exp->node.bnode = bin;
	return exp;
}

Exp makeIDNodeExp(ID id) {
	Exp exp = malloc(sizeof (struct Expression));
	exp->kind = idexp;
	exp->node.id = id;
	return exp;
}

Exp makeFuncCallExp(FuncCall fc) {
	Exp exp = malloc(sizeof (struct Expression));
	exp->kind = funcexp;
	exp->node.funcCall = fc;
	return exp;
}

Exp makeIntExp(Int i) {
	Exp exp = malloc(sizeof (struct Expression));
	exp->kind = intexp;
	exp->node.intval = i;
	return exp;
}

Exp makeBoolExp(Bool b) {
	Exp exp = malloc(sizeof (struct Expression));
	exp->kind = boolexp;
	exp->node.boolval = b;
	return exp;
}

void freeExp(Exp exp) {
	switch (exp->kind) {
		case unodeexp:
			freeUnNode(exp->node.unode);
			break;
		case bnodeexp:
			freeBinNode(exp->node.bnode);
			break;
		case idexp:
			freeID(exp->node.id);
			break;
		case funcexp:
			freeFuncCall(exp->node.funcCall);
			break;
		case intexp:
			freeInt(exp->node.intval);
			break;
		case boolexp:
			freeBool(exp->node.boolval);
			break;
		default:
			fprintf(stderr, "Undefined kind of expression!");
			exit(EXIT_FAILURE);
	}
	free(exp);
}

int getExpType(Exp e){
	switch (e->kind) {
		case unodeexp: ;
			int type = getExpType(e->node.unode->e);
			switch(e->node.unode->operator){
				case notop:
					if(type == -1 || (type/10)*10 != BOOLEAN_TYPE){
						return -1;
					}
					return type;
					break;
				case negop:
					if(type == -1 || (type/10)*10 != INTEGER_TYPE){
						return -1;
					}
					return type;
					break;
				default:
					fprintf(stderr, "Undefined kind of unary operator!");
					exit(EXIT_FAILURE);
			}
			break;
		case bnodeexp: ;
			int lType = getExpType(e->node.bnode->l);
			int rType = getExpType(e->node.bnode->r);
			switch(e->node.bnode->operator){
				case plusop:
				case minop:
				case mulop:
				case divop:
				case modop:
				case powop:
					if(lType == -1 || rType == -1 || (lType/10)*10 != INTEGER_TYPE || (rType/10)*10 != INTEGER_TYPE){
						return -1;
					}
					return INTEGER_TYPE;
					break;
				case gtop:
				case ltop:
				case geop:
				case leop:
					if(lType == -1 || rType == -1 || (lType/10)*10 != INTEGER_TYPE || (rType/10)*10 != INTEGER_TYPE){
						return -1;
					}
					return BOOLEAN_TYPE;
					break;
				case andop:
				case orop:
				case candop:
				case corop:
					if(lType == -1 || rType == -1 || (lType/10)*10 != BOOLEAN_TYPE || (rType/10)*10 != BOOLEAN_TYPE){
						return -1;
					}
					return BOOLEAN_TYPE;
					break;
				case neqop:
				case eqop:
					if(lType == -1 || rType == -1 || (lType/10)*10 != (rType/10)*10){
						return -1;
					}
					return BOOLEAN_TYPE;
					break;
				default:
					fprintf(stderr, "Undefined kind of binary operator!");
					exit(EXIT_FAILURE);
			}
			break;
		case idexp:
			return e->node.id->type;
			break;
		case funcexp:
			return e->node.funcCall->id->type;
			break;
		case intexp:
			return INTEGER_TYPE;
			break;
		case boolexp:
			return BOOLEAN_TYPE;
			break;
		default:
			fprintf(stderr, "Undefined kind of expression!");
			exit(EXIT_FAILURE);
		
	}
}

Unode makeUnNode(Exp e, UnOp op) {
	Unode un = malloc(sizeof (struct UnNode));
	un->e = e;
	un->operator = op;
	return un;
}

void freeUnNode(Unode un) {
	freeExp(un->e);
	free(un);
}

Bnode makeBinNode(Exp l, Exp r, BinOp op) {
	Bnode bin = malloc(sizeof (struct BinNode));
	bin->l = l;
	bin->r = r;
	bin->operator = op;
	return bin;
}

void freeBinNode(Bnode bin) {
	freeExp(bin->l);
	freeExp(bin->r);
	free(bin);
}
