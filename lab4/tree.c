#include <string.h>
#include "expressiontree.h"
#include "tree.h"

Prog makeProg(char *name, int numConstDefs, Dec* constDefs, int numVarDefs, Dec* varDefs, int numProcDefs, ProcDef* procDefs, int numFuncDefs, FuncDef* funcDefs, int numBodyStmnts, Stmnt *bodyStmnts) {
	Prog p = malloc(sizeof (struct Program));
	p->name = NULL;
	if (name != NULL) {
		int nLength = strlen(name) + 1;
		char *nCopy = malloc(nLength * sizeof (char));
		memcpy(nCopy, name, nLength * sizeof (char));
		p->name = nCopy;
	}
	p->numConstDefs = numConstDefs;
	p->constDefs = constDefs;
	p->numVarDefs = numVarDefs;
	p->varDefs = varDefs;
	p->numProcDefs = numProcDefs;
	p->procDefs = procDefs;
	p->numFuncDefs = numFuncDefs;
	p->funcDefs = funcDefs;
	p->numBodyStmnts = numBodyStmnts;
	p->bodyStmnts = bodyStmnts;
	return p;
}

void freeProg(Prog p) {
	if (p != NULL) {
		free(p->name);
		for (int i = 0; i < p->numConstDefs; i++) {
			freeDec(p->constDefs[i]);
		}
		if (p->numConstDefs > 0) {
			free(p->constDefs);
		}
		for (int i = 0; i < p->numVarDefs; i++) {
			freeDec(p->varDefs[i]);
		}
		if (p->numVarDefs > 0) {
			free(p->varDefs);
		}
		for (int i = 0; i < p->numProcDefs; i++) {
			freeProcDef(p->procDefs[i]);
		}
		if (p->numProcDefs > 0) {
			free(p->procDefs);
		}
		for (int i = 0; i < p->numFuncDefs; i++) {
			freeFuncDef(p->funcDefs[i]);
		}
		if (p->numFuncDefs > 0) {
			free(p->funcDefs);
		}
		for (int i = 0; i < p->numBodyStmnts; i++) {
			freeStmnt(p->bodyStmnts[i]);
		}
		if (p->numBodyStmnts > 0) {
			free(p->bodyStmnts);
		}
		free(p);
	}
}

FuncDef makeFuncDef(ID id, int numParams, Param *params, int numStmnts, Stmnt *stmnts) {
	FuncDef fd = malloc(sizeof (struct FunctionDefinition));
	fd->id = id;
	fd->numParams = numParams;
	fd->params = params;
	fd->numStmnts = numStmnts;
	fd->stmnts = stmnts;
	return fd;
}

void freeFuncDef(FuncDef fd) {
	if (fd != NULL) {
		freeID(fd->id);
		for (int i = 0; i < fd->numParams; i++) {
			freeParam(fd->params[i]);
		}
		if (fd->numParams > 0) {
			free(fd->params);
		}
		for (int i = 0; i < fd->numStmnts; i++) {
			freeStmnt(fd->stmnts[i]);
		}
		if (fd->numStmnts > 0) {
			free(fd->stmnts);
		}
		free(fd);
	}
}

ProcDef makeProcDef(char *name, int numParams, Param *params, int numStmnts, Stmnt *stmnts) {
	ProcDef pd = malloc(sizeof (struct ProcedureDefinition));
	pd->name = NULL;
	if (name != NULL) {
		int nLength = strlen(name) + 1;
		char *nCopy = malloc(nLength * sizeof (char));
		memcpy(nCopy, name, nLength * sizeof (char));
		pd->name = nCopy;
	}
	pd->numParams = numParams;
	pd->params = params;
	pd->numStmnts = numStmnts;
	pd->stmnts = stmnts;
	return pd;
}

void freeProcDef(ProcDef pd) {
	if (pd != NULL) {
		free(pd->name);
		for (int i = 0; i < pd->numParams; i++) {
			freeParam(pd->params[i]);
		}
		if (pd->numParams > 0) {
			free(pd->params);
		}
		for (int i = 0; i < pd->numStmnts; i++) {
			freeStmnt(pd->stmnts[i]);
		}
		if (pd->numStmnts > 0) {
			free(pd->stmnts);
		}
		free(pd);
	}
}

Param makeParam(ID id, Call call) {
	Param p = malloc(sizeof (struct Parameter));
	p->id = id;
	p->call = call;
	return p;
}

void freeParam(Param p) {
	if (p != NULL) {
		freeID(p->id);
		free(p);
	}
}

Stmnt makeDecStmnt(Dec d) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = decStmnt;
	s->dec = d;
	return s;
}

Stmnt makeAssStmnt(Ass a) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = assStmnt;
	s->assignment = a;
	return s;
}

Stmnt makeFuncCallStmnt(FuncCall fc) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = funcCallStmnt;
	s->funcCall = fc;
	return s;
}

Stmnt makeRCallStmnt(RCall rc) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = readCallStmnt;
	s->rCall = rc;
	return s;
}

Stmnt makeWCallStmnt(WCall wc) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = writeCallStmnt;
	s->wCall = wc;
	return s;
}

Stmnt makeIfStmnt(If i) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = ifStmnt;
	s->ifStmnt = i;
	return s;
}

Stmnt makeDoStmnt(Do d) {
	Stmnt s = malloc(sizeof (struct Statement));
	s->kind = doStmnt;
	s->doStmnt = d;
	return s;
}

