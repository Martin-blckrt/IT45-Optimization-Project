#include <stdio.h>
#include <stdlib.h>
#include "dintegerarray.h"


IntegerArray init_intarray(int initSize)
{
    IntegerArray array;
    array.int_array = (int*)malloc(sizeof(int) * initSize);
    array.capacity = initSize;
    array.size = 0;
    return array;
}

void add_element_intarray(IntegerArray* a, int value)
{
    if(a != NULL)
    {
        if(a->size + 1 > a->capacity)
        {
            a->int_array = realloc(a->int_array, (a->capacity*=2) * sizeof(int));
        }
        a->size++;
        a->int_array[a->size-1] = value;
    }
}

void remove_element_intarray(IntegerArray* a)
{
    if(a->size>0)
    {
        a->int_array[a->size - 1] = 0;
        a->size--;
        a->int_array = realloc(a->int_array, a->size * sizeof(int));
    }
    else
    {
        a->int_array = NULL;
        free(a->int_array);
    }
}

void clean_intarray(IntegerArray* a)
{
    while(a->int_array != NULL)
    {
        remove_element_intarray(&*a);
    }
}
