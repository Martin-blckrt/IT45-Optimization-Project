#include <stdio.h>
#include <stdlib.h>
#include "dintegerarray.h"

void init_intarray(IntegerArray* array)
{
    array->int_array = NULL;
	array->capacity = 0;
    array->size = 0;
    
}

void add_element_intarray(IntegerArray* a, int value)
{
	if(a->capacity == 0)
	{
		a->int_array = malloc(sizeof(int));
		a->capacity++;
		a->int_array[a->size++] = value;
		return;
	}
    
	if(a->size >= a->capacity)
	{
		a->capacity = a->capacity * 2;
		int* temp = malloc(a->capacity * sizeof(int));
		for(int i = 0; i < a->size; i++)
			temp[i] = a->int_array[i];
		free(a->int_array);
		a->int_array = temp;
	}
	a->int_array[a->size] = value;
	a->size++;
    
}

void remove_element_intarray(IntegerArray* a, int value)
{
    if(a->size>0)
    {
    	int i = 0;
    	while(a->int_array[i] != value && i < a->size)
    		i++;
    	for(i = i; i < a->size - 1; i++)
    		a->int_array[i] = a->int_array[i+1];
    	a->int_array[a->size - 1] = 0;
        a->size--;
    }

}

void clean_intarray(IntegerArray* a)
{
    a->int_array = NULL;
    free(a->int_array);
}
