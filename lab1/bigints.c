#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) a<b?a:b

/* datastructure for infinite intgers */
struct EGCLint {
    int* digits; /* the value for each of the digits, big endian */
    unsigned long length; /* maximum value is approx. 10^4294967295, 
	not infinite, but close enough. */
    int sign; /* wheter it is positive, of negative */
};
typedef struct EGCLint Integer;

/* utility function to malloc the memory*/
int* safeMalloc(unsigned long size) {
	int* k = malloc(size * sizeof(int));
	if (k == NULL) {
		printf("Error during allocation\n");
		exit(-1);
	}
	return k;
}

/* utility function to free the memory */
void freeInteger(Integer *a) {
    free(a->digits);
}

/* make integer form a string */
void makeIntegerFromString(Integer *a, char digits[]) {
    unsigned long i = 0;
    /* store the sign */
	 if (digits[0] == '-') {
        a->sign = -1;
        i++;
    }else{
        a->sign = 1;
    }
    
    /* determine length */
    unsigned long k = i;
    for (i; digits[i] != '\0'; i++) {}
    
    /* allocate length */
    a->length = i-k;
	 a->digits = safeMalloc(a->length);
	 
	 /* store the digits */
    unsigned long j = a->length-1;
    for (i = k; digits[i] != '\0'; i++) {
		a->digits[j] = digits[i] - 48;
		--j;
    }
};

/* prints integer to stdout */
void printInteger(Integer a) {
    unsigned long i;
	 if (a.sign == -1) {
		printf("-");
	 }
    for (i = a.length; i > 0; --i) {
        printf("%d", a.digits[i-1]);
    }
}

/* a := a + b */
void addInteger(Integer *a, Integer b);

/* a := a - b */
void subInteger(Integer *a, Integer b);

/* a := a * b */
void mulInteger(Integer *a, Integer b);

/* a := a div b */
void divInteger(Integer *a, Integer b);


/* Implementations */

/* make integer form a string */
void makeIntegerFromString(Integer *a, char digits[]);

/* a := a + b */
void addInteger(Integer *a, Integer b) {
	unsigned long alen = a->length;
	unsigned long blen = b.length;
	
	/* check sign */	
	if (a->sign == 1 && b.sign == -1) {
		/* execute subFunction */
                subIneger(a, b);
		return;
	}
	if (a->sign == -1 && b.sign == 1) {
		/* execute subFunction swap a and b */
                subIneger(b, a);
		return;
	}
	/* for equal signs, use below */
	
	int carry = 0, temp;
	unsigned long i, min = MIN(alen, blen);
	for (i = 0; i < min; ++i) {
		temp = a->digits[i] + b.digits[i] + carry;
		a->digits[i] = temp % 10;
		carry = temp / 10;
	}
	
	/* blen > alen */
	if (blen > alen) {
		/* allocate more memory */
		int* digitsnew;
		digitsnew = safeMalloc(blen);
		/* copy digits over */
		for (i = 0; i < alen; ++i) {
			digitsnew[i] = a->digits[i];
		}
		/* old digits can be removed */
		free(a->digits);
		/* copy carry over */
		digitsnew[i] = b.digits[i] + carry;
		carry = 0;
		
		/* copy rest of digits over */
		for (i++; i < blen; ++i) {
			digitsnew[i] = b.digits[i];
		}
		/* finally replace digits */
		a->digits = digitsnew;
		a->length = blen;
		
	}else if (alen == blen && carry > 0) {
		/* more space is needed */
		int* digitsnew;
		digitsnew = safeMalloc(alen+1);
		for (i = 0; i < alen; ++i) {
			digitsnew[i] = a->digits[i];
		}
		digitsnew[i] = carry;
		free(a->digits);
		a->digits = digitsnew;
		(a->length)++;
		
	} else if ( carry > 0) {
		/* alen > blen */
		a->digits[i] = carry;
	}
}

/* a := a - b */
void subInteger(Integer *a, Integer b) {
	unsigned long alen = a->length;
	unsigned long blen = b.length;
	
	
}

/* a := a * b */
void mulInteger(Integer *a, Integer b);

/* a := a div b */
void divInteger(Integer *a, Integer b);


int main () {
	Integer a,b;
	makeIntegerFromString(&a, "555");
	makeIntegerFromString(&b, "2");
	printInteger(a);
	printf("\n");
	printInteger(b);
	printf("\n");
	
	addInteger(&a, b);
	printInteger(a);
	printf("\n");
	
	freeInteger(&a);
	freeInteger(&b);
	return 0;
}
