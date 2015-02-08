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
	unsigned long i;
	aCopy->digits = safeMalloc(a.length);
	for (i = 0; i < a.length; i++) {
		aCopy->digits[i] = a.digits[i];
	}
	aCopy->length = a.length;
	aCopy->sign = a.sign;
}

/* utility function to shallow copy Integers */
void shallowCopyInteger(Integer a, Integer *aCopy) {
	aCopy->digits = a.digits;
	aCopy->length = a.length;
	aCopy->sign = a.sign;
}

/* utility function to compare numbers */
int compareTo(Integer a, Integer b) {
	if (a.length > b.length) {
		return 1;
	} else if (b.length > a.length) {
		return -1;
	} else {
		unsigned long i;
		for (i = a.length - 1; i >= 0; i--) {
			if (a.digits[i] > b.digits[i]) {
				return 1;
			} else if (b.digits[i] > a.digits[i]) {
				return -1;
			}
		}
		return 0;
	}

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

	/* check if b > a */
	if (compareTo(b, *a) > 0) {
		/* deep copy b */
		Integer bCopy;
		deepCopyInteger(b, &bCopy);
		addInteger(&bCopy, *a);
		freeInteger(a);
		shallowCopyInteger(bCopy, a);
		return;
	}

	/* for equal signs and a >= b */
	int carry = 0, temp;
	unsigned long i;

	/* calculate sum */
	for (i = 0; i < blen; ++i) {
		temp = a->digits[i] + b.digits[i] + carry;
		a->digits[i] = temp % BASE;
		carry = temp / BASE;
	}

	/* copy the last carry */
	for (; carry != 0 && i < alen; ++i) {
		temp = a->digits[i] + carry;
		a->digits[i] = temp % BASE;
		carry = temp / BASE;
	}

	/* if last carry is overflowing a */
	if (carry > 0) {
		/* more space is needed */
		int *digitsnew;
		/* allocate more memory */
		digitsnew = safeMalloc(alen + 1);
		/* copy digits over */
		for (i = 0; i < alen; i++) {
			digitsnew[i] = a->digits[i];
		}
		/* copy the carry */
		digitsnew[i] = carry;
		/* free the old array */
		free(a->digits);
		/* put the new array in digits */
		a->digits = digitsnew;
		/* Make a length 1 larger*/
		(a->length)++;
	}
}

