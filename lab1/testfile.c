#include <stdio.h>
#include <assert.h>
#include "bigints.c"

int main() {
	Integer a, b;
	makeIntegerFromString(&a, "-50545936");
	printInteger(a);
	printf("\n");
	freeInteger(&a);
/*
	makeIntegerFromString(&a, "-98");
	makeIntegerFromString(&b, "-998");
	printInteger(a);
	printf("\n");
	printInteger(b);
	printf("\n");

	subInteger(&a, b);
	printInteger(a);
	printf("\n");

	freeInteger(&a);
	freeInteger(&b);


	makeIntegerFromString(&a, "23663");
	makeIntegerFromString(&b, "2356");
	printInteger(a);
	printf("\n");
	printInteger(b);
	printf("\n");
	mulInteger(&a, b);
	printInteger(a);
	printf("\n");

	freeInteger(&a);
	freeInteger(&b);
*/
	return 0;
}