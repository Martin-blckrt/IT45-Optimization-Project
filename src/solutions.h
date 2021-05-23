#include "instancegenerator/constants.h"
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
	IntegerArray formation;
	
} Interface;

void find_init_solution();

int compare_formations(const void *, const void *);

int compare_interfaces(const void *, const void *);

int poids_interface(const Interface*);

int check_compatibility(Interface*, int *, int);

double compute_distance(double, double, double, double);

double compute_employee_distance(int);

double compute_avg_distance();

double compute_standard_error(double);

double compute_fcorr(double);

void print_formation();

void print_interfaces();

void print_solution();
