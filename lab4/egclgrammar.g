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
#define UNKNOWN 258
#define WRITETOCONSTANT 259
#define	METHODASKED 260
#define PARAMMISMATCH1 261
#define PARAMMISMATCH2 262
#define REFERENCETOCONSTANT 263
#define PROCISOFUNC 264	
#define ASSMISMATCH 265
#define	VARIABLEASKED 266
#define RETURNINPROC 267
#define MISSINGRETURN 268

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

extern FILE * yyin;
extern char * yytext;
extern char * lexeme;

char **lines;
char *file_name;
int linesread;

int error;

/* to keep track of errors */
int columnnr;
int linecount;

/* the program name */
char *programname;

/* the parse tree */
Prog program;

/* temporary storage for identifier names when declaring more  */
char *lastmethodidentifier;

typedef struct TempINode {
	char *name;
	struct TempINode *next;
} INode;

INode *tempidentifierlist;
Node *tempparamlist;

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
int lastconstanttype;

/* adds an identifier to the temp list */
void addTempList(char *name) {
	INode *new = malloc(sizeof(struct TempINode));
	new->name = name;
	new->next = tempidentifierlist;
	tempidentifierlist = new;
}

void freeTempParamList() {
	Node *n = tempparamlist;
	tempparamlist = NULL;
	while (n != NULL) {
		Node *next = n->next;
		freeNode(n);
		n = next;
	}
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
		programname = NULL;
	}
	if (tempidentifierlist != NULL) {
		freeTempList();
	}
	if (lexeme != NULL) {
		free(lexeme);
		lexeme = NULL;
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
	/*utilCleanUp();
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);*/
	error = 1;
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
	/*utilCleanUp();
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);*/
	error = 1;
}


void printTypeError(char *identifier, int ErrorType) {
	int i = 0, k;
	
	/* print symbol table for debug reasons */
	printf("\nSymboltable:\n");
	printSymbolTable();
	
	printf("\n");
	k = printf("Error on line %d: ", linecount+1);
	printf("%s", lines[linecount]);
	for (i; i < columnnr + k; i++) {
		printf(" ");
	}
	printf("^\n");
	switch (ErrorType) {
		case DUPLICATE: printf("Duplicate identifier (%s), at column %d\n", identifier, columnnr+1); break;
		case WRONGTYPE: printf("Value of '%s' is of the wrong type, at column %d\n", identifier, columnnr+1); break;//TODO: print more info
		case UNKNOWN: printf("Unknown identifier (%s), at column %d\n", identifier, columnnr+1); break;
		case WRITETOCONSTANT: printf("Trying to write to '%s' which is a constant, at column %d\n", identifier, columnnr+1); break;//TODO: print more info
		case METHODASKED: printf("Variable '%s' found in stead of function, at column %d\n", identifier, columnnr+1);break;
		case PARAMMISMATCH1: printf("The number of parameters for function '%s' differs from what was previously defined\n", identifier);break;
		case PARAMMISMATCH2: printf("One of the parameters for function '%s' has a type mismatch\n", identifier);break;
		case REFERENCETOCONSTANT: printf("In function '%s' a constant was used as reference parameter\n", identifier);break;
		case PROCISOFUNC: printf("Procedure '%s' is used as function, at column %d\n", identifier, columnnr+1);break;
		case ASSMISMATCH: printf("The number of variables is unequal to the number of assigned expressions\n");break;
		case VARIABLEASKED: printf("Function or procedure '%s' found in stead of variable, at column %d\n", identifier, columnnr+1);break;
		case RETURNINPROC: printf("Trying to return a value to a procedure '%s', at column %d\n", identifier, columnnr+1);break;
		case MISSINGRETURN: printf("Function '%s' has nothing assigned to its return variable, at column %d\n", identifier, columnnr+1);break;
	}
	
	free(identifier);
	
	/*utilCleanUp();
	
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);*/
	error = 1;
}

int getType(char *name) {
	NodeType nt = lookupType(name);
	int type = lookupEvalType(name, nt);
	if(type == -1){
		// trying to save something that was not declared
		printTypeError(name, UNKNOWN);
	}else if (type == CONST_BOOLEAN_TYPE || type == CONST_INTEGER_TYPE) {
		printTypeError(name, WRITETOCONSTANT);
	}else {
		free(name);
	}
	return type;
}

