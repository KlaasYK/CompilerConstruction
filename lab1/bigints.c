#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(a,b) a<b?a:b

#define BASE 10

/* datastructure for infinite intgers */
struct EGCLint {
	int *digits; /* the value for each of the digits, big endian */
	unsigned long length; /* maximum value is approx. 10^4294967295, 
	not infinite, but close enough. */
	int sign; /* wheter it is positive, of negative */
};
typedef struct EGCLint Integer;

/* utility function to malloc the memory*/
int *safeMalloc(unsigned long size) {
	int *k = malloc(size * sizeof (int));
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
	} else {
		a->sign = 1;
	}

	/* determine length */
	unsigned long k = i;
	for (i; digits[i] != '\0'; i++) {
	}

	/* allocate length */
	a->length = i - k;
	a->digits = safeMalloc(a->length);

	/* store the digits */
	unsigned long j = a->length - 1;
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
void divInteger(Integer *a, Integer b);

/* a := a mod b */
void modInteger(Integer *a, Integer b);

/* a := a^b */
void powInteger(Integer *a, Integer b);

/* Implementations */

/* make integer form a string */
void makeIntegerFromString(Integer *a, char digits[]);

/* a := a + b */
void addInteger(Integer *a, Integer b) {
	unsigned long alen = a->length;
	unsigned long blen = b.length;

	/* check sign */
	if (a->sign + b.sign == 0) {
		/* execute subtract function */
		b.sign = a->sign;
		subInteger(a, b);
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
		for (; carry != 0; ++i) {
			digitsnew[i] = b.digits[i] + carry;
			carry = digitsnew[i] / 10;
			digitsnew[i] %= 10;
		}

		/* copy rest of digits over */
		for (; i < blen; ++i) {
			digitsnew[i] = b.digits[i];
		}
		/* finally replace digits */
		a->digits = digitsnew;
		a->length = blen;

	} else if (alen == blen && carry > 0) {
		/* more space is needed */
		int* digitsnew;
		digitsnew = safeMalloc(alen + 1);
		for (i = 0; i < alen; ++i) {
			digitsnew[i] = a->digits[i];
		}
		digitsnew[i] = carry;
		free(a->digits);
		a->digits = digitsnew;
		(a->length)++;

	} else if (carry > 0) {
		/* alen > blen */
		a->digits[i] = carry;
	}
}

/* a := a - b */
void subInteger(Integer *a, Integer b) {
	unsigned long alen = a->length;
	unsigned long blen = b.length;

	/* check sign */
	if (a->sign + b.sign == 0) {
		/* execute add function */
		b.sign = a->sign;
		addInteger(a, b);
		return;
	}

	/* for equal signs, use below */
	int carry = 0, temp;
	unsigned long i, min = MIN(alen, blen);
	for (i = 0; i < min; ++i) {
		temp = a->digits[i] - b.digits[i] + carry;
		a->digits[i] = (temp + 10) % 10;
		carry = (temp + 10) / 10 - 1;
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
		for (; carry != 0; ++i) {
			digitsnew[i] = b.digits[i] + carry;
			carry = digitsnew[i] / 10;
			digitsnew[i] %= 10;
		}

		/* copy rest of digits over */
		for (; i < blen; ++i) {
			digitsnew[i] = b.digits[i];
		}
		/* finally replace digits */
		a->digits = digitsnew;
		a->length = blen;

	} else if (alen == blen && carry > 0) {
		/* more space is needed */
		int* digitsnew;
		digitsnew = safeMalloc(alen + 1);
		for (i = 0; i < alen; ++i) {
			digitsnew[i] = a->digits[i];
		}
		digitsnew[i] = carry;
		free(a->digits);
		a->digits = digitsnew;
		(a->length)++;

	} else if (carry > 0) {
		/* alen > blen */
		a->digits[i] = carry;
	}

}


/* a := a * b where b < 10 */
void simpleMul(Integer *a, int b ) {
	int carry = 0, val;
	unsigned long i, alen = a->length;
	/* multiply the whole "string" with the single digit */
	for (i = 0; i < alen; ++i) {
		val = a->digits[i] * b + carry;
		carry = val / BASE;
		a->digits[i] = val % BASE;
	}
	
	/* allocate an extra digit, add carry */
	if (carry > 0) {
		int *newdigits = safeMalloc(alen + 1);
		for (i = 0; i < alen; ++i) {
			newdigits[i] = a->digits[i];
		}
		newdigits[i] = carry;
		a->length = alen + 1;
		free(a->digits);
		a->digits = newdigits;
	}
	
}

/* recursive karatsuba */
Integer karatsuba(Integer a, Integer b) {
	unsigned long alen = a.length, blen = b.length;
	Integer c;
	
	/* a < 10 */
	if (alen < 2) {
		simpleMul(&b,a);
		return b;
	}
	
	
}



/* a := a * b */
void mulInteger(Integer *a, Integer b) {
	unsigned long alen = a->length, blen = b.length;

}

/* a := a div b */
void divInteger(Integer *a, Integer b) {

}

/* a := a mod b */
void modInteger(Integer *a, Integer b) {

}

/* a := a^b */
void powInteger(Integer *a, Integer b) {

}


int main() {
	Integer a, b;
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
