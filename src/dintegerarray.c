#include <stdio.h>
#include <stdlib.h>
#include "dintegerarray.h"

//Initialise le pointeur à NULL et les champs de l'array
void init_intarray(IntegerArray* array)
{
    
    array->int_array = NULL;
    array->size = 0;
}

//Ajoute un élément en fin de tableau en réallouant l'espace mémoire à chaque changement de taille
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

//Enlève l'élément "valeur" du tableau, si celui-ci n'existe pas alors la fonction ne fait rien
void remove_element_intarray(IntegerArray* a, int value)
{
    if(a->size>0)
    {
    	int i = 0;
    	//Recherche de la valeur
    	while(i < a->size && a->int_array[i] != value)
    		i++;
    		
    	//Cas où la valeur ne se trouve pas dans le tableau
    	if(i >= a->size)
    		return;
    		
    	//Décalage du tableau vers la gauche
    	for(i = i; i < a->size - 1; i++)
    		a->int_array[i] = a->int_array[i+1];

	//redimensionnement
	a->int_array[a->size - 1] = 0;
	a->size--;
	
	
    }

}

//Créer un nouveau tableau dynamique à partir du tableau array2
void duplicate_intarrays(IntegerArray *array1, IntegerArray array2)
{
	//Initialisation du nouvel array
	init_intarray(array1);
	if(array2.size > 0)
	{
		//Attribution des champs
		array1->size = array2.size;
		
		//Attribution de la mémoire
		array1->int_array = malloc(sizeof(int) * array2.size);
		
		//Recopiage du tableau
		for(int p = 0; p < array1->size; p++)
		{
			array1->int_array[p] =  array2.int_array[p];
		}
	}
}

//Fonction de supression d'un array dynamique
void clean_intarray(IntegerArray* a)
{
	if(a->int_array != NULL)
	{
		free(a->int_array);
		a->int_array = NULL;
		a->size = 0;
	}

}
