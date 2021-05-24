#ifndef DEF_INTERFACE
#define DEF_INTERFACE

#include "constants.h"
#include "dintegerarray.h"

typedef struct
{
	int competence[2];
	int specialite[NBR_SPECIALITES];

//Tableau représentant l'agenda d'une interface, il est structuré de la manière suivante :
//- Le premier index correspond au jour de l'agenda
//- Le deuxième index correspond à l'heure du jour (allant de 0 à 13, représentant les heures de 6 à 19)
	int agenda[6][13];
	
	//L'agenda seul ne permet pas d'identifier les apprenants suivis par l'interface, ce tableau dynamique s'en charge 
	IntegerArray formation[6];
	
}Interface;

void remplir_agendas();

int check_compatibility(Interface *, int *, int);

void init_tableau_interfaces();

void print_interfaces();

int poids_interface(const Interface *);

#endif
