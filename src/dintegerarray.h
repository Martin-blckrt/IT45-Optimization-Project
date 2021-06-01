#ifndef DEF_DINTEGERARRAY
#define DEF_INTEGERARRAY

typedef struct {
    int* int_array;
    int size;
}IntegerArray;
 
void init_intarray(IntegerArray*);

void add_element_intarray(IntegerArray*, int);

void remove_element_intarray(IntegerArray*, int);

void clean_intarray(IntegerArray*);

#endif
