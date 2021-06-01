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
	
	double distance_totale;
	int nb_penalties;
	
}Interface;

double compute_employee_distance(Interface);

void remplir_agendas(Interface*);

void remove_creneau_agenda(int *, int *, int);

int check_compatibility(Interface *, int *, int);

void init_tableau_interfaces(Interface*);

void print_interfaces(Interface*);

int poids_interface(const Interface *);

int compute_penalty_interface(Interface);

#endif
