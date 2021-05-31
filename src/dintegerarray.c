#include <stdio.h>
#include <stdlib.h>
#include "dintegerarray.h"

void init_intarray(IntegerArray* array, int initSize)
{
    array->int_array = (int*)malloc(sizeof(int) * initSize);
    array->capacity = initSize;
    array->size = 0;
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

void remove_element_intarray(IntegerArray* a, int value)
{
    if(a->size>0)
    {
    	int i = 0;
    	while(a->int_array[i] != value)
    		i++;
    	for(i = i; i < a->size - 1; i++)
    		a->int_array[i] = a->int_array[i+1];
        //a->int_array[a->size - 1] = 0;
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
        remove_element_intarray(a, a->int_array[0]);
    }
}
