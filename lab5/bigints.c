#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bigints.h"

#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a<b?b:a)

/*** utility functions ***/

/* utility function to malloc the memory*/
uint32_t *safeMalloc(unsigned long size) {
	uint32_t *k = malloc(size * sizeof (uint32_t));
	if (k == NULL) {
		printf("Error during allocation\n");
		exit(-1);
	}
	return k;
}

/* utility function to calloc the memory*/
uint32_t *safeCalloc(unsigned long size) {
	uint32_t *k = calloc(size, sizeof (uint32_t));
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
	//printf("test length:\n");
	if (a.length > b.length) {
		//printf(" a longer then b\n");
		return 1;
	} else if (b.length > a.length) {
		//printf(" b longer then a\n");
		return -1;
	} else {
		//printf(" a and b of equal length, test number:\n");
		unsigned long i;
		for (i = a.length - 1; i + 1 > 0; i--) {
			if (a.digits[i] > b.digits[i]) {
				//printf("  a larger then b\n");
				return 1;
			} else if (b.digits[i] > a.digits[i]) {
				//printf("  b larger then a\n");
				return -1;
			}
		}
		//printf("  a and b equally large\n");
		return 0;
	}

}

/* Implementations */

/* function to convert the value to another base */
void addValueInBase(uint32_t *digits, unsigned long length, uint32_t value, int srcBase, int dstBase) {
	uint32_t temp, carry = value;
	unsigned long i;

	for (i = 0; i < length; ++i) {
		temp = digits[i] * srcBase + carry;
		digits[i] = temp % dstBase;
		carry = temp / dstBase;
	}
}

void makeIntegerFromString(Integer *a, const char *digits) {
	unsigned long signCorrection = 0, strLength, i, j, k, l;
	/* store the sign */
	if (digits[0] == '-') {
		a->sign = -1;
		signCorrection++;
	} else {
		a->sign = 1;
	}

	a->length = strlen(digits) - signCorrection;
	/* use calloc here to make sure all are zeros */
	a->digits = safeCalloc(a->length);

	for (i = signCorrection; i < a->length + signCorrection; ++i) {
		addValueInBase(a->digits, a->length, digits[i] - 48, 10, BASE);
	}

	/* remove the zeros form the end */
	for (i = a->length - 1; i + 1 >= 1; --i) {
		if (a->digits[i] > 0) {
			break;
		}
	}
	/* only zeros */
	if (i + 1 == 0) {
		a->length = 1;
	} else {
		a->length = i + 1;
	}
	uint32_t *newdigits = safeMalloc(a->length);
	for (i = 0; i < a->length; ++i) {
		newdigits[i] = a->digits[i];
	}
	free(a->digits);
	a->digits = newdigits;
}

char *makeStringFromInteger(Integer a) {
	unsigned long i;
	char *rstring;
	int negative = 0;

	uint32_t val;
	if (a.sign == -1) {
		//printf("-");
		negative = 1;
	}
	uint32_t *printdigits = safeCalloc(LOGBASE * a.length);
	for (i = a.length - 1; i + 1 >= 1; --i) {
		addValueInBase(printdigits, LOGBASE * a.length, a.digits[i], BASE, 10);
	}

	/* remove the zeros form the end */
	for (i = LOGBASE * a.length - 1; i + 1 >= 1; --i) {
		if (printdigits[i] > 0) {
			break;
		}
	}

	/* print 0 */
	if (i + 1 == 0) {
		rstring = malloc(2 * sizeof (char));
		sprintf(rstring, "0");

	} else {
		unsigned long length = i;
		rstring = malloc((i + negative + 1) * sizeof(char));
		if (negative) {
			sprintf(rstring, "-");
		}

		for (i; i + 1 >= 1; --i) {
			sprintf(rstring + negative + (length - i), "%u", printdigits[i]);
		}
	}

	free(printdigits);
	return rstring;
}

void printInteger(Integer a) {
	char *str = makeStringFromInteger(a);
	printf("%s", str);
	free(str);
}

