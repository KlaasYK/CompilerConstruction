%start parser, start;
%token BEGIN_TOK, END_TOK, PROGRAM_TOK, DOBEGIN_TOK, DOEND_TOK, IFBEGIN_TOK, IFEND_TOK, FUNCTION_TOK, PRINT_TOK, READ_TOK, OR_OP, AND_OP, CAND_OP, COR_OP, ASSIGNMENT_OP, PLUS_OP, MIN_OP, MUL_OP, POW_OP, COMPARE_OP, TYPE_OP, VAR_TOK, NUMBER,STRING, BOOLEAN, THEN_TOK, CONSTANT_TOK, COMMA, SEMICOLON, ALTGUARD, IDENTIFIER, NOT_TOK, TYPE, DOT, LPARREN, RPARREN, PROCEDURE_TOK;
%options "generate-symbol-table generate-lexer-wrapper";
%lexical yylex;

{
/* BEGIN C FILE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"

#include "tree.h"

/* different typechecking errors */
#define DUPLICATE 256
#define WRONGTYPE 257

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

extern FILE * yyin;
extern char * yytext;

char **lines;
char *file_name;
int linesread;

/* to keep track of errors */
int columnnr;
int linecount;

/* the program name */
char *programname;

/* the parse tree */
Prog program;

/* temporary storage for identifier names when declaring more  */
char *lastidentifier;

typedef struct TempINode {
	char *name;
	struct TempINode *next;
} INode;

INode *tempidentifierlist;

void freeTempList() {
	INode *n = tempidentifierlist;
	tempidentifierlist = NULL;
	while (n != NULL) {
		INode *next = n->next;
		free(n->name);
		free(n);
		n = next;
	}
}

/* adds an identifier to the temp list */
void addTempList(char *name) {
	INode *new = malloc(sizeof(struct TempINode));
	new->name = name;
	new->next = tempidentifierlist;
	tempidentifierlist = new;
}



void readFile(char *filename) {
	FILE * fin = fopen(filename, "r");
	linesread = 0;
	size_t len = 0;
	ssize_t read = 0;
	/* TODO: remove hardcoded limit */
	lines = calloc(1000, sizeof(char*)); /* calloc, prevents unconditional jumps */
	int guard = getline( &(lines[linesread]), &len, fin);
	while ( guard != -1 ) {
		linesread++;
		guard = getline( &(lines[linesread]), &len, fin);
	}
	linesread++;
	fclose(fin);
}

void freeLines() {
	int i;
	for (i=0; i < linesread; ++i) {
		free(lines[i]);
	}
	free(lines);
	if (yyin != NULL) {
		fclose(yyin);
		yyin = NULL;
	}
	/* flex buffers */
	yylex_destroy();
}

/* debug function used for cleaning up temporary variables */
void utilCleanUp() {
	if (programname != NULL) {
		free(programname);
	}
	if (tempidentifierlist != NULL) {
		freeTempList();
	}
}


void printLexError(char *illchar, int line, int column) {
	int i = 0, k;
	printf("\n");
	k = printf("Error on line %d: ", line+1);
	printf("%s", lines[line]);
	for (i; i < column + k; i++) {
		printf(" ");
	}
	printf("^\n");
	printf("Illegal character (%s) detected at column %d\n", illchar, column+1);
	utilCleanUp();
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);
}

void LLmessage(int token) {
	int i = 0, k, c;
	printf("\n");
	k = printf("Error on line %d: ", linecount+1);
	c = columnnr - strlen(yytext);
	printf("%s", lines[linecount]);
	for (i; i < c + k; i++) {
		printf(" ");
	}
	printf("^\n");
	switch (token) {
		case LL_MISSINGEOF:
		printf("Expected %s, found %s (%s).\n", LLgetSymbol(EOFILE), LLgetSymbol(LLsymb), yytext);
		break;
		case LL_DELETE:
		printf("Unexpected %s (%s).\n", LLgetSymbol(LLsymb), yytext);
		break;
		default:
		printf("Expected %s, found %s (%s).\n", LLgetSymbol(token), LLgetSymbol(LLsymb), yytext);
		break;
	}
	utilCleanUp();
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);
}


