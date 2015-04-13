#ifndef BIGINTS_H
#define BIGINTS_H
#include <stdint.h>
/*** stuff to implement ***/

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