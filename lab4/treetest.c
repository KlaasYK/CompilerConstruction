#include <stdio.h>
#include "tree.h"

int main(){
    printf("test0\n");
    ExpTree et = makeBinNodeExp(
	makeBinNode(
	    makeUnNodeExp(
		makeUnNode(
		    makeIntExp(
			makeInt("45")
		    ), 
		    negop
		)
	    ), 
	    makeIntExp(
		makeInt("934")
	    ), 
	    plusop
	)
    );
    printf("test1\n");
    freeExp(et);
    printf("test2\n");
    return 0;
}