/* a := b */
void setInteger(Integer *a, Integer b){
	deepCopyInteger(b, a);
}

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
	uint32_t carry = 0, temp;
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
		uint32_t *digitsnew;
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
		addInteger(a, b);
		return;
	}

	/* check if b > a */
	if (compareTo(b, *a) > 0) {
		/* deep copy b */
		Integer bCopy;
		deepCopyInteger(b, &bCopy);
		subInteger(&bCopy, *a);
		freeInteger(a);
		shallowCopyInteger(bCopy, a);
		a->sign = -(a->sign);
		return;
	}

	/* for equal signs and a >= b */
	uint32_t carry = 0, temp;
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
		uint32_t *digitsnew;
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

/* a := a * b where b <= 10 */
void simpleMul(Integer *a, Integer b) {
	uint32_t carry = 0, val, val2;
	unsigned long i, alen = a->length;
	/* multiply the whole "string" with the single digit */
	for (i = 0; i < alen; ++i) {
		val2 = a->digits[i];
		val = val2 * b.digits[0] + carry;
		carry = val / BASE;
		a->digits[i] = val % BASE;
	}

	/* allocate an extra digit, add carry */
	if (carry > 0) {
		uint32_t *newdigits = safeMalloc(alen + 1);
		for (i = 0; i < alen; ++i) {
			newdigits[i] = a->digits[i];
		}
		newdigits[i] = carry;
		a->length = alen + 1;
		free(a->digits);
		a->digits = newdigits;
	}
	a->sign = a->sign * b.sign;
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
	low->sign = largeInteger.sign;

	/* high digits */
	if (largeInteger.length < split) {
		high->length = 1;
		high->digits = safeMalloc(high->length);
		high->digits[0] = 0;
		high->sign = 1;
	} else {
		high->length = largeInteger.length - split;

		if (high->length == 0) {
			/* multiply small with very large numer */
			makeIntegerFromString(high, "0");
		} else {
			high->digits = safeMalloc(high->length);
			for (i = 0; i < high->length; ++i) {
				high->digits[i] = largeInteger.digits[i + split];
			}
		}
		high->sign = largeInteger.sign;
	}

}

/* a := a * BASE^k shift (makes Integer smaller (divide)) */
void shiftLeft(Integer *a, unsigned long k) {
	unsigned long i;
	uint32_t *newdigits = safeMalloc(a->length - k);
	for (i = k; i < a->length; ++i) {
		newdigits[i - k] = a->digits[i];
	}
	free(a->digits);
	a->digits = newdigits;
	a->length = a->length - k;
}

/* a := a * BASE^k shift (makes Intger larger (multiply) */
void shiftRight(Integer *a, unsigned long k) {
	unsigned long i;
	uint32_t *newdigits = safeMalloc(a->length + k);
	for (i = 0; i < k; ++i) {
		newdigits[i] = 0;
	}
	for (i = k; i < k + a->length; ++i) {
		newdigits[i] = a->digits[i - k];
	}
	free(a->digits);
	a->digits = newdigits;
	a->length = a->length + k;
}

