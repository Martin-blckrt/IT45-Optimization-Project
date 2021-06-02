#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "btree.h"
#include "constants.h"

void add_child(Arbre *arbre, Solution *value, int side)
{
	if(arbre != NULL)
	{
		Arbre *child = NULL;
		if(side == 0)
			child = &((*arbre)->leftchild);
		else
			child = &((*arbre)->rightchild);
		(*child) = malloc(sizeof(Node));
		(*child)->leftchild = NULL;
		(*child)->rightchild = NULL;
		(*child)->solution = malloc(sizeof(*value));
		memcpy((*child)->solution, value, sizeof(*value));	
		/*for(int i = 0; i < NBR_INTERFACES; i++)
		{
			for(int j = 0; j < 6; j++)
				memcpy(&((*child)->solution->interface[i].formation[j].int_array), &(value->interface[i].formation[j].int_array), sizeof(value->interface[i].formation[j].int_array));
		}*/
	}
}

void delete_arbre(Arbre arbre)
{
	if(arbre == NULL)
		return;
	delete_arbre(arbre->leftchild);
	delete_arbre(arbre->rightchild);
	
	Interface *interface = arbre->solution->interface;
	for(int i = 0; i < NBR_INTERFACES; i++)
	{
		for(int j = 0; j < 6; i++)
			clean_intarray(&(interface[i].formation[j]));
	}
	free(arbre->solution);
	free(arbre->leftchild);
	free(arbre->rightchild);
	free(arbre);
}
				
void print_arbre(Arbre arbre)
{
	if(arbre == NULL)
		return;
	print_z(*(arbre->solution));
	printf("LEFT\n");
	print_arbre(arbre->leftchild);
	printf("FINLEFT\n");
	printf("RIGHT\n");
	print_arbre(arbre->rightchild);
	printf("FINRIGHT\n");
}
