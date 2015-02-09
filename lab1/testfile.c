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
	
}

void testSubInteger(){
	operatorHelper("2", "2", subInteger, '-');
	operatorHelper("293487239847239847928347", "237957909275092850928355", subInteger, '-');
	operatorHelper("25435", "1", subInteger, '-');
	operatorHelper("1", "25435", subInteger, '-');
	operatorHelper("1", "999", subInteger, '-');
	operatorHelper("999", "1", subInteger, '-');
	operatorHelper("500", "501", subInteger, '-');
	operatorHelper("501", "500", subInteger, '-');
	
	operatorHelper("-2", "2", subInteger, '-');
	operatorHelper("-293487239847239847928347", "237957909275092850928355", subInteger, '-');
	operatorHelper("-25435", "1", subInteger, '-');
	operatorHelper("-1", "25435", subInteger, '-');
	operatorHelper("-1", "999", subInteger, '-');
	operatorHelper("-999", "1", subInteger, '-');
	operatorHelper("-500", "501", subInteger, '-');
	operatorHelper("-501", "500", subInteger, '-');
	
	operatorHelper("2", "-2", subInteger, '-');
	operatorHelper("293487239847239847928347", "-237957909275092850928355", subInteger, '-');
	operatorHelper("25435", "-1", subInteger, '-');
	operatorHelper("1", "-25435", subInteger, '-');
	operatorHelper("1", "-999", subInteger, '-');
	operatorHelper("999", "-1", subInteger, '-');
	operatorHelper("500", "-501", subInteger, '-');
	operatorHelper("501", "-500", subInteger, '-');
	
	operatorHelper("-2", "-2", subInteger, '-');
	operatorHelper("-293487239847239847928347", "-237957909275092850928355", subInteger, '-');
	operatorHelper("-25435", "-1", subInteger, '-');
	operatorHelper("-1", "-25435", subInteger, '-');
	operatorHelper("-1", "-999", subInteger, '-');
	operatorHelper("-999", "-1", subInteger, '-');
	operatorHelper("-500", "-501", subInteger, '-');
	operatorHelper("-501", "-500", subInteger, '-');
}

void testMulInteger(){
	operatorHelper("2", "3", mulInteger, '*'); // z0
	operatorHelper("4", "5", mulInteger, '*'); // z2
	operatorHelper("2", "4", addInteger ,'+'); // z1a
	operatorHelper("3", "5", addInteger ,'+'); // z1b
	operatorHelper("6", "8", mulInteger, '*'); // z1
	
	operatorHelper("48", "20", subInteger ,'-'); // z1 - z2
	operatorHelper("28", "6", subInteger ,'-'); // z1 - z2 - z0
	
	// (z1-z2-z0) * 10
	
	// z2 * 100
	
	operatorHelper("220", "2000", addInteger ,'+');
	operatorHelper("2220", "6", addInteger ,'+');
	printf("%d * %d = %d\n", 42, 53, 42 * 53);
	
	
	
	operatorHelper("42", "53", mulInteger, '*');
	//operatorHelper("23663", "2356", mulInteger, '*');
}

void testShiftRight() {
	Integer a;
	makeIntegerFromString(&a, "42");
	shiftRight(&a, 2);
	printInteger(a);
	printf("\n");
	freeInteger(&a);
}

void testDivInteger(){
	
}

void testModInteger(){
	
}

void testPowInteger(){
	
}

int main() {
	testShiftRight();
	printf("\n");
	testAddInteger();
	printf("\n");
	testSubInteger();
	printf("\n");
	testMulInteger();
	return 0;
}
