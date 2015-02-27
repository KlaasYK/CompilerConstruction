/* THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY LLnextgen. DO NOT EDIT */
#define LL_NTERMINALS 6
#define LL_NSETS 2
#define LL_SSETS 4
#define LLinset(LLx) (LLsets[LLx*LL_SSETS + (LLcsymb/8)] & (1<<(LLcsymb & 7)))
#define LL_SCANDONE(LLx) if (LLsymb != LLx) LLerror(LLx);
static int LLscnt[LL_NSETS+1], LLtcnt[LL_NTERMINALS];
static int LLcsymb;
#include <string.h>
static const char LLsets[] = {
	'\x32', 	'\x00', 	'\x00', 	'\x00', 
	'\x30', 	'\x00', 	'\x00', 	'\x00', 
	0
};
static const int LLindex[] = { 0,
	   0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	   0,    1,    2,    3,    4,    5};
int LLsymb;
static int LLreissue;
int yylex(void);
static int LLlexerWrapper(void) {
	if (LLreissue == -2 /* LL_NEW_TOKEN */) {
		return yylex();
	} else {
		int LLretval = LLreissue;
		LLreissue = -2 /* LL_NEW_TOKEN */;
		return LLretval;
	}
}
void LLmessage(int);
static void LLread(void) { LLcsymb = LLindex[(LLsymb = LLlexerWrapper()) + 1]; }
static int LLskip(void) {
	int LL_i;
	if (LLcsymb >= 0) {
		if (LLtcnt[LLcsymb] != 0) return 0;
		for (LL_i = 0; LL_i < LL_NSETS; LL_i++)
			if (LLscnt[LL_i] != 0 && LLinset(LL_i))
				return 0;
	}

	for (;;) {
		LLmessage(0 /* LL_DELETE */);
		while ((LLcsymb = LLindex[(LLsymb = LLlexerWrapper()) + 1]) < 0) LLmessage(0 /* LL_DELETE */);
		if (LLtcnt[LLcsymb] != 0)
			return 1;
		for (LL_i = 0; LL_i < LL_NSETS; LL_i++)
			if (LLscnt[LL_i] != 0 && LLinset(LL_i))
				return 1;
	}
}
static void LLerror(int LLtoken) {
	if (LLtoken == 256 /* EOFILE */) {
		LLmessage(-1 /* LL_MISSINGEOF */);
		while (LLindex[(LLsymb = LLlexerWrapper()) + 1] != 0) /*NOTHING*/ ;
		return;
	}
	LLtcnt[LLindex[LLtoken + 1]]++;
	LLskip();
	LLtcnt[LLindex[LLtoken + 1]]--;
	if (LLsymb != LLtoken) { LLreissue = LLsymb; LLmessage(LLtoken); }
}
#include "grammar.h"
#line 6 "grammar.g"

	#include <stdio.h>
	#include <stdlib.h>

	int main(int argc, char *argv[]) {
		parser();
		printf("Accepted\n");
		return 0;
	}

	void LLmessage(int token) {
		printf("Parse error: %d\n", token);
		exit(EXIT_FAILURE);
	}

#line 111 "grammar.c"
static void LL0_start(void);
static void LL1_atom(void);
static void LL0_start(void){
LL_0:
switch (LLcsymb) {
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 4:/* ATOK */
case 5:/* BTOK */
LLscnt[0]--;
LLscnt[1]++;
LL1_atom();
break;
case 1:/* LPAR */
LLscnt[0]--;
LLscnt[0]++;
LLtcnt[2]++;
LLscnt[1]++;
LLtcnt[3]++;
LL_SCANDONE(257);/* LPAR */
LLread();
LL0_start();
LLread();
LLtcnt[2]--;
LL_SCANDONE(258);/* PLUS */
LLread();
LL1_atom();
LLread();
LLtcnt[3]--;
LL_SCANDONE(259);/* RPAR */
break;
}
}
static void LL1_atom(void){
LL_0:
switch (LLcsymb) {
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 4:/* ATOK */
LLscnt[1]--;
LL_SCANDONE(260);/* ATOK */
break;
case 5:/* BTOK */
LLscnt[1]--;
LL_SCANDONE(261);/* BTOK */
break;
}
}
void parser(void) {
	memset(LLscnt, 0, LL_NSETS * sizeof(int));
	memset(LLtcnt, 0, LL_NTERMINALS * sizeof(int));
	LLtcnt[0]++;
	LLsymb = 0;
	LLreissue = -2 /* LL_NEW_TOKEN */;
	LLread();
LLscnt[0]++;
	LL0_start();
	LLread();
	if (LLcsymb != 0) LLerror(256 /* EOFILE*/);
}

