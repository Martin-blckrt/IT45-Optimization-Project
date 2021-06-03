#ifndef DEF_DINTEGERARRAY
#define DEF_INTEGERARRAY

#include <stdio.h>

typedef struct {
    size_t size;
    int* int_array;
}IntegerArray;

void init_intarray(IntegerArray*);

void add_element_intarray(IntegerArray*, int);

void remove_element_intarray(IntegerArray*, int);

void clean_intarray(IntegerArray*);

#endif
