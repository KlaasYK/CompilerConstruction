#include <stdio.h>
#include <stdlib.h>

#include "codegen.h"
#include "tree.h"

FILE *outputfile;

void WTF(char *code) {
	fputs(code,outputfile);
}


void writeHeaders() {
		WTF("#include <stdio.h>\n");
		WTF("#include <stdlib.h>\n");
		WTF("#include \"bigints.h\"\n");
}



void compileMain() {
	WTF("int main(int argc, char **argv){\n");
	
	//TODO: compile body statements
	
	WTF("return EXIT_SUCCESS;\n");
	WTF("}\n");
}

void generateCode(Prog program, char *outputfilename) {
	outputfile = fopen(outputfilename, "w");
	
	writeHeaders();
	
	//TODO: compile functions and procedures
	
	compileMain();
	
	fclose(outputfile);
}