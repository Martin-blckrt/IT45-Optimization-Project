#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "btree.h"
#include "constants.h"

//Ajoute un fils gauche ou droit à la racine arbre en fonction de la valeur de side
void add_child(Arbre *arbre, Solution value, int side)
{
	if(arbre != NULL)
	{
		Arbre *child = NULL;
		if(side == 0)
			child = &((*arbre)->leftchild);
		else
			child = &((*arbre)->rightchild);
		
		(*child) = malloc(sizeof(Node));
		(*child)->solution = NULL;
		(*child)->leftchild = NULL;
		(*child)->rightchild = NULL;
		
		//Association de la nouvelle feuille à une solution passée en paramètre (value)
		create_from_solution(&(*child)->solution, value);

	}
}

void delete_arbre(Arbre arbre)
{
	if(arbre == NULL)
	{
		return;
	}
	delete_arbre(arbre->leftchild);
	delete_arbre(arbre->rightchild);
	delete_solution(arbre->solution);
	free(arbre);

}

//Stock dans le tableau de solution pop le dernier étage de l'arbre binaire
int find_last_floor(Arbre arbre, Solution *pop, int index)
{
	//La génération de feuille étant systématique, l'absence de feuille gauche signifie l'absence de feuille droite, donc on ne teste que la feuille gauche
	if(arbre->leftchild == NULL)
	{
		//Duplication et stockage de la solution dans le tableau
		pop[index] = *(arbre->solution);
		duplicate_formations(pop[index].interface, arbre->solution->interface);
		index++;
		return index;
	}
	index = find_last_floor(arbre->leftchild, pop, index);
	index = find_last_floor(arbre->rightchild, pop, index);
	return index;

}

void print_arbre(Arbre arbre)
{
	if(arbre == NULL)
		return;
	print_solution(*(arbre->solution));
	print_arbre(arbre->leftchild);
	print_arbre(arbre->rightchild);
}
