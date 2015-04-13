#ifndef STRUCTARRAYS_H
#define STRUCTARRAYS_H

#include "tree.h"

typedef struct Stmnts{
	int numStmnts;
	Stmnt *stmnts;
}*Stmnts;

typedef struct Decs{
	int numDecs;
	Dec *decs;
}*Decs;

typedef struct IDs{
	int numIds;
	ID *ids;
}*IDs;

typedef struct Exps{
	int numExps;
	ExpTree *exps;
}*Exps;

typedef struct GCmds {
	int numGCmds;
	GCommand *gCmds;
}*GCmds;

typedef struct Params {
	int numParams;
	Param *params;
}*Params;

#endif // STRUCTARRAYS_H