#include <string.h>
#include "expressiontree.h"
#include "tree.h"

FuncDef makeFuncDef(ID id, int numParams, ID *params, int numStmnts, Stmnt *stmnts) {
	FuncDef fd = malloc(sizeof (struct FunctionDefinition));
	fd->id = id;
	fd->numParams = numParams;
	fd->params = params;
	fd->numStmnts = numStmnts;
	fd->stmnts = stmnts;
}

void freeFuncDef(FuncDef fd) {
	freeID(fd->id);
	for (int i = 0; i < fd->numParams; i++) {
		freeID(fd->params[i]);
	}
	for (int i = 0; i < fd->numStmnts; i++) {
		freeStmnt(fd->stmnts[i]);
	}
	free(fd);
}

ProcDef makeProcDef(char *name, int numParams, ID *params, int numStmnts, Stmnt *stmnts) {
	ProcDef pd = malloc(sizeof (struct ProcedureDefinition));
	int nLength = strlen(name) + 1;
	char *nCopy = malloc(nLength * sizeof (char));
	memcpy(nCopy, name, nLength * sizeof (char));
	pd->name = nCopy;
	pd->numParams = numParams;
	pd->params = params;
	pd->numStmnts = numStmnts;
	pd->stmnts = stmnts;

}

void freeProcDef(ProcDef pd) {
	free(pd->name);
	for (int i = 0; i < pd->numParams; i++) {
		freeID(pd->params[i]);
	}
	for (int i = 0; i < pd->numStmnts; i++) {
		freeStmnt(pd->stmnts[i]);
	}
	free(pd);
}

Stmnt makeDecStmnt(Dec d) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = decStmnt;
	s->dec = d;
}

Stmnt makeAssStmnt(Ass a) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = assStmnt;
	s->assignment = a;
}

Stmnt makeFuncCallStmnt(FuncCall fc) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = funcCallStmnt;
	s->funcCall = fc;
}

Stmnt makeProcCallStmnt(ProcCall pc) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = procCallStmnt;
	s->procCall = pc;
}

Stmnt makeRCallStmnt(RCall rc) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = readCallStmnt;
	s->rCall = rc;
}

Stmnt makeWCallStmnt(WCall wc) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = writeCallStmnt;
	s->wCall = wc;
}
Stmnt makeIfStmnt(If i){
	Stmnt s = malloc(sizeof(struct Statement));
	s->kind = ifStmnt;
	s->ifStmnt = i;
}
Stmnt makeDoStmnt(Do d){
	Stmnt s = malloc(sizeof(struct Statement));
	s->kind = doStmnt;
	s->doStmnt = d;
}
void freeStmnt(Stmnt s){
	switch(s->kind){
		case decStmnt:
			freeDec(s->dec);
			break;
		case assStmnt:
			freeAss(s->assignment);
			break;
		case funcCallStmnt:
			freeFuncCall(s->funcCall);
			break;
		case procCallStmnt:
			freeProcCall(s->procCall);
			break;
		case readCallStmnt:
			freeRCall(s->rCall);
			break;
		case writeCallStmnt:
			freeWCall(s->wCall);
			break;
		case ifStmnt:
			freeIf(s->ifStmnt);
			break;
		case doStmnt:
			freeDo(s->doStmnt);
			break;
		default:
			fprintf(stderr, "Undefined kind of statement!");
			exit(EXIT_FAILURE);
	}
	free(s);
}

Dec makeDec(ID id, IDType idType, ExpTree expTree){
	Dec d = malloc(sizeof(struct Declaration));
	d->id = id;
	d->idType = idType;
	d->expTree = expTree;
}
void freeDec(Dec d){
	freeID(d->id);
	freeExp(d->expTree);
	free(d);
}

Ass makeAss(ID id, ExpTree expTree){
	Ass a = malloc(sizeof(struct Assignment));
	a->id = id;
	a->expTree = expTree;
}
void freeAss(Ass a){
	freeID(a->id);
	freeExp(a->expTree);
	free(a);
}

RCall makeRCall(ID *ids){
	RCall rc = malloc(sizeof(struct ReadCall));
	rc->ids = ids;
}
void freeRCall(RCall rc);

WCall makeWCall(Printable *p);
void freeWCall(WCall wc);

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