/* recursive karatsuba */
Integer karatsuba(Integer a, Integer b) {
	unsigned long alen = a.length, blen = b.length, m, m2;

	Integer z0, z1, z2, returnInt;

	/* base state of recursion */

	/* a < 10 */
	if (alen < 2) {
		deepCopyInteger(b, &returnInt);
		simpleMul(&returnInt, a);
		return returnInt;
	}
	if (blen < 2) {
		deepCopyInteger(a, &returnInt);
		simpleMul(&returnInt, b);
		return returnInt;
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

	addInteger(&low1, high1);
	addInteger(&low2, high2);
	/* the low Integers now contain the sums */
	z1 = karatsuba(low1, low2);

	/* now follows the z2 * 10^(2*m2) + ((z1-z2-z0)*10^(m2) + z0 */

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
	deepCopyInteger(z2, &returnInt);

	freeInteger(&z0);
	freeInteger(&z1);
	freeInteger(&z2);

	return returnInt;
}

/* a := a * b */
void mulInteger(Integer *a, Integer b) {
	int newsign = a->sign * b.sign;
	Integer c;
	/* calculate multiplication, possibly with the wrong sign */
	c = karatsuba(*a, b);
	freeInteger(a);
	shallowCopyInteger(c, a);
	/* check how many zero's are at the end of a number*/
	unsigned long i, alen = a->length;
	for (i = 0; i < alen && a->digits[alen - i - 1] == 0; ++i);

	/* if the number is zero */
	if (i == alen) {
		unsigned long j;
		i--;
		a->sign = 1;
		/* more space is needed */
		uint32_t *digitsnew;
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
void divInteger(Integer *n, Integer d) {
	/* check for d = 0  => error!*/
	unsigned long shifts = 0;
	Integer resultInt, currentDivisor, one;

	if (d.length == 1 && d.digits[0] == 0) {
		printf("Division by zero: ");
		return;
	}

	/* check for d > *n  => 0*/
	if (compareTo(*n, d) < 0) {
		freeInteger(n);
		makeIntegerFromString(n, "0");
		return;
	}

	makeIntegerFromString(&resultInt, "0");
	makeIntegerFromString(&one, "1");

	deepCopyInteger(d, &currentDivisor);

	while (compareTo(*n, currentDivisor) >= 0) {
		shiftRight(&currentDivisor, 1);
		shifts++;
	}

	shifts--;
	shiftLeft(&currentDivisor, 1);

	while (shifts + 1 >= 1) {

		while (!(compareTo(*n, currentDivisor) < 0)) {
			subInteger(n, currentDivisor);
			addInteger(&resultInt, one);
		}

		shiftLeft(&currentDivisor, 1);
		shiftRight(&resultInt, 1);
		shifts--;
	}

	shiftLeft(&resultInt, 1);

	freeInteger(n);
	shallowCopyInteger(resultInt, n);

	freeInteger(&one);
	freeInteger(&currentDivisor);
}

/* a := a mod b */
void modInteger(Integer *n, Integer d) {
	/* check for d = 0  => error!*/
	unsigned long shifts = 0;
	Integer currentDivisor;

	if (d.length == 1 && d.digits[0] == 0) {
		printf("Division by zero: ");
		return;
	}

	/* check for d > *n  => *n */
	if (compareTo(*n, d) < 0) {
		return;
	}

	deepCopyInteger(d, &currentDivisor);

	while (compareTo(*n, currentDivisor) >= 0) {
		shiftRight(&currentDivisor, 1);
		shifts++;
	}

	shifts--;
	shiftLeft(&currentDivisor, 1);

	while (shifts + 1 >= 1) {

		while (!(compareTo(*n, currentDivisor) < 0)) {
			subInteger(n, currentDivisor);
		}

		shiftLeft(&currentDivisor, 1);
		shifts--;
	}

	freeInteger(&currentDivisor);
}

/* a := a^b */
void powInteger(Integer *base, Integer exponent) {
	Integer result, zero, one, two, expCopy;
	makeIntegerFromString(&zero, "0");
	if (exponent.sign == -1) {
		freeInteger(base);
		shallowCopyInteger(zero, base);
	} else {
		makeIntegerFromString(&one, "1");
		if (compareTo(exponent, zero) == 0) {
			freeInteger(base);
			shallowCopyInteger(one, base);
		} else {
			makeIntegerFromString(&result, "1");
			makeIntegerFromString(&two, "2");
			deepCopyInteger(exponent, &expCopy);
			while (compareTo(expCopy, one) != 0) {
				if (expCopy.digits[0] % 2 == 1) {
					mulInteger(&result, *base);
					/* implicit exponent - 1 */
				}

				divInteger(&expCopy, two);
				mulInteger(base, *base);
			}
			mulInteger(&result, *base);
			freeInteger(base);
			shallowCopyInteger(result, base);
			freeInteger(&expCopy);
			freeInteger(&one);
			freeInteger(&two);
		}

		freeInteger(&zero);
	}
}