/* constants may be used! */
int getTypeConst(char *name) {
	NodeType nt = lookupType(name);
	int type = lookupEvalType(name, nt);
	if(type == -1){
		// trying to save something that was not declared
		printTypeError(name, UNKNOWN);
	}else{
		free(name);
	}
	return type;
}

int main(int argc, char** argv) {
	// initialise global vars to NULL/0
	linecount = 0, columnnr = 0;
	error = 0;
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
	if (error) {
		printf("Parser failed!\n");
	} else {
		printf("Parsing succesfull\n");
	}
	
	utilCleanUp();
	freeProg(program);
	freeSymbolTable();
	freeLines();
	
	return EXIT_SUCCESS;
}

/* EOF c FILE */
}

rootexpr<Exp>(char *name, int isFunc)	: 
				LPARREN 
				expr<e>(NULL){
					LLretval = e;
				}
				RPARREN
			| 
				IDENTIFIER{
					name = strdup(yytext);
					isFunc = 0;
				}
				[
					functioncall<fc>(name, 0, NULL){
						isFunc = 1;
						if(lookupEvalType(name, lookupType(name))== VOID_TYPE){
							printTypeError(strdup(name), PROCISOFUNC);
						}
						LLretval = makeFuncCallExp(fc);
					}
				]?{
					if(!isFunc){
						LLretval = makeIDNodeExp(makeID(getTypeConst(strdup(name)), name));
					}
					free(name);
				}
			| 
				NUMBER{
					LLretval = makeIntExp(makeInt(yytext));
				}
			|
				BOOLEAN{
					char *bool = strdup(yytext);
					LLretval = makeBoolExp(makeBool(strcmp(bool, "true")==0?true:false));
					free(bool);
				}
			;


