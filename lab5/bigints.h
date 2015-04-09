#ifndef BIGINTS_H
#define BIGINTS_H
/*** stuff to implement ***/

/* use only base of 10^x (otherwise makeIntegerFromString and printInteger will break) */
#define BASE 65536 /* must become 65535 = 2 ^16 - 1*/ 
#define LOGBASE 6 /* must become 6 */

/* datastructure for infinite integers */
struct EGCLint {
	uint32_t *digits; /* the value for each of the digits, big endian */
	unsigned long length; /* maximum value is approx. 10^4294967295, 
	not infinite, but close enough. */
	int sign; /* wheter it is positive, of negative */
};
typedef struct EGCLint Integer;

/* make integer form a string */
void makeIntegerFromString(Integer *a, const char digits[]);

/* prints integer to stdout */
void printInteger(Integer a);

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

#endif //BIGINTS_H