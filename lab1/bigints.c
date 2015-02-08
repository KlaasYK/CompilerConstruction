#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(a,b) a<b?a:b
#define MAX(a,b) a<b?b:a

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

/* utility function to deep copy Integers*/
void deepCopyInteger(Integer a, Integer *aCopy) {
	aCopy->digits = safeMalloc(a.length);
	for (int i = 0; i < a.length; i++) {
		aCopy->digits[i] = a.digits[i];
	}
	aCopy->length = a.length;
	aCopy->sign = a.sign;
}

void shallowCopyInteger(Integer a, Integer *aCopy) {
	aCopy->digits = a.digits;
	aCopy->length = a.length;
	aCopy->sign = a.sign;
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
	int val;
	if (a.sign == -1) {
		printf("-");
	}
	for (i = a.length; i > 0; --i) {
		val = a.digits[i - 1];
		if (val >= BASE || val < 0) {
			/* print error */
			printf("!(%d)!", val);
		} else {
			printf("%d", val);
		}
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

	/* check if blen > alen*/
	if (blen > alen) {
		/* deep copy b */
		Integer bCopy;
		deepCopyInteger(b, &bCopy);
		addInteger(&bCopy, *a);
		freeInteger(a);
		shallowCopyInteger(bCopy, a);
		return;
	}

	/* for equal signs and alen >= blen */
	int carry = 0, temp;
	unsigned long i, min = MIN(alen, blen);
	for (i = 0; i < min; ++i) {
		temp = a->digits[i] + b.digits[i] + carry;
		a->digits[i] = temp % 10;
		carry = temp / 10;
	}

	if (alen == blen && carry > 0) {
		/* more space is needed */
		int *digitsnew;
		/* allocate more memory */
		digitsnew = safeMalloc(alen + 1);
		/* copy digits over */
		for (i = 0; i < alen; i++) {
			digitsnew[i] = a->digits[i];
		}
		/* copy the carry */
		for (; carry != 0 && i < blen; ++i) {
			digitsnew[i] = b.digits[i] + carry;
			carry = digitsnew[i] / 10;
			digitsnew[i] %= 10;
		}
		/* free the old array */
		free(a->digits);
		/* put the new array in digits */
		a->digits = digitsnew;
		/* Make a length 1 larger*/
		(a->length)++;
	}
	if (carry > 0) {
		/* fix carry */
		printf("%d", i);
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
		int *digitsnew;
		digitsnew = safeMalloc(blen);
		/* copy digits over */
		for (i = 0; i < alen; ++i) {
			digitsnew[i] = a->digits[i];
		}
		/* old digits can be removed */
		free(a->digits);
		/* copy carry over */
		for (; carry != 0 && i < blen; ++i) {
			digitsnew[i] = b.digits[i] + carry;
			carry = digitsnew[i] / 10;
			digitsnew[i] %= 10;
		}
		if (i == blen && carry != 0) {
			/* if there is carry for the last digit create a new array of the right length*/
			int *temp = safeMalloc(blen + 1);
			blen++;
			int j;
			/* copy values to the new array*/
			for (j = 0; j < blen - 1; ++j) {
				temp[j] = a->digits[j];
			}
			/* copy the carry */
			temp[j] = carry;
			/* free the old array*/
			free(digitsnew);
			/* put the new array in digitsnew*/
			digitsnew = temp;
		} else {
			/* copy rest of digits over */
			for (; i < blen; ++i) {
				digitsnew[i] = b.digits[i];
			}
		}
		/* finally replace digits */
		a->digits = digitsnew;
		a->length = blen;

	} else if (alen == blen && carry > 0) {
		/* more space is needed */
		int *digitsnew;
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
void simpleMul(Integer *a, int b) {
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

/* splits at split moving it to 2 other integers, deep copies */
void splitAt(Integer *high, Integer *low, Integer largeInteger, unsigned long split) {
	unsigned long i;
	
	/* make sure the right amount of low digits is passed */
	low->length = MIN(split,largeInteger.length);
	low->digits = safeMalloc(low->length);
	for (i=0; i < low->length; ++i) {
		low->digits[i] = largeInteger.digits[i];
	}
	
	/* high digits */
	if (largeInteger.length < split) {
		high->length = 1l;
		high->digits = safeMalloc(high->length);
		high->digits[0] = 0;
	} else {
		high->length = largeInteger.length - split;
		high->digits = safeMalloc(high->length);
		for(i=0; i < high->length; ++i) {
			high->digits[i] = largeInteger.digits[i+split];
		}
	}
	
}

/* recursive karatsuba */
Integer karatsuba(Integer a, Integer b) {
	unsigned long alen = a.length, blen = b.length,m,m2;

	/* base state */
	/* a < 10 */
	if (alen < 2) {
		simpleMul(&b, a.digits[0]);
		return b;
	}
	if (blen < 2) {
		simpleMul(&a, b.digits[0]);
		return a;
	}
	
	m = MAX(alen,blen);
	m2 = m/2;
	
	/* declare all the integers! */ 
	Integer high1, low1, high2, low2;
	
	
	
	/* free the temp integers */
	freeInteger(&high1);
	freeInteger(&low1);
	freeInteger(&high2);
	freeInteger(&low2);

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
	makeIntegerFromString(&a, "999");
	makeIntegerFromString(&b, "1");
	printInteger(a);
	printf("\n");
	printInteger(b);
	printf("\n");

	addInteger(&a, b);
	printInteger(a);
	printf("\n");

	freeInteger(&a);
	freeInteger(&b);
	
	
	Integer high, low;
	makeIntegerFromString(&a, "2542");
	makeIntegerFromString(&b, "4");
	printInteger(a);
	printf("\n");
	printInteger(b);
	printf("\n");
	
	splitAt(&high, &low, a, 5l);
	printInteger(high);
	printf("\n");
	printInteger(low);
	printf("\n");

	freeInteger(&a);
	freeInteger(&b);
	return 0;
}