powbase<Exp> : 
			MIN_OP 
			powbase<e>{
				if((getExpType(e)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
				LLretval = makeUnNodeExp(makeUnNode(e, negop));
			}
		| 
			rootexpr<e>(NULL,0){
			LLretval = e;
		}
		;

factor2<Exp> : 
		POW_OP 
		powbase<l>
		factor2<e>{
			if(e == NULL){
				LLretval = makeBinNodeExp(makeBinNode(NULL, l, powop));
			}else{
				e->node.bnode->l = l;
				if((getExpType(l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
				LLretval = makeBinNodeExp(makeBinNode(NULL, e, powop));
			}
		}
	| 
		/* epsilon */{
			LLretval = NULL;
		}
;

factor<Exp>: 
		powbase<l>
		factor2<e>{
			if(e == NULL){
				LLretval = l;
			}else{
				e->node.bnode->l = l;
				if((getExpType(l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
				LLretval = e;
			}
		} 
;

term2<Exp>(Exp left, Exp *exp, BinOp mulOp)	: 
		MUL_OP {
			char *mulOpText = strdup(yytext);
			if(strcmp(mulOpText, "*") == 0){
				mulOp = mulop;
			}
			else if(strcmp(mulOpText, "/") == 0){
				mulOp = divop;
			}
			else if(strcmp(mulOpText, "div") == 0){
				mulOp = divop;
			}
			else if(strcmp(mulOpText, "%") == 0){
				mulOp = modop;
			}
			else if(strcmp(mulOpText, "mod") == 0){
				mulOp = modop;
			}
			free(mulOpText);
		}
		factor<r>{
			LLretval = makeBinNodeExp(makeBinNode(left, r, mulOp));
		}
		term2<e>(LLretval, exp, 0){
			if(e != NULL){
				if((getExpType(e->node.bnode->l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		/* epsilon */{
			LLretval = NULL;
		}
;

term<Exp>(Exp *exp) : 
{
	exp = malloc(sizeof(Exp));
}
		factor<l>
		term2<e>(l, exp, 0){
			if(e == NULL){
				LLretval = l;
			}else{
				if((getExpType(l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
				LLretval = *exp;
			}
			free(exp);
		}
;

sumexpr2<Exp>(Exp left, Exp *exp) : 
		PLUS_OP
		term<r>(NULL){
			LLretval = makeBinNodeExp(makeBinNode(left, r, plusop));	
		}
		sumexpr2<e>(LLretval, exp){
			if(e != NULL){
				if((getExpType(e->node.bnode->l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		MIN_OP 
		term<r>(NULL){
			LLretval = makeBinNodeExp(makeBinNode(left, r, minop));
		}
		sumexpr2<e>(LLretval, exp){
			if(e != NULL){
				if((getExpType(e->node.bnode->l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		/* epsilon */{
			LLretval = NULL;
		}
;

sumexpr<Exp>(Exp *exp) : 
{
	exp = malloc(sizeof(Exp));
}
		term<l>(NULL)
		sumexpr2<e>(l, exp){
			if(e == NULL){
				LLretval = l;
			}else{
				e->node.bnode->l = l;
				if((getExpType(l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
				LLretval = *exp;
			}
			free(exp);
		}
;

relexpr2<Exp>(Exp left, Exp *exp, BinOp compOp)	: 
		COMPARE_OP{
			char *compOpText = strdup(yytext);
			if(strcmp(compOpText, "<>") == 0){
				compOp = neqop;
			}
			else if(strcmp(compOpText, "=") == 0){
				compOp = eqop;
			}
			else if(strcmp(compOpText, ">") == 0){
				compOp = gtop;
			}
			else if(strcmp(compOpText, ">=") == 0){
				compOp = geop;
			}
			else if(strcmp(compOpText, "<") == 0){
				compOp = ltop;
			}
			else if(strcmp(compOpText, "<=") == 0){
				compOp = leop;
			}
			free(compOpText);
		}
		sumexpr<r>(NULL){
			LLretval = makeBinNodeExp(makeBinNode(left, r, compOp));
		}
		relexpr2<e>(LLretval, exp, 0){
			if(e != NULL){
				switch(e->node.bnode->operator){
					case gtop:
					case ltop:
						if((getExpType(e->node.bnode->l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
							printTypeError(strdup(yytext), WRONGTYPE);
						}	
						break;
					case neqop:
					case eqop:
						if(getExpType(e->node.bnode->l) == -1 || getExpType(e->node.bnode->r) == -1 || (getExpType(e->node.bnode->l)/10)*10 != (getExpType(e->node.bnode->r)/10)*10){
							printTypeError(strdup(yytext), WRONGTYPE);
						}
						break;
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		/* epsilon */{
			LLretval = NULL;
		}
;

relexpr<Exp>(Exp *exp) : 
{
	exp = malloc(sizeof(Exp));
}
		sumexpr<l>(NULL)
		relexpr2<e>(l, exp, 0){
			if(e == NULL){
				LLretval = l;
			}else{
				switch(e->node.bnode->operator){
					case gtop:
					case ltop:
						if((getExpType(l)/10)*10 != INTEGER_TYPE || (getExpType(e->node.bnode->r)/10)*10 != INTEGER_TYPE){
							printTypeError(strdup(yytext), WRONGTYPE);
						}	
						break;
					case neqop:
					case eqop:
						if(getExpType(l) == -1 || getExpType(e->node.bnode->r) == -1 || (getExpType(l)/10)*10 != (getExpType(e->node.bnode->r)/10)*10){
							printTypeError(strdup(yytext), WRONGTYPE);
						}
						break;
				}
				LLretval = *exp;
			}
			free(exp);
		}
;

notexpr<Exp> : 
		NOT_TOK 
		notexpr<e>{
			if((getExpType(e)/10)*10 != BOOLEAN_TYPE){
				printTypeError(strdup(yytext), WRONGTYPE);
			}
			LLretval = makeUnNodeExp(makeUnNode(e, notop));
		}
	| 
		relexpr<e>(NULL){
			LLretval = e;
		}
;

andexpr2<Exp>(Exp left, Exp *exp) : 
		AND_OP 
		notexpr<r>{
			LLretval = makeBinNodeExp(makeBinNode(left, r, andop));
		}
		andexpr2<e>(LLretval, exp){
			if(e != NULL){
				if((getExpType(e->node.bnode->l)/10)*10 != BOOLEAN_TYPE || (getExpType(e->node.bnode->r)/10)*10 != BOOLEAN_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		CAND_OP 
		notexpr<r>{
			LLretval = makeBinNodeExp(makeBinNode(left, r, candop));
		}
		andexpr2<e>(LLretval, exp){
			if(e != NULL){
				if((getExpType(e->node.bnode->l)/10)*10 != BOOLEAN_TYPE || (getExpType(e->node.bnode->r)/10)*10 != BOOLEAN_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		/* epsilon */{
			LLretval = NULL;
		}
;

andexpr<Exp>(Exp *exp): 
{
	exp = malloc(sizeof(Exp));
}
		notexpr<l>
		andexpr2<e>(l, exp){
			if(e == NULL){
				LLretval = l;
			}else{
				if((getExpType(l)/10)*10 != BOOLEAN_TYPE || (getExpType(e->node.bnode->r)/10)*10 != BOOLEAN_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
				LLretval = *exp;
			}
			free(exp);
		}
;
			
expr2<Exp>(Exp left, Exp *exp): 
		OR_OP
		andexpr<r>(NULL){
			LLretval = makeBinNodeExp(makeBinNode(left, r, orop));
		}
		expr2<e>(LLretval, exp){
			if(e != NULL){
				if((getExpType(e->node.bnode->l)/10)*10 != BOOLEAN_TYPE || (getExpType(e->node.bnode->r)/10)*10 != BOOLEAN_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		COR_OP 
		andexpr<r>(NULL){
			LLretval = makeBinNodeExp(makeBinNode(left, r, corop));
		}
		expr2<e>(LLretval, exp){
			if(e != NULL){
				if((getExpType(e->node.bnode->l)/10)*10 != BOOLEAN_TYPE || (getExpType(e->node.bnode->r)/10)*10 != BOOLEAN_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
			}else{
				*exp = LLretval;
			}
		}
	| 
		/* epsilon */{
			LLretval = NULL;
		}
;

expr<ExpTree>(Exp *exp) :
{
	exp = malloc(sizeof(Exp));
}
		andexpr<l>(NULL)
		expr2<e>(l, exp){
			if(e == NULL){
				LLretval = l;
			}else{
				
				if((getExpType(l)/10)*10 != BOOLEAN_TYPE || (getExpType(e->node.bnode->r)/10)*10 != BOOLEAN_TYPE){
					printTypeError(strdup(yytext), WRONGTYPE);
				}
				LLretval = *exp;
			}
			free(exp);
		}
;

guardedcommand<GCommand>(ExpTree exp)	: 
		expr<e>(NULL)  {
			if (e != NULL) {
				if (getExpType(e)/10*10 != BOOLEAN_TYPE) {
					/* TODO: print expression */
					printTypeError(strdup(yytext), WRONGTYPE);
				} else {
					exp = e;
				}
			}
		}
		THEN_TOK 
		statementset<stmnts> {
			LLretval = makeGCommand(exp, stmnts->numStmnts, stmnts->stmnts);
			free(stmnts);
			
		}
;

guardedcommandset<GCmds>(GCmds gcmds)	: 
						guardedcommand<retgcmd>(NULL) {
							gcmds = malloc(sizeof(struct GCmds));
							gcmds->numGCmds = 1;
							gcmds->gCmds = malloc(sizeof(GCommand));
							gcmds->gCmds[0] = retgcmd;
						}
						[
							ALTGUARD 
							guardedcommand<retgcmd>(NULL)
							{
								// add them
								gcmds->numGCmds++;
								gcmds->gCmds = realloc(gcmds->gCmds,gcmds->numGCmds*sizeof(GCommand));
								gcmds->gCmds[gcmds->numGCmds-1] = retgcmd;
								// TODO: free?? if needed...
							}
						]* 
						{
							LLretval = gcmds;
						}
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

functioncall<FuncCall>(char *name, int type, Exps params): 
		LPARREN{
			NodeType nt = lookupType(name);
			if(nt != METHOD){
				printTypeError(strdup(name), METHODASKED);
			}
			type = getType(strdup(name));
			params = malloc(sizeof(struct Exps));
			params->numExps = 0;
			params->exps = NULL;
		}
		[
		expr<e>(NULL){
			params->numExps = 1;
			params->exps = malloc(params->numExps*sizeof(Exp));
			params->exps[0] = e;
		}
			[
				COMMA 
				expr<e>(NULL){
					params->numExps++;
					params->exps = realloc(params->exps, params->numExps*sizeof(Exp));
					params->exps[params->numExps-1] = e;
			}
			]*
		]?
		RPARREN{
			Node *expectedParams = lookupParams(name);
			int expectedNumParams = getNumNodes(expectedParams);
			if(params->numExps != expectedNumParams){
				printTypeError(strdup(name), PARAMMISMATCH1);
			}
			for(int i = params->numExps-1;i>=0;i--){
				int type = getExpType(params->exps[i]);
				int expectedType = expectedParams->evaltype;
				if((type/10)*10 != (expectedType/10)*10){
					printTypeError(strdup(name), PARAMMISMATCH2);
				}
				if(type%10 == 1 && expectedType%10 == 2){
					printTypeError(strdup(name), REFERENCETOCONSTANT);					
				}
				expectedParams = expectedParams->next;
			}
			FuncCall fc = makeFuncCall(type, name, params->numExps, params->exps);
			LLretval = fc;
			free(params);
		}
;

/* original version of assignmentcall that has an equal length for the identifiers and the following expressions (could make semantics very hard to handle) */
assignmentcallV1<Stmnts>(char *name): 
		ASSIGNMENT_OP 
		expr<LLdiscard>(NULL)
	| 
		COMMA 
		IDENTIFIER 
		assignmentcall<LLdiscard>(name)
		COMMA 
		expr<LLdiscard>(NULL)
;

/* newer version of assignmentcall that doesn't make sure yet that the amount of identifiers equals the amount of expressions (semantically easier to evaluate) */
assignmentcallV2<Stmnts>(char *name, Stmnts stmnts, Exps exps)	: 
		{
			//TODO typecheck name (watch out for return type of functions!)
			addTempList(strdup(name));
			
			stmnts = malloc(sizeof(struct Stmnts));
			stmnts->numStmnts = 1;
			stmnts->stmnts = malloc(stmnts->numStmnts*sizeof(Stmnt));
			int type = getType(strdup(name));
			stmnts->stmnts[0] = makeAssStmnt(makeAss(makeID(type, name), NULL, linecount));
		}
		[
			COMMA 
			IDENTIFIER{
				addTempList(strdup(yytext));
				
				//TODO typecheck IDENTIFIER (watch out for return type of functions!)
				stmnts->numStmnts++;
				stmnts->stmnts = realloc(stmnts->stmnts, stmnts->numStmnts*sizeof(Stmnt));
				int type = getType(strdup(yytext));
				stmnts->stmnts[stmnts->numStmnts-1] = makeAssStmnt(makeAss(makeID(type, yytext), NULL, linecount));
			}
		]* 
		ASSIGNMENT_OP 
		expr<e>(NULL){
			exps = malloc(sizeof(struct Exps));
			exps->numExps = 1;
			exps->exps = malloc(exps->numExps*sizeof(Exp));
			exps->exps[0] = e;
		}
		[
			COMMA 
			expr<e>(NULL){
				exps->numExps++;
				exps->exps = realloc(exps->exps, exps->numExps*sizeof(Exp));
				exps->exps[exps->numExps-1] = e;
			}
		]*{
			
		
			if(stmnts->numStmnts!=exps->numExps && exps->numExps!=1){
				/* if not equal, and not one to many... */
				freeTempList();
				printTypeError(NULL, ASSMISMATCH);
			}
			if ( exps->numExps != 1) {
				INode *n = tempidentifierlist;
				for(int i=exps->numExps-1;i+1>0;i--){
					/* type checking */
					int lhs = getType(strdup(n->name));
					int rhs = getExpType(exps->exps[i]);
					stmnts->stmnts[i]->assignment->expTree = exps->exps[i];
					if (lhs == VOID_TYPE) {
						//Trying to assign something to the proc
						printTypeError(strdup(n->name),RETURNINPROC);
					} else if (lookupType(n->name) == METHOD && lhs != VOID_TYPE) {
						// check if we are in the function
						if(!updateFunc(n->name)){
							printTypeError(strdup(n->name),VARIABLEASKED);
						}
					} else if ((lhs/10)*10 != (rhs/10)*10 ) {
						/* the list is freeëd in error */
						printTypeError(strdup(n->name),WRONGTYPE);
					}
					n = n->next;
				}
			} else {
				/* one to all statements */
				int rhs = getExpType(exps->exps[0]);
				INode *n = tempidentifierlist;
				for(int i=stmnts->numStmnts-1;i+1 > 0;i--){
					/* type checking */
					int lhs = getType(strdup(n->name));
					stmnts->stmnts[i]->assignment->expTree = deepCopyExp(exps->exps[0]);
					if (lhs == VOID_TYPE) {
						//Trying to assign something to the proc
						printTypeError(strdup(n->name),RETURNINPROC);
					} else if (lookupType(n->name) == METHOD && lhs != VOID_TYPE) {
						if(!updateFunc(n->name)){
							printTypeError(strdup(n->name),VARIABLEASKED);
						}
					} else if ((lhs/10)*10 != (rhs/10)*10 ) {
						printTypeError(strdup(n->name),WRONGTYPE);
					}
					n = n->next;
				}
				freeExp(exps->exps[0]);
			}
			freeTempList();
			free(exps->exps);
			free(exps);
			LLretval = stmnts;
			
		}
;

/* select assignmentcall V1 or V2 */
assignmentcall<Stmnts>(char *name) : 
		assignmentcallV2<ss>(name, NULL, NULL){
			LLretval = ss;
		}
;

dostatement<Stmnt>:	
		DOBEGIN_TOK 
		guardedcommandset<gCmds>(NULL)
		{
			LLretval = makeDoStmnt(makeDo(gCmds->numGCmds, gCmds->gCmds));
			free(gCmds);
		}
		DOEND_TOK
;

ifstatement<Stmnt>:	
		IFBEGIN_TOK 
		guardedcommandset<gCmds>(NULL)
		{
			LLretval = makeIfStmnt(makeIf(gCmds->numGCmds, gCmds->gCmds));
			free(gCmds);
		}
		IFEND_TOK
;

printable<Printable> : 
		STRING{
			Printable p = makeStringPrintable(yytext);
			LLretval = p;
		}
	| 
		expr<e>(NULL){
			Printable p = makeExpPrintable(e);
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

readcall<RCall>(IDs ids)	: 
		READ_TOK 
		IDENTIFIER{
			ids = malloc(sizeof(struct IDs));
			ids->numIds = 1;
			ids->ids = malloc(ids->numIds * sizeof(ID));
			ids->ids[0] = makeID(getType(strdup(yytext)), yytext);
		}
		[
			COMMA 
			IDENTIFIER{
				ids->numIds++;
				ids->ids = realloc(ids->ids, ids->numIds * sizeof(ID));
				ids->ids[ids->numIds-1] = makeID(getType(strdup(yytext)), yytext);
			}
		]*{
			RCall rc = makeRCall(ids->numIds, ids->ids);
			free(ids);
			LLretval = rc;
		}
;

call<Stmnts>(char *name) :	
		functioncall<fc>(name, 0, NULL){
			Stmnts ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 1;
			ss->stmnts = malloc(ss->numStmnts*sizeof(Stmnt));
			ss->stmnts[0] = makeFuncCallStmnt(fc);
		LLretval = ss;
		}
	|	
		assignmentcall<ss>(name){
			LLretval = ss;
		}
		
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
						if ( !existsInTop(n->name) && !isMethod(n->name) ) {
							insertIdentifier(strdup(n->name), VARIABLE, stringToEvalType(yytext), NULL);
						} else if(isMethod(n->name)){
							printTypeError(n->name, VARIABLEASKED);
						} else {
							printTypeError(n->name, DUPLICATE);
						}
						n = n->next;
					}
					freeTempList();
				}
			;

statement<Stmnts>(Stmnts ss, char *name) : 
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
		IDENTIFIER{
			name = strdup(yytext);
		}
		call<stmnts>(name){
			ss = stmnts;
			free(name);
		}
	| 
		printcall<wc>(0, NULL){
			ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 1;
			ss->stmnts = malloc(ss->numStmnts*sizeof(Stmnt));
			ss->stmnts[0] = makeWCallStmnt(wc);
		}
	| 
		readcall<rc>(NULL){
			ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 1;
			ss->stmnts = malloc(ss->numStmnts*sizeof(Stmnt));
			ss->stmnts[0] = makeRCallStmnt(rc);
		}
	| 
		dostatement<dostmnt> {
			ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 1;
			ss->stmnts = malloc(ss->numStmnts*sizeof(Stmnt));
			ss->stmnts[0] = dostmnt;
		}
	|
		ifstatement<ifstmnt> {
			ss = malloc(sizeof(struct Stmnts));
			ss->numStmnts = 1;
			ss->stmnts = malloc(ss->numStmnts*sizeof(Stmnt));
			ss->stmnts[0] = ifstmnt;
		}
]{
	LLretval = ss;
}
;

parameterset 	: 
		VAR_TOK
		IDENTIFIER {
			addTempList(strdup(yytext));
		}
		[
			COMMA 
			identifierarray<ids>(NULL){
				for(int i=0;i<ids->numIds;i++){
					freeID(ids->ids[i]);
				}
				free(ids->ids);
				free(ids);//not used
			}
		]?
		TYPE_OP
		TYPE {
			/* call by ref */
			int tc_type = stringToEvalType(yytext) + 2;
			INode *in = tempidentifierlist;
			while (in != NULL) {
				Node *new = makeNode(strdup(in->name), VARIABLE, tc_type, NULL);
				new->next = tempparamlist;
				tempparamlist = new;
				in = in->next;
			}
			freeTempList();
		}
		[
			COMMA 
			parameterset
		]?
	| 
		IDENTIFIER
		{
			addTempList(strdup(yytext));
		}
		[
			COMMA 
			identifierarray<ids>(NULL){
				for(int i=0;i<ids->numIds;i++){
					freeID(ids->ids[i]);
				}
				free(ids->ids);
				free(ids);//not used
			}
		]?
		TYPE_OP
		TYPE {
			/* call by value */
			int tc_type = stringToEvalType(yytext);
			INode *in = tempidentifierlist;
			while (in != NULL) {
				Node *new = makeNode(strdup(in->name), VARIABLE, tc_type, NULL);
				new->next = tempparamlist;
				tempparamlist = new;
				in = in->next;
			}
			freeTempList();
		}
		[
			COMMA 
			parameterset
		]?
	;

variable<Dec>(ExpTree exp, int type) : 
	[
			BOOLEAN{
				char *bool = strdup(yytext);
				BoolVal bv;
				if(strcmp(bool, "true") == 0){
					bv = true;
				}else if(strcmp(bool, "false") == 0){
					bv = false;
				}
				type = CONST_BOOLEAN_TYPE;
				free(bool);
				exp = makeBoolExp(makeBool(bv));
			}
		| 
			NUMBER{
				type = CONST_INTEGER_TYPE;
				exp = makeIntExp(makeInt(yytext));
			}
	]{
		LLretval = makeExpDec(makeID(type, NULL), variable, exp);
	}
	| 
		STRING{
			LLretval = makeStringDec(makeID(0, NULL), variable, yytext);
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
		statement<ss>(NULL, NULL){
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
statementsetV2	: statement<LLdiscard>(NULL, NULL)
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

function<FuncDef>(int numparams, Param *p, int numStmnts, Stmnt *stmnts)	: 
				FUNCTION_TOK 
				IDENTIFIER 
				{
					lastmethodidentifier = strdup(yytext);
				}
				LPARREN 
				parameterset? 
				RPARREN 
				THEN_TOK
				TYPE 
				{
					int tc_type = stringToEvalType(yytext);
					
					if (!existsInTop(lastmethodidentifier)) {
						insertIdentifier(strdup(lastmethodidentifier), METHOD, tc_type, tempparamlist);
						tempparamlist = NULL;
						
					} else {
						freeTempParamList();
						/* lastmethodidentifier is freeëd in printing... */
						printTypeError(lastmethodidentifier, DUPLICATE);
					}
					
				}
				SEMICOLON
				{
					putBlock(lastmethodidentifier);
					/* insert all the parameters to the symboltable */
					Node *n = lookupParams(lastmethodidentifier);
					numparams = getNumNodes(n);
					p = malloc(numparams * sizeof(struct Parameter));
					int i = numparams-1;
					while (n != NULL) {
						if (!existsInTop(n->name) && !isMethod(n->name) ) {
							insertIdentifier(strdup(n->name), n->type, n->evaltype, NULL);
							if (n->evaltype%10 == 2) {
								p[i] = makeParam(makeID(n->evaltype,n->name), byRef);
							} else {
								p[i] = makeParam(makeID(n->evaltype,n->name), byVal);
							}
							i--;
							n = n->next;
						} else if(isMethod(n->name)){
							printTypeError(n->name, VARIABLEASKED);
						} else {
							printTypeError(lastmethodidentifier, DUPLICATE);
						}
					}
				}
				statementset<ss>
				END_TOK 
				{
					int returns = popBlock();
					if (!returns) {
						printTypeError(strdup(lastmethodidentifier), MISSINGRETURN);
					}
					LLretval = makeFuncDef(makeID(getType(strdup(lastmethodidentifier)), lastmethodidentifier),numparams, p, ss->numStmnts, ss->stmnts);
					free(lastmethodidentifier);
					lastmethodidentifier = NULL;
					free(ss);
				}
				SEMICOLON
			;

procedure<ProcDef>(int numparams, Param *p, int numStmnts, Stmnt *stmnts)	: 
				PROCEDURE_TOK 
				IDENTIFIER 
				{
					lastmethodidentifier = strdup(yytext);
				}
				LPARREN 
				parameterset?
				RPARREN 
				{
					if (!existsInTop(lastmethodidentifier)) {
						insertIdentifier(strdup(lastmethodidentifier), METHOD, VOID_TYPE, tempparamlist);
						tempparamlist = NULL;
					} else {
						freeTempParamList();
						/* lastmethodidentifier is freed in printing... */
						printTypeError(lastmethodidentifier, DUPLICATE);
					}
				}
				SEMICOLON {
					putBlock("[LOCAL PROCEDURE]");
					/* insert all the parameters to the symboltable */
					Node *n = lookupParams(lastmethodidentifier);
					numparams = getNumNodes(n);
					p = malloc(numparams * sizeof(struct Parameter));
					int i = 0;
					while (n != NULL) {
						if (!existsInTop(n->name) && !isMethod(n->name) ) {
							insertIdentifier(strdup(n->name), n->type, n->evaltype, NULL);
							if (n->evaltype%10 == 2) {
								p[i] = makeParam(makeID(n->evaltype,n->name), byRef);
							} else {
								p[i] = makeParam(makeID(n->evaltype,n->name), byVal);
							}
							i++;
							n = n->next;
						} else if(isMethod(n->name)){
							printTypeError(n->name, VARIABLEASKED);
						} else {
							printTypeError(n->name, DUPLICATE);
						}
					}
				}
				statementset<ss>
				END_TOK {
					popBlock();
					LLretval = makeProcDef(lastmethodidentifier,numparams, p, ss->numStmnts, ss->stmnts);
					free(lastmethodidentifier);
					lastmethodidentifier = NULL;
					free(ss);
				}
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
			INode *n = tempidentifierlist;
			while (n != NULL) {
				/* check if the  identifier exists already */
				if ( !existsInTop(n->name) ) {
					// type+1 for constants
					insertIdentifier(strdup(n->name), VARIABLE, type+1, NULL);
				} else {
					printTypeError(n->name, DUPLICATE);
				}
				n = n->next;
			}
			freeTempList();
		}
		COMPARE_OP 
		variable<d>(NULL, 0){
			dec = d;
			int tc_type = d->id->type;
			NodeType nt = lookupType(name);
			int lookuptype = lookupEvalType(name, nt);
			if (nt != VARIABLE || tc_type != lookuptype ) {
				//print error
				printTypeError(name, WRONGTYPE);
			}
		}
		SEMICOLON{
			dec->id->name = name;
			dec->idType = constant;
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
		[
			procedure<procdef>(0,NULL,0,NULL){
				int oldNumProcDefs = numProcDefs;
					numProcDefs++;
					if(oldNumProcDefs == 0){
						procDefs = malloc(numProcDefs*sizeof(ProcDef));
					}else{
						procDefs = realloc(procDefs, numProcDefs*sizeof(ProcDef));
					}
					procDefs[oldNumProcDefs] = procdef;
			}
		]* {
			printf("Num of proc defs: %d\n", numProcDefs);
		}
		[
			function<funcdef>(0,NULL,0,NULL){
				int oldNumFuncDefs = numFuncDefs;
				numFuncDefs++;
				if(oldNumFuncDefs == 0){
					funcDefs = malloc(numFuncDefs*sizeof(FuncDef));
				}else{
					funcDefs = realloc(funcDefs, numFuncDefs*sizeof(FuncDef));
				}
				funcDefs[oldNumFuncDefs] = funcdef;
			}
		]* {
			printf("Num of func defs: %d\n", numFuncDefs);
		}
		BEGIN_TOK {
			putBlock("[MAIN VARIABLES]"); /* add a new frame of reference */
		} 
		statementset<bss>{
			numBodyStmnts = bss->numStmnts;
			printf("Num of bodystmnts: %d\n", bss->numStmnts);
			bodyStmnts = bss->stmnts;
			free(bss);
		}
		END_TOK {
			popBlock();
			Prog prog = makeProg(programname, numConstDefs, constDefs, numVarDefs, varDefs, numProcDefs, procDefs, numFuncDefs, funcDefs, numBodyStmnts, bodyStmnts);
			LLretval = prog;
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
			/*printf("Program name: %s\n", program->name);
			if(strcmp(file_name, "riktest.gcl") == 0){
				printf("Print string: %s\n", program->bodyStmnts[0]->wCall->items[0]->string);
				printf("boolval: %s\n", (program->constDefs[0]->expTree->node.boolval->value == true)?"true":"false");
				printf("intval: %s\n", program->constDefs[1]->expTree->node.intval->value);
			}*/
		}
; 
