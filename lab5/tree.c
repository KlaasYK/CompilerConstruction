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
		p->name = NULL;
		for (int i = 0; i < p->numConstDefs; i++) {
			freeDec(p->constDefs[i]);
			p->constDefs[i] = NULL;
		}
		if (p->numConstDefs > 0) {
			free(p->constDefs);
			p->constDefs = NULL;
		}
		for (int i = 0; i < p->numVarDefs; i++) {
			freeDec(p->varDefs[i]);
			p->varDefs[i] = NULL;
		}
		if (p->numVarDefs > 0) {
			free(p->varDefs);
			p->varDefs = NULL;
		}
		for (int i = 0; i < p->numProcDefs; i++) {
			freeProcDef(p->procDefs[i]);
			p->procDefs[i] = NULL;
		}
		if (p->numProcDefs > 0) {
			free(p->procDefs);
			p->procDefs = NULL;
		}
		for (int i = 0; i < p->numFuncDefs; i++) {
			freeFuncDef(p->funcDefs[i]);
			p->funcDefs[i] = NULL;
		}
		if (p->numFuncDefs > 0) {
			free(p->funcDefs);
			p->funcDefs = NULL;
		}
		for (int i = 0; i < p->numBodyStmnts; i++) {
			freeStmnt(p->bodyStmnts[i]);
			p->bodyStmnts[i] = NULL;
		}
		if (p->numBodyStmnts > 0) {
			free(p->bodyStmnts);
			p->bodyStmnts = NULL;
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
		fd->id = NULL;
		for (int i = 0; i < fd->numParams; i++) {
			freeParam(fd->params[i]);
			fd->params[i] = NULL;
		}
		if (fd->numParams > 0) {
			free(fd->params);
			fd->params = NULL;
		}
		for (int i = 0; i < fd->numStmnts; i++) {
			freeStmnt(fd->stmnts[i]);
			fd->stmnts[i] = NULL;
		}
		if (fd->numStmnts > 0) {
			free(fd->stmnts);
			fd->stmnts = NULL;
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
		pd->name = NULL;
		for (int i = 0; i < pd->numParams; i++) {
			freeParam(pd->params[i]);
			pd->params[i] = NULL;
		}
		if (pd->numParams > 0) {
			free(pd->params);
			pd->params = NULL;
		}
		for (int i = 0; i < pd->numStmnts; i++) {
			freeStmnt(pd->stmnts[i]);
			pd->stmnts[i] = NULL;
		}
		if (pd->numStmnts > 0) {
			free(pd->stmnts);
			pd->stmnts = NULL;
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
		p->id = NULL;
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
				s->dec = NULL;
				break;
			case assStmnt:
				freeAss(s->assignment);
				s->assignment = NULL;
				break;
			case funcCallStmnt:
				freeFuncCall(s->funcCall);
				s->funcCall = NULL;
				break;
			case readCallStmnt:
				freeRCall(s->rCall);
				s->rCall = NULL;
				break;
			case writeCallStmnt:
				freeWCall(s->wCall);
				s->wCall = NULL;
				break;
			case ifStmnt:
				freeIf(s->ifStmnt);
				s->ifStmnt = NULL;
				break;
			case doStmnt:
				freeDo(s->doStmnt);
				s->doStmnt = NULL;
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
		d->id = NULL;
		if (d->isInitialized == true) {
			switch (d->decType) {
				case expKind:
					freeExp(d->expTree);
					d->expTree = NULL;
					break;
				case stringKind:
					free(d->str);
					d->str = NULL;
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
		a->id = NULL;
		freeExp(a->expTree);;
		a->expTree = NULL;
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
			rc->ids[i] = NULL;
		}
		if (rc->numids > 0) {
			free(rc->ids);
			rc->ids = NULL;
		}
		free(rc);
	}
}

WCall makeWCall(int numitems, Printable *p, BoolVal b) {
	WCall wc = malloc(sizeof (struct WriteCall));
	wc->numitems = numitems;
	wc->items = p;
	wc->newLine = b;
	return wc;
}

void freeWCall(WCall wc) {
	if (wc != NULL) {
		for (int i = 0; i < wc->numitems; i++) {
			freePrintable(wc->items[i]);
			wc->items[i] = NULL;
		}
		if (wc->numitems > 0) {
			free(wc->items);
			wc->items = NULL;
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
				p->string = NULL;
				break;
			case expKind:
				freeExp(p->exp);
				p->exp = NULL;
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
			i->gCommands[j] = NULL;
		}
		if (i->numGCommands > 0) {
			free(i->gCommands);
			i->gCommands = NULL;
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
			d->gCommands[i] = NULL;
		}
		if (d->numGCommands > 0) {
			free(d->gCommands);
			d->gCommands = NULL;
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
		gc->condition = NULL;
		for (int i = 0; i < gc->numStmnts; i++) {
			freeStmnt(gc->stmnts[i]);
			gc->stmnts[i] = NULL;
		}
		if (gc->numStmnts > 0) {
			free(gc->stmnts);
			gc->stmnts = NULL;
		}
		free(gc);
	}
}