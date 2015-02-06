#include <stdio.h>
#include <stdlib.h>

/* datastructure for infinite intgers */
struct EGCLint {
	int* digits; /* the value for each of the digits */
	unsigned long length; /* maximum value is approx. 10^4294967295, 
	not infinite, but close enough. */
	int sign; /* wheter it is positive, of negative */
};

typedef struct EGCLint Integer;

/* utility function to free the memory */
void freeInteger(Integer *a) {
	free(a);
}

/* make integer form a string */
void makeIntegerFromString(Integer *a, char digits[]);

/* prints integer to stdout */
void printInteger(Integer a);

/* a := a + b */
void addInteger(Integer *a, Integer b);

/* a := a - b */
void subInteger(Integer *a, Integer b);

/* a := a * b */
void mulInteger(Integer *a, Integer b);

/* a := a div b */
void divInteger();