void freeStmnt(Stmnt s) {
	if (s != NULL) {
		switch (s->kind) {
			case decStmnt:
				freeDec(s->dec);
				break;
			case assStmnt:
				freeAss(s->assignment);
				break;
			case funcCallStmnt:
				freeFuncCall(s->funcCall);
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
}

Dec makeExpUninitDec(ID id, IDType idType) {
	Dec d = malloc(sizeof (struct Declaration));
	d->id = id;
	d->idType = idType;
	d->decType = expKind;
	d->isInitialized = false;
	return d;
}

Dec makeExpDec(ID id, IDType idType, ExpTree expTree) {
	Dec d = malloc(sizeof (struct Declaration));
	d->id = id;
	d->idType = idType;
	d->decType = expKind;
	d->isInitialized = true;
	d->expTree = expTree;
	return d;
}

Dec makeStringDec(ID id, IDType idType, char *str) {
	Dec d = malloc(sizeof (struct Declaration));
	d->id = id;
	d->idType = idType;
	d->decType = stringKind;
	d->isInitialized = true;
	d->str = NULL;
	if (str != NULL) {
		int sLength = strlen(str) + 1;
		char *sCopy = malloc(sLength * sizeof (char));
		memcpy(sCopy, str, sLength * sizeof (char));
		d->str = sCopy;
	}
	return d;
}

void freeDec(Dec d) {
	if (d != NULL) {
		freeID(d->id);
		if (d->isInitialized == true) {
			switch (d->decType) {
				case expKind:
					freeExp(d->expTree);
					break;
				case stringKind:
					free(d->str);
					break;
				default:
					fprintf(stderr, "Undefined kind of statement!");
					exit(EXIT_FAILURE);
			}
		}
		free(d);
	}
}

Ass makeAss(ID id, ExpTree expTree, int lineNr) {
	Ass a = malloc(sizeof (struct Assignment));
	a->id = id;
	a->expTree = expTree;
	a->lineNr = lineNr;
	return a;
}

void freeAss(Ass a) {
	if (a != NULL) {
		freeID(a->id);
		freeExp(a->expTree);
		free(a);
	}
}

RCall makeRCall(int numids, ID *ids) {
	RCall rc = malloc(sizeof (struct ReadCall));
	rc->numids = numids;
	rc->ids = ids;
	return rc;
}

void freeRCall(RCall rc) {
	if (rc != NULL) {
		for (int i = 0; i < rc->numids; i++) {
			freeID(rc->ids[i]);
		}
		if (rc->numids > 0) {
			free(rc->ids);
		}
		free(rc);
	}
}

WCall makeWCall(int numitems, Printable *p) {
	WCall wc = malloc(sizeof (struct WriteCall));
	wc->numitems = numitems;
	wc->items = p;
	return wc;
}

void freeWCall(WCall wc) {
	if (wc != NULL) {
		for (int i = 0; i < wc->numitems; i++) {
			freePrintable(wc->items[i]);
		}
		if (wc->numitems > 0) {
			free(wc->items);
		}
		free(wc);
	}
}

Printable makeStringPrintable(char *string) {
	Printable p = malloc(sizeof (struct PrintableItem));
	p->kind = stringKind;
	p->string = NULL;
	if (string != NULL) {
		int sLength = strlen(string) + 1;
		char *sCopy = malloc(sLength * sizeof (char));
		memcpy(sCopy, string, sLength * sizeof (char));
		p->string = sCopy;
	}
	return p;
}

Printable makeExpPrintable(Exp exp) {
	Printable p = malloc(sizeof (struct PrintableItem));
	p->kind = expKind;
	p->exp = exp;
	return p;
}

void freePrintable(Printable p) {
	if (p != NULL) {
		switch (p->kind) {
			case stringKind:
				free(p->string);
				break;
			case expKind:
				freeExp(p->exp);
				break;
			default:
				fprintf(stderr, "Undefined kind of printable!");
				exit(EXIT_FAILURE);
		}
		free(p);
	}
}

If makeIf(int numGCommands, GCommand *gcs) {
	If i = malloc(sizeof (struct IfStatement));
	i->numGCommands = numGCommands;
	i->gCommands = gcs;
	return i;
}

void freeIf(If i) {
	if (i != NULL) {
		for (int j = 0; j < i->numGCommands; j++) {
			freeGCommand(i->gCommands[j]);
		}
		if (i->numGCommands > 0) {
			free(i->gCommands);
		}
		free(i);
	}
}

Do makeDo(int numGCommands, GCommand *gcs) {
	Do d = malloc(sizeof (struct DoStatement));
	d->numGCommands = numGCommands;
	d->gCommands = gcs;
	return d;
}

void freeDo(Do d) {
	if (d != NULL) {
		for (int i = 0; i < d->numGCommands; i++) {
			freeGCommand(d->gCommands[i]);
		}
		if (d->numGCommands > 0) {
			free(d->gCommands);
		}
		free(d);
	}
}

GCommand makeGCommand(Exp condition, int numStmnts, Stmnt *stmnts) {
	GCommand gc = malloc(sizeof (struct GuardedCommand));
	gc->condition = condition;
	gc->numStmnts = numStmnts;
	gc->stmnts = stmnts;
	return gc;
}

void freeGCommand(GCommand gc) {
	if (gc != NULL) {
		freeExp(gc->condition);
		for (int i = 0; i < gc->numStmnts; i++) {
			freeStmnt(gc->stmnts[i]);
		}
		if (gc->numStmnts > 0) {
			free(gc->stmnts);
		}
		free(gc);
	}
}