void printTypeError(char *identifier, int ErrorType) {
	int i = 0, k;
	printf("\n");
	k = printf("Error on line %d: ", linecount+1);
	printf("%s", lines[linecount]);
	for (i; i < columnnr + k; i++) {
		printf(" ");
	}
	printf("^\n");
	switch (ErrorType) {
		case DUPLICATE: printf("Duplicate identifier (%s) detected at column %d\n", identifier, columnnr+1);
	}
	
	free(identifier);
	
	utilCleanUp();
	
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	// initialise global vars to NULL/0
	linecount = 0, columnnr = 0;
	
	programname = NULL;
	tempidentifierlist = NULL;
	
	printf("Extended Guarded Command Language Compiler.\n");
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [filename.c]\n", argv[0]);
		exit(-1);
  	}
	if (argc == 2) {
		file_name = argv[1];
		printf("Compiling file: %s\n",file_name);
		readFile(argv[1]);
		yyin = fopen(argv[1], "r");
	}
	
	initSymbolTable();
	
	parser();
	
	/* test region for symbol table */	
	printf("\nSymbolTable:\n");
	printSymbolTable();
	printf("\n");
	

	
	/* end test region for symbol table */

	if (argc == 2) {
		fclose(yyin);
		yyin = NULL;
	}

	printf("Parsing succesfull\n");
	
	utilCleanUp();
	freeSymbolTable();
	freeLines();
	
	return EXIT_SUCCESS;
}

/* EOF c FILE */
}

rootexpr	: 
				LPARREN 
				expr 
				RPARREN
			| 
				IDENTIFIER 
				functioncall?
			| 
				NUMBER
			;


powbase	: 
			MIN_OP 
			powbase
		| 
			rootexpr
		;

factor2	: 
			POW_OP 
			powbase 
			factor2
		| 
			/* epsilon */
		;

factor	: 
			powbase 
			factor2 
		;

term2	: 
			MUL_OP 
			factor 
			term2
		| 
			/* epsilon */
		;

term	: 
			factor 
			term2
		;

sumexpr2	: 
				PLUS_OP 
				term 
				sumexpr2
			| 
				MIN_OP 
				term 
				sumexpr2
			| 
				/* epsilon */
			;

sumexpr	: 
			term 
			sumexpr2
		;

relexpr2	: 
				COMPARE_OP sumexpr relexpr2
			| 
				/* epsilon */
			;

relexpr : 
			sumexpr 
			relexpr2
		| 
			BOOLEAN
		;

notexpr	: 
			NOT_TOK 
			notexpr
		| 
			relexpr
		;

andexpr2	: 
				AND_OP 
				notexpr 
				andexpr2
			| 
				CAND_OP 
				notexpr 
				andexpr2
			| 
				/* epsilon */
			;

andexpr	: 
			notexpr 
			andexpr2 
		;
			
expr2	: 
			OR_OP 
			andexpr 
			expr2
		| 
			COR_OP 
			andexpr 
			expr2
		| 
			/* epsilon */
		;

expr	: 
			andexpr 
			expr2
		;

guardedcommand	: 
		expr 
		THEN_TOK 
		statementset<LLdiscard>
;

guardedcommandset	: 
						guardedcommand 
						[
							ALTGUARD 
							guardedcommand
						]*
					;

identifierarray<IDs>(IDs idents)	: 
		IDENTIFIER {
			addTempList(strdup(yytext));
			ID id = makeID(0, yytext);
			idents = malloc(sizeof(struct IDs));
			idents->numIds = 1;
			idents->ids = malloc(sizeof(ID));
			idents->ids[0] = id;
		} 
		[
			COMMA 
			identifierarray<ids>(NULL){
				int oldNumIds = idents->numIds;
				idents->numIds += ids->numIds;
				idents->ids = realloc(idents->ids, idents->numIds*sizeof(ID));
				for(int i = 0; i + oldNumIds < idents->numIds; i++){
					idents->ids[i + oldNumIds] = ids->ids[i];
				}
				free(ids->ids);
				free(ids);
			}
		]?{
			LLretval = idents;
		}
;

functioncall	: 
					LPARREN 
					identifierarray(NULL)/* TODO check validity: can't calls contain expressions? */
					RPARREN
				;

/* original version of assignmentcall that has an equal length for the identifiers and the following expressions (could make semantics very hard to handle) */
assignmentcallV1	: 
						ASSIGNMENT_OP 
						expr
					| 
						COMMA 
						IDENTIFIER 
						assignmentcall 
						COMMA 
						expr
					;

/* newer version of assignmentcall that doesn't make sure yet that the amount of identifers equals the amount of expressions (semantically easier to evaluate) */
assignmentcallV2	: 
						[
							COMMA 
							IDENTIFIER
						]* 
						ASSIGNMENT_OP 
						expr 
						[
							COMMA 
							expr
						]*
					;

/* select assignmentcall V1 or V2 */
assignmentcall	: 
					assignmentcallV2
				;

dostatement	:	
				DOBEGIN_TOK 
				guardedcommandset
				DOEND_TOK
			;

