#include <stdio.h>
#include <assert.h>
#include "bigints.c"

void operatorHelper(const char *aStr, const char *bStr, void (*f)(Integer *, Integer), char operator){
	
	Integer a, b;
	makeIntegerFromString(&a, aStr);
	makeIntegerFromString(&b, bStr);
	printInteger(a);
	printf(" %c ", operator);
	printInteger(b);
	printf(" = ");
	(*f)(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
}

void testPrintInteger(){
	
}

void testMakeIntegerFromString(){
	Integer a;
	makeIntegerFromString(&a, "-50545000936034002");
	printInteger(a);
	printf("\n");
	freeInteger(&a);
}

void testAddInteger(){	
	operatorHelper("2", "2", addInteger, '+');
	operatorHelper("293487239847239847928347", "237957909275092850928355", addInteger, '+');
	operatorHelper("25435", "1", addInteger, '+');
	operatorHelper("1", "25435", addInteger, '+');
	operatorHelper("1", "999", addInteger, '+');
	operatorHelper("999", "1", addInteger, '+');
	operatorHelper("500", "501", addInteger, '+');
	operatorHelper("501", "500", addInteger, '+');
	
	operatorHelper("-2", "2", addInteger, '+');
	operatorHelper("-293487239847239847928347", "237957909275092850928355", addInteger, '+');
	operatorHelper("-25435", "1", addInteger, '+');
	operatorHelper("-1", "25435", addInteger, '+');
	operatorHelper("-1", "999", addInteger, '+');
	operatorHelper("-999", "1", addInteger, '+');
	operatorHelper("-500", "501", addInteger, '+');
	operatorHelper("-501", "500", addInteger, '+');
	
	operatorHelper("2", "-2", addInteger, '+');
	operatorHelper("293487239847239847928347", "-237957909275092850928355", addInteger, '+');
	operatorHelper("25435", "-1", addInteger, '+');
	operatorHelper("1", "-25435", addInteger, '+');
	operatorHelper("1", "-999", addInteger, '+');
	operatorHelper("999", "-1", addInteger, '+');
	operatorHelper("500", "-501", addInteger, '+');
	operatorHelper("501", "-500", addInteger, '+');
	
	operatorHelper("-2", "-2", addInteger, '+');
	operatorHelper("-293487239847239847928347", "-237957909275092850928355", addInteger, '+');
	operatorHelper("-25435", "-1", addInteger, '+');
	operatorHelper("-1", "-25435", addInteger, '+');
	operatorHelper("-1", "-999", addInteger, '+');
	operatorHelper("-999", "-1", addInteger, '+');
	operatorHelper("-500", "-501", addInteger, '+');
	operatorHelper("-501", "-500", addInteger, '+');
/*
	
	makeIntegerFromString(&a, "293487239847239847928347");
	makeIntegerFromString(&b, "237957909275092850928355");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
	makeIntegerFromString(&a, "283049");
	makeIntegerFromString(&b, "1");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
	makeIntegerFromString(&a, "283049");
	makeIntegerFromString(&b, "1");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
*/
	
}

void testSubInteger(){
	operatorHelper("1", "25435", subInteger, '-');
}

void testMulInteger(){
	operatorHelper("23663", "2356", mulInteger, '*');
}

void testDivInteger(){
	
}

void testModInteger(){
	
}

void testPowInteger(){
	
}

int main() {
	testAddInteger();
	printf("\n");
	testSubInteger();
	return 0;
#include <stdio.h>
#include <assert.h>
#include "bigints.c"

void operatorHelper(const char *aStr, const char *bStr, void (*f)(Integer *, Integer), char operator){
	
	Integer a, b;
	makeIntegerFromString(&a, aStr);
	makeIntegerFromString(&b, bStr);
	printInteger(a);
	printf(" %c ", operator);
	printInteger(b);
	printf(" = ");
	(*f)(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
}

void testPrintInteger(){
	
}

void testMakeIntegerFromString(){
	Integer a;
	makeIntegerFromString(&a, "-50545000936034002");
	printInteger(a);
	printf("\n");
	freeInteger(&a);
}

void testAddInteger(){	
	operatorHelper("2", "2", addInteger, '+');
	operatorHelper("293487239847239847928347", "237957909275092850928355", addInteger, '+');
	operatorHelper("25435", "1", addInteger, '+');
	operatorHelper("1", "25435", addInteger, '+');
	operatorHelper("1", "999", addInteger, '+');
	operatorHelper("999", "1", addInteger, '+');
	operatorHelper("500", "501", addInteger, '+');
	operatorHelper("501", "500", addInteger, '+');
	
	operatorHelper("-2", "2", addInteger, '+');
	operatorHelper("-293487239847239847928347", "237957909275092850928355", addInteger, '+');
	operatorHelper("-25435", "1", addInteger, '+');
	operatorHelper("-1", "25435", addInteger, '+');
	operatorHelper("-1", "999", addInteger, '+');
	operatorHelper("-999", "1", addInteger, '+');
	operatorHelper("-500", "501", addInteger, '+');
	operatorHelper("-501", "500", addInteger, '+');
	
	operatorHelper("2", "-2", addInteger, '+');
	operatorHelper("293487239847239847928347", "-237957909275092850928355", addInteger, '+');
	operatorHelper("25435", "-1", addInteger, '+');
	operatorHelper("1", "-25435", addInteger, '+');
	operatorHelper("1", "-999", addInteger, '+');
	operatorHelper("999", "-1", addInteger, '+');
	operatorHelper("500", "-501", addInteger, '+');
	operatorHelper("501", "-500", addInteger, '+');
	
	operatorHelper("-2", "-2", addInteger, '+');
	operatorHelper("-293487239847239847928347", "-237957909275092850928355", addInteger, '+');
	operatorHelper("-25435", "-1", addInteger, '+');
	operatorHelper("-1", "-25435", addInteger, '+');
	operatorHelper("-1", "-999", addInteger, '+');
	operatorHelper("-999", "-1", addInteger, '+');
	operatorHelper("-500", "-501", addInteger, '+');
	operatorHelper("-501", "-500", addInteger, '+');
/*
	
	makeIntegerFromString(&a, "293487239847239847928347");
	makeIntegerFromString(&b, "237957909275092850928355");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
	makeIntegerFromString(&a, "283049");
	makeIntegerFromString(&b, "1");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
	makeIntegerFromString(&a, "283049");
	makeIntegerFromString(&b, "1");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
*/
	
}

void testSubInteger(){
	operatorHelper("1", "25435", subInteger, '-');
}

void testMulInteger(){
	operatorHelper("23663", "2356", mulInteger, '*');
}

void testDivInteger(){
	
}

void testModInteger(){
	
}

void testPowInteger(){
	
}

int main() {
	testAddInteger();
	printf("\n");
	testSubInteger();
	return 0;
#include <stdio.h>
#include <assert.h>
#include "bigints.c"

void operatorHelper(const char *aStr, const char *bStr, void (*f)(Integer *, Integer), char operator){
	
	Integer a, b;
	makeIntegerFromString(&a, aStr);
	makeIntegerFromString(&b, bStr);
	printInteger(a);
	printf(" %c ", operator);
	printInteger(b);
	printf(" = ");
	(*f)(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
}

void testPrintInteger(){
	
}

void testMakeIntegerFromString(){
	Integer a;
	makeIntegerFromString(&a, "-50545000936034002");
	printInteger(a);
	printf("\n");
	freeInteger(&a);
}

void testAddInteger(){
	Integer a, b;
	
	operatorHelper("2", "2", addInteger, '+');
	operatorHelper("293487239847239847928347", "237957909275092850928355", addInteger, '+');
	operatorHelper("25435", "1", addInteger, '+');
	operatorHelper("1", "25435", addInteger, '+');
	operatorHelper("1", "999", addInteger, '+');
	operatorHelper("999", "1", addInteger, '+');
	operatorHelper("500", "501", addInteger, '+');
	operatorHelper("501", "500", addInteger, '+');
/*
	
	makeIntegerFromString(&a, "293487239847239847928347");
	makeIntegerFromString(&b, "237957909275092850928355");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
	makeIntegerFromString(&a, "283049");
	makeIntegerFromString(&b, "1");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
	
	makeIntegerFromString(&a, "283049");
	makeIntegerFromString(&b, "1");
	printInteger(a);
	printf("+");
	printInteger(b);
	printf("=");
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
	freeInteger(&b);
*/
	
}

void testSubInteger(){
	Integer a, b;
	makeIntegerFromString(&a, "-98");
	makeIntegerFromString(&b, "-998");
	printInteger(a);
	printf("-");
	printInteger(b);
	printf("=");

	subInteger(&a, b);
	printInteger(a);
	printf("\n");
	
}

void testMulInteger(){
	Integer a, b;

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
}

void testDivInteger(){
	
}

void testModInteger(){
	
}

void testPowInteger(){
	
}

int main() {
	testAddInteger();
	return 0;
}
