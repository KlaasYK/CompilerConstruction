#include <stdio.h>
#include <assert.h>
#include "bigints.c"

void operatorHelper(const char *aStr, const char *bStr, void (*f)(Integer *, Integer), char operator){
	
	Integer a, b;
	makeIntegerFromString2(&a, aStr);
	makeIntegerFromString2(&b, bStr);
	printInteger(a);
	printf(" %c ", operator);
	printInteger2(b);
	printf(" = ");
	(*f)(&a, b);
	printInteger2(a);
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
	operatorHelper("2", "3", mulInteger, '*');
	operatorHelper("42", "53", mulInteger, '*');
	operatorHelper("23663", "2356", mulInteger, '*');
	operatorHelper("42", "0", mulInteger, '*');
	operatorHelper("0", "42", mulInteger, '*');
	operatorHelper("25", "-4", mulInteger, '*');
	operatorHelper("-25", "4", mulInteger, '*');
	operatorHelper("-25", "-4", mulInteger, '*');
	operatorHelper("-293487239847239847928347", "-237957909275092850928355", mulInteger, '*');

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
	operatorHelper("5", "2", divInteger, '/');
	operatorHelper("50", "2", divInteger, '/');
	operatorHelper("65536", "2", divInteger, '/');
	
	operatorHelper("131072", "2", divInteger, '/');
	
	operatorHelper("54509999823543694364987654935879875943", "23946239875692375752", divInteger, '/');
	operatorHelper("23946239875692375752", "54509999823543694364987654935879875943", divInteger, '/');
	operatorHelper("42", "0", divInteger, '/');
	
}

void testModInteger(){
	operatorHelper("5", "2", modInteger, '%');
	
}

void testPowInteger(){
	
}

int main() {
	/*testDivInteger();
	/*testShiftRight();*/
	printf("\n");
	testAddInteger();
	printf("\n");
	testSubInteger();
	printf("\n");
	testMulInteger();
	printf("\n");
	testDivInteger();
	/*printf("\n");
	testModInteger();*/
	return 0;
}
