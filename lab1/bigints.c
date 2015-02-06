#include <stdio.h>
#include <stdlib.h>

/* datastructure for infinite intgers */
struct EGCLint {
    int* digits; /* the value for each of the digits, little endian */
    unsigned long length; /* maximum value is approx. 10^4294967295, 
	not infinite, but close enough. */
    int sign; /* wheter it is positive, of negative */
};
typedef struct EGCLint Integer;

/* utility function to malloc the memory*/
void mallocInteger(Integer *a){
    a->digits = malloc(a->length*sizeof(int));
}

/* utility function to free the memory */
void freeInteger(Integer *a) {
    free(a);
}

/* make integer form a string */
void makeIntegerFromString(Integer *a, char digits[]) {
    unsigned long i = 0;
    if (digit[0] == '-') {
        a->sign = -1;
        i++;
    }else{
        a->sign = 1;
    }
    for (i; digit[i] != '\0'; i++) {
    }
    a->length = i-1;
    mallocInteger(a);
    unsigned long j = 0;
    for (i; digit[i] != '\0'; i++) {
        a->digits[j] = digits[i] - 48;
        j++;
    }
};

/* prints integer to stdout */
void printInteger(Integer a) {
    unsigned long i;
    for (i = a.length; i > 0; --i) {
        printf("%d", a.digits[i - 1]);
    }
}

/* a := a + b */
void addInteger(Integer *a, Integer b);

/* a := a - b */
void subInteger(Integer *a, Integer b);

/* a := a * b */
void mulInteger(Integer *a, Integer b);

/* a := a div b */
void divInteger();

/* make integer form a string */
void makeIntegerFromString(Integer *a, char digits[]);

/* a := a + b */
void addInteger(Integer *a, Integer b);

/* a := a - b */
void subInteger(Integer *a, Integer b);

/* a := a * b */
void mulInteger(Integer *a, Integer b);

/* a := a div b */
void divInteger();
