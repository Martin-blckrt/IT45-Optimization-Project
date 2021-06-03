#include <stdio.h>
#include <stdlib.h>
#include "dintegerarray.h"

void init_intarray(IntegerArray* array)
{
    
    array->int_array = NULL;
    array->size = 0;
}

void add_element_intarray(IntegerArray* a, int value)
{
	int *temp = realloc(a->int_array, sizeof(int) * (a->size + 1));
	if(temp == NULL)
	{
		fprintf(stderr, "error");
		exit(EXIT_FAILURE);
	}
	a->int_array = temp;
	a->int_array[a->size] = value;
	a->size++;

}

void remove_element_intarray(IntegerArray* a, int value)
{
    if(a->size>0)
    {
    	int i = 0;
    	while(i < a->size && a->int_array[i] != value)
    		i++;
    	for(i = i; i < a->size - 1; i++)
    		a->int_array[i] = a->int_array[i+1];
    	if(i < a->size)
	{
		a->int_array[a->size - 1] = 0;
		a->size--;
	}
	
    }

}

void duplicate_intarrays(IntegerArray *array1, IntegerArray array2)
{
	init_intarray(array1);
	if(array2.size > 0)
	{
		array1->size = array2.size;
		array1->int_array = malloc(sizeof(int) * array2.size);
		for(int p = 0; p < array1->size; p++)
		{
			array1->int_array[p] =  array2.int_array[p];
		}
	}
}
void clean_intarray(IntegerArray* a)
{
	if(a->int_array != NULL)
	{
		free(a->int_array);
		a->int_array = NULL;
		a->size = 0;
	}

}