ifstatement	:	
				IFBEGIN_TOK 
				guardedcommandset 
				IFEND_TOK
			;

printable<Printable> : 
		STRING{
			Printable p = makeStringPrintable(yytext);
			LLretval = p;
		}
	| 
		expr{
			Printable p = NULL;
			LLretval = p;
		}
;

printcall<WCall>(int numitems, Printable *ps) : 
		PRINT_TOK 
		printable<p>{
			numitems = 1;
			ps = malloc(sizeof(Printable));
			ps[0] = p;
		}
		[
			COMMA 
			printable<p>{
				numitems++;
				ps = realloc(ps, numitems*sizeof(Printable));
				ps[numitems-1] = p;
			}
		]*{
			WCall wc = makeWCall(numitems, ps);
			LLretval = wc;
		}
;

readcall	: 
				READ_TOK 
				IDENTIFIER 
				[
					COMMA 
					IDENTIFIER
				]*
			;

call	:	
			functioncall
		|	
			assignmentcall
		;

declaration<Decs>(IDs idents): 
				VAR_TOK 
				identifierarray<ids>(NULL){
					idents = ids;
				}
				TYPE_OP 
				TYPE {
					int type = stringToEvalType(yytext);
					/* TREE */
					for(int i = 0; i < idents->numIds; i++){
						idents->ids[i]->type = type;
					}
					Decs d  = malloc(idents->numIds*sizeof(struct Decs));
					d->numDecs = idents->numIds;
					d->decs = malloc(d->numDecs*sizeof(Dec));
					for(int i=0; i < d->numDecs; i++){
						d->decs[i] = makeExpUninitDec(idents->ids[i], variable);
					}
					free(idents->ids);
					free(idents);
					LLretval = d;
					
					/* SYMBOL TABLE */
					INode *n = tempidentifierlist;
					while (n != NULL) {
						/* check if the  identifier exists already */
						if ( !existsInTop(n->name) ) {
							insertIdentifier(strdup(n->name), VARIABLE, stringToEvalType(yytext), NULL);
						} else {
							printTypeError(n->name, DUPLICATE);
						}
						n = n->next;
					}
					freeTempList();
				}
			;

statement<Stmnts>(Stmnts ss) : 
[
		declaration<ds>(NULL){
			/*TODO placeholder*/
			ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = ds->numDecs;
			ss->stmnts = malloc(ss->numStmnts*sizeof(Stmnt));
			for(int i = 0;i < ss->numStmnts; i++){
				ss->stmnts[i] = makeDecStmnt(ds->decs[i]);
			}
			free(ds->decs);
			free(ds);
		}
	| 
		IDENTIFIER 
		call
	| 
		printcall<wc>(0, NULL){
			ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 1;
			ss->stmnts = malloc(ss->numStmnts*sizeof(Stmnt));
			ss->stmnts[0] = makeWCallStmnt(wc);
		}
	| 
		readcall
	| 
		dostatement
	|
		ifstatement
]{
	LLretval = ss;
}
;

parameterset 	: 
					identifierarray(NULL) 
					TYPE_OP 
					TYPE
				;

variable<Dec>(ExpTree exp) : 
	[
			BOOLEAN{
				char *bool = strdup(yytext);
				BoolVal bv;
				if(strcmp(bool, "true") == 0){
					bv = true;
				}else if(strcmp(bool, "false") == 0){
					bv = false;
				}
				free(bool);
				exp = makeBoolExp(makeBool(bv));
			}
		| 
			NUMBER{
				exp = makeIntExp(makeInt(yytext));
			}
	]{
		LLretval = makeExpDec(NULL, variable, exp);
	}
	| 
		STRING{
			LLretval = makeStringDec(NULL, variable, yytext);
		}

;
			
/* can the last statement in a block end with a semicolon? internet says of a certain version of gcl that a statement has the rule: S -> S;S | ...*/
statementset2<Stmnts> : 
		SEMICOLON 
		statementset<ss>{
			LLretval = ss;
		}
	| 
		/* epsilon */{
			Stmnts ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 0;
			ss->stmnts = NULL;
			LLretval = ss;
		}
;

statementsetV1<Stmnts>(Stmnts stmnts) : 
		statement<ss>(NULL){
			stmnts = ss;
		}
		statementset2<ss>{
			int oldNumStmnts = stmnts->numStmnts;
			stmnts->numStmnts += ss->numStmnts;
			Stmnt *sarr = stmnts->stmnts;
			stmnts->stmnts = realloc(stmnts->stmnts, stmnts->numStmnts*sizeof(Stmnt));
			for(int i = 0; i + oldNumStmnts < stmnts->numStmnts; i++){
				stmnts->stmnts[i + oldNumStmnts] = ss->stmnts[i];
			}
			free(ss->stmnts);
			free(ss);
			LLretval = stmnts;
		}
	| 
		/* epsilon */{
			Stmnts ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 0;
			ss->stmnts = NULL;
			LLretval = ss;
		}