/* a := a - b */
void subInteger(Integer *a, Integer b) {
	unsigned long alen = a->length;
	unsigned long blen = b.length;

	/* check sign */
	if (a->sign + b.sign == 0) {
		/* execute subtract function */
		b.sign = a->sign;
		subInteger(a, b);
		return;
	}

	/* check if b > a */
	if (compareTo(b, *a) > 0) {
		/* deep copy b */
		Integer bCopy;
		deepCopyInteger(b, &bCopy);
		a->sign = -(a->sign);
		bCopy.sign = -(bCopy.sign);
		subInteger(&bCopy, *a);
		freeInteger(a);
		shallowCopyInteger(bCopy, a);
		a->sign = -(a->sign);
		return;
	}

	/* for equal signs and a >= b */
	int carry = 0, temp;
	unsigned long i;

	/* calculate sum */
	for (i = 0; i < blen; ++i) {
		temp = a->digits[i] - b.digits[i] + carry;
		a->digits[i] = (temp + BASE) % BASE;
		carry = (temp + BASE) / BASE - 1;
	}

	/* copy the last carry */
	for (; carry != 0 && i < alen; ++i) {
		temp = a->digits[i] + carry;
		a->digits[i] = (temp + BASE) % BASE;
		carry = (temp + BASE) / BASE - 1;
	}

	/* check how many zero's are at the end of a number*/
	for (i = 0; i < alen && a->digits[alen - i - 1] == 0; ++i);

	/* if the number is prepended by zeros */
	if (i > 0) {
		/* check for 0 or -0 and make it always positive */
		if (i == alen) {
			i--;
			a->sign = 1;
		}
		unsigned long j;
		/* more space is needed */
		int *digitsnew;
		/* allocate more memory */
		digitsnew = safeMalloc(alen - i);
		/* copy digits over */
		for (j = 0; j < alen - i; ++j) {
			digitsnew[j] = a->digits[j];
		}
		/* free the old array */
		free(a->digits);
		/* put the new array in digits */
		a->digits = digitsnew;
		/* Make a length 1 larger*/
		(a->length) -= i;
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
	low->length = MIN(split, largeInteger.length);
	low->digits = safeMalloc(low->length);
	for (i = 0; i < low->length; ++i) {
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
		for (i = 0; i < high->length; ++i) {
			high->digits[i] = largeInteger.digits[i + split];
		}
	}

}

/* a := a * BASE^k shift */
void shiftRight(Integer *a, unsigned long k) {
	unsigned long i;
	int *newdigits = safeMalloc(a->length + k);
	for (i = 0; i < k; ++i) {
		newdigits[i] = 0;
	}
	for (i = k; i < a->length; ++i) {
		newdigits[i] = a->digits[i];
	}
	free(a->digits);
	a->digits = newdigits;
}

/* recursive karatsuba */
Integer karatsuba(Integer a, Integer b) {
	unsigned long alen = a.length, blen = b.length, m, m2;

	Integer z0, z1, z2;
	
	/* base state of recursion */

	/* a < 10 */
	if (alen < 2) {
		simpleMul(&b, a.digits[0]);
		return b;
	}
	if (blen < 2) {
		simpleMul(&a, b.digits[0]);
		return a;
	}

	m = MAX(alen, blen);
	m2 = m / 2;

	/* declare all the integers! */
	Integer high1, low1, high2, low2;
	splitAt(&high1, &low1, a, m2);
	splitAt(&high2, &low2, b, m2);
	
	/* divide */
	z0 = karatsuba(low1, low2);
	z2 = karatsuba(high1, high2);
	
	addInteger(&low1,high1);
	addInteger(&low2,high2);
	/* the low Integers now contain the sums */
	z1 = karatsuba(low1, low2);
	
	/* now follows the z2 * 10^(2*m2) + ((z1-z2-z0)*10^(m2) + z0
	
	/* the z1 - z2 -z0 stored in the z1 */
	subInteger(&z1, z2);
	subInteger(&z1, z0);
	
	/* shift right for z1 and z2 */
	shiftRight(&z1, m2);
	shiftRight(&z2, m2 * 2);
	
	/* and conquer */
	addInteger(&z2, z1);
	addInteger(&z2, z0);
	
	/* free the temp integers */
	freeInteger(&high1);
	freeInteger(&low1);
	freeInteger(&high2);
	freeInteger(&low2);
	
	/* done */
	return z2;
}

/* a := a * b */
void mulInteger(Integer *a, Integer b) {
	int newsign = a->sign * b.sign;
	unsigned long i, alen = a->length;

	/* calculate multiplication, possibly with the wrong sign */
	*a = karatsuba(*a, b);
	/* check how many zero's are at the end of a number*/
	for (i = 0; i < alen && a->digits[alen - i - 1] == 0; ++i);

	/* if the number is zero */
	if (i == alen) {
		unsigned long j;
		i--;
		a->sign = 1;
		/* more space is needed */
		int *digitsnew;
		/* allocate more memory */
		digitsnew = safeMalloc(alen - i);
		/* copy digits over */
		for (j = 0; j < alen - i; ++j) {
			digitsnew[j] = a->digits[j];
		}
		/* free the old array */
		free(a->digits);
		/* put the new array in digits */
		a->digits = digitsnew;
		/* Make a length 1 larger*/
		(a->length) -= i;
	} else {
		a->sign = newsign;
	}

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


	makeIntegerFromString(&a, "2");
	makeIntegerFromString(&b, "4");
	printInteger(a);
	printf("\n");
	printInteger(b);
	printf("\n");
	mulInteger(&a, b);
	printInteger(a);
	printf("\n");

	freeInteger(&a);
	freeInteger(&b);
	return 0;
}