;

/* alternative where every line needs to end with a semicolon */
statementsetV2	: statement<LLdiscard>(NULL)
		SEMICOLON 
		statementset
	| 
		/* epsilon */
;

/* select statementset V1 or V2 */
statementset<Stmnts>: 
		statementsetV1<ss>(NULL){
			LLretval = ss;
		}
;

function	: 
				FUNCTION_TOK 
				IDENTIFIER 
				LPARREN 
				parameterset? 
				RPARREN 
				THEN_TOK TYPE 
				SEMICOLON 
				statementset<LLdiscard>
				END_TOK 
				SEMICOLON
			;

procedure	: 
				PROCEDURE_TOK 
				IDENTIFIER 
				LPARREN 
				VAR_TOK 
				parameterset? 
				RPARREN 
				SEMICOLON 
				statementset<LLdiscard>
				END_TOK 
				SEMICOLON
			;

constantdef<Dec>(int type, char *name, Dec dec)	: 
		CONSTANT_TOK
		IDENTIFIER{
			name = strdup(yytext);
			/* SYMBOL TABLE */
			addTempList(strdup(yytext));
		}
		TYPE_OP 
		TYPE{
			type = stringToEvalType(yytext);
		}
		COMPARE_OP 
		variable<d>(NULL){
			dec = d;
		}
		SEMICOLON{
			d->id = makeID(type, name);
			d->idType = constant;
			free(name);
			LLretval = d;
		}
;

/* first procuders then functions? */
programbody<Prog>(int numConstDefs, Dec *constDefs, int numVarDefs, Dec *varDefs, int numProcDefs, ProcDef *procDefs, int numFuncDefs, FuncDef *funcDefs, int numBodyStmnts, Stmnt *bodyStmnts)	: 
		[
			constantdef<cd>(0, NULL, NULL){
				numConstDefs++;
				if(numConstDefs == 1){
					constDefs = malloc(numConstDefs*sizeof(Dec));
				}else{
					constDefs = realloc(constDefs, numConstDefs*sizeof(Dec));
				}
				constDefs[numConstDefs-1] = cd;
			}
		]*{
			printf("Num of const defs: %d\n", numConstDefs);
		}
		[
			declaration<vds>(NULL)
			SEMICOLON{
				int oldNumVarDefs = numVarDefs;
				numVarDefs += vds->numDecs;
				if(oldNumVarDefs == 0){
					varDefs = malloc(numVarDefs*sizeof(Dec));
				}else{
					varDefs = realloc(varDefs, numVarDefs*sizeof(Dec));
				}
				for(int i = 0; i + oldNumVarDefs < numVarDefs; i++){
					varDefs[i + oldNumVarDefs] = vds->decs[i];
				}
				free(vds->decs);
				free(vds);
			}
		]* {
			printf("Num of var defs: %d\n", numVarDefs);
		}
		procedure* 
		function* 
		BEGIN_TOK {
			putBlock(); /* add a new frame of reference */
		} 
		statementset<bss>{
			numBodyStmnts = bss->numStmnts;
			printf("Num of bodystmnts: %d\n", bss->numStmnts);
			bodyStmnts = bss->stmnts;
			free(bss);
		}
		END_TOK {
			/* popBlock(); TODO: activate this after debugging */
			LLretval = makeProg(programname, numConstDefs, constDefs, numVarDefs, varDefs, numProcDefs, procDefs, numFuncDefs, funcDefs, numBodyStmnts, bodyStmnts);
		}
;
			
header		: 
		PROGRAM_TOK
		IDENTIFIER {
			programname = strdup(yytext); /* the token is freed in freeNode (normally) */
		} 
		SEMICOLON 
;

start		: 
		header 
		programbody<prog>(0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL){
			program  = prog;
		}
		DOT{
			printf("Program name: %s\n", program->name);
			if(strcmp(file_name, "riktest.gcl") == 0){
				printf("Print string: %s\n", program->bodyStmnts[0]->wCall->items[0]->string);
				printf("boolval: %s\n", (program->constDefs[0]->expTree->node.boolval->value == true)?"true":"false");
				printf("intval: %s\n", program->constDefs[1]->expTree->node.intval->value);
				
				
			}
			freeProg(program);
		}
; 
