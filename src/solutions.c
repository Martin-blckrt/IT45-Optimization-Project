#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solutions.h"


extern int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES];
extern int competences_interfaces[NBR_INTERFACES][2];
extern int formation[NBR_FORMATIONS][6];
extern float coord[NBR_NODES][2];
double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];

double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];

Interface infos_interface[NBR_INTERFACES];

void print_distances()
{
	for(int i = 0; i < NBR_SPECIALITES + 1; i++)
	{
		printf("Depart %d : \n", i);
		for(int j = 0; j < NBR_SPECIALITES + 1; j++)
		{
			printf("Arrivee %d : %f\n", j, distances[i][j]);
		}
		printf("\n");
	}
}

void init_distance_matrix()
{
	for(int i = 0; i < NBR_SPECIALITES + 1; i++)
	{
		for(int j = 0; j < NBR_SPECIALITES + 1;j++)
		{
			if(i == j)
				distances[i][j] = 0;
			else
				distances[i][j] = compute_distance(coord[i][0], coord[i][1], coord[j][0], coord[j][1]);
		}
	}
	print_distances();
}

double compute_distance(double xa, double ya, double xb, double yb)
{
    double distance = 0;
    distance = pow(xa-xb, 2) + pow(ya-yb, 2);
    distance = sqrt(distance);
    return distance;
}

int compare_formations(const void *n1, const void *n2)
{

	const int *a = n1;
	const int *b = n2;
	
	if(a[5] - a[4] > b[5] - b[4])
		return -1;
	else
		return 1;
}


int compare_interfaces(const void *n1, const void *n2)
{
	const Interface *a = n1;
	const Interface *b = n2;
	
	if(poids_interface(a) > poids_interface(b))
		return -1;
	else
		return 1;
}

int compare_agenda(const void *n1, const void *n2)
{
	const int *a = (const int*)n1;
	const int *b = (const int*)n2;
	
	if(formation[*a][4] < formation[*b][4])
		return 1;
	else
		return -1;
}

void init_tableau_interfaces()
{

	for(int i = 0; i < NBR_INTERFACES; i++)
	{
		for(int j = 0; j < 2; j++)
			infos_interface[i].competence[j] = competences_interfaces[i][j];
		for(int j = 0; j < NBR_SPECIALITES; j++)
			infos_interface[i].specialite[j] = specialite_interfaces[i][j];
		for(int j = 0; j < 6; j++)
		{
			init_intarray(&(infos_interface[i].formation[j]), 1);
			for(int p = 0; p < 13; p++)
				infos_interface[i].agenda[j][p] = 0;
		}
	
		
	}
}

//Calcule le poids d'une interface afin d'avoir les interfaces ayant beaucoup de spécialités en haut de liste et les interfaces avec double compétences
//en fin de liste
int poids_interface(const Interface *interface)
{
    int poids = 0;
    if(interface->competence[0] == 1 && interface->competence[1] == 1)
        poids = -NBR_SPECIALITES - 1;
    for(int i = 0; i < NBR_SPECIALITES; i++)
    	poids += interface->specialite[i];
    return poids;

}


void find_init_solution()
{
    init_distance_matrix();
    init_tableau_interfaces();

    qsort(formation, NBR_FORMATIONS, sizeof(formation[0]), compare_formations);
    qsort(infos_interface, NBR_INTERFACES, sizeof(infos_interface[0]), compare_interfaces);
    //Affichage tableau formation et interfaces pour débuggage
    printf("\n*********************FORMATIONS****************\n");
    print_formation();
    printf("\n**********************INTERFACES************************\n");
    print_interfaces();

    //On cherche une solution en faisant rentrer le plus de formations dans les premieres interfaces
    for(int i = 0; i < NBR_FORMATIONS; i++)
    {
        int temps_creneau = formation[i][5] - formation[i][4]; //Durée d'une formation
	int jour = formation[i][3] - 1;
        //On recherche la première interface pouvant prendre la formation, si on arrive au bout du tableau des interfaces sans avoir trouvé
        //d'interface valide, alors l'algorithme n'est pas capable de trouver de solution initiale valide
        int p = 0;
        while(check_compatibility(&(infos_interface[p]), formation[i], temps_creneau) == -1 && p < NBR_FORMATIONS)
            p++;

        if(p >= NBR_FORMATIONS)
        {
            printf("Impossible d'assigner un des creneaux");
            exit(EXIT_FAILURE);
        }

        add_element_intarray(&(infos_interface[p].formation[jour]), formation[i][0]);

    }
    
    for(int p = 0; p < NBR_INTERFACES; p++)
    {
	    for(int i = 0; i < 6; i++)
	    {
	    	qsort(infos_interface[p].formation[i].int_array, infos_interface[p].formation[i].size, sizeof(int), compare_agenda);
	    }
     }

    printf("\n*****************************AGENDA*************************\n");
    print_solution();

}


//Vérifie si l'interface à l'index index peut prendre le créneau passé en paramètre
//Elle le peut si :
//- Elle a la compétence requise (codage LPC ou langage des signes)
//- Elle n'a pas déjà de formation prévu à cette horaire
//- L'amplitude de sa journée ne dépasse pas 12h
//- Son nombre d'heures hebdomadaire ne dépasse pas 35h
//- Son nombre d'heures quotidiennes ne dépasse pas 8h
int check_compatibility(Interface *interface, int *creneau, int temps_creneau)
{
    //Verification compatibilité compétence
    if(creneau[2] == 0 && interface->competence[0] == 0)
        return -1;


    int jour_sem = creneau[3] - 1; //Jour de la formation passée en paramètre
    int map = creneau[4] - 6; //Le tableau agenda allant de 0 à 13, il faut mapper les heures de 6 à 19 pour qu'elles correspondent aux index du tableau

    //Verification de la compatibilité d'emploi du temps
    for(int i = 0; i < temps_creneau; i++)
    {
        if(interface->agenda[jour_sem][map + i] == 1) //Si il y a déjà un 1 dans le tableau agenda, alors cela signifie que l'heure est déjà prise
            return -1;
    }


    //On insere le nouveau creneau dans l'agenda de l'interface afin d'ensuite effectuer les tests de vérification
    int temp[13];
    for(int i = 0; i < 13; i++)
        temp[i] = interface->agenda[jour_sem][i];
    for(int i = 0; i < temps_creneau; i++)
        interface->agenda[jour_sem][map + i] = 1;

    //Verification de l'amplitude de la journée (12h maximum entre la première et dernière heure de travail)
    int p = 0;
    int premiere_heure = 0;
    
    while(p < 13 && interface->agenda[jour_sem][p] == 0)
    	p++;
    	
    if(p < 13)
    {
        premiere_heure = interface->agenda[jour_sem][p];
        int derniere_heure = 0;
        int p = 12;
        while(interface->agenda[jour_sem][p] == 0)
            p--;
        if(derniere_heure - premiere_heure > 12)
        {
            for(int i = 0; i < 13; i++)
            {
                interface->agenda[jour_sem][i] = temp[i];

            }
            return -1;
        }

    }

    //Verification du nombre d'heures de la journée
    int heures_journalieres = 0;
    for(int i = 0; i < 13; i++)
        heures_journalieres += interface->agenda[jour_sem][i];

    if(heures_journalieres > 8)
    {
        for(int i = 0; i < 13; i++)
        {
            interface->agenda[jour_sem][i] = temp[i];

        }
        return -1;
    }

    //Verification heures hebdomadaires
    int heures_hebdomadaires = 0;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            heures_hebdomadaires += interface->agenda[i][j];
        }
    }
    if(heures_hebdomadaires > 35)
    {
        for(int i = 0; i < 13; i++)
        {
            interface->agenda[jour_sem][i] = temp[i];

        }
        return -1;
    }

    for(int i = 0; i < temps_creneau; i++)
        {
            interface->agenda[jour_sem][creneau[4] - 6 + i] = 1;
        }

    return 0;
}




double compute_employee_distance(int i)
{
    Interface interface = infos_interface[i];
    IntegerArray* jour_formation = interface.formation;
    double distance = 0;
    for(int k = 0; k < 6; k++)
    {
    	if(jour_formation[k].size != 0)
    	{
    		
    		distance += distances[0][formation[jour_formation[k].int_array[0]][1]];
    		int j = 0;
    		for(j = 1; j < jour_formation[k].size - 2; j++)
    			distance += distances[j][formation[jour_formation[k].int_array[j+1]][1]];
    			
    		distance += distances[formation[jour_formation[k].int_array[j]][1]][0];
    	}
    }
    
    return distance;
}
/*
double compute_avg_distance()
{
    double total = 0;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
        total += compute_employee_distance(i);
    }
    total = total / NBR_INTERFACES;
    return total;
}

double compute_standard_error(double avg)
{
    double total = 0;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
        double current = 0, temp = 0;
        current = compute_employee_distance(i);
        temp = current - avg;
        total += pow(temp, 2);
    }
    total = total / NBR_INTERFACES;
    total = sqrt(total);
    return total;
}

double compute_fcorr(double avg)
{
    double total = 0;
    total = avg * NBR_INTERFACES;
    total = total / NBR_FORMATIONS;
    return total;
}

double compute_penalties()
{
    double total = 0;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
        Interface interface = infos_interface[i];
        int* formation_interface = interface.formation.int_array;
        int nb_formations = interface.formation.size;
        for (int index = 0; index < nb_formations; index++)
        {
            if (interface.specialite[formation[formation_interface[index]][1]] != 1)
            {
                total += 1;
            }
        }
    }
    return total;
}

double compute_min_z()
{
    double total = 0, avg = 0, std = 0, fcorr = 0, penalty = 0;
    avg = compute_avg_distance();
    std = compute_standard_error(avg);
    fcorr = compute_fcorr(avg);
    penalty = compute_penalties();
    total = 0.5 * (avg + std) + 0.5 * fcorr * penalty;
    return total;
<<<<<<< HEAD
}*/


void print_formation()
{
    for(int i = 0; i < NBR_FORMATIONS; i++)
    {
        printf("\nApprenant %d : \n", formation[i][0]);
        printf("Specialite : %d\n", formation[i][1]);
        printf("Competence requise : %d\n", formation[i][2]);
        printf("Jour de la formation : %d\n", formation[i][3]);
        printf("Heure de debut de la formation : %d\n", formation[i][4]);
        printf("Heure de fin de la formation : %d\n",formation[i][5]);
    }
}



void print_interfaces()
{
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        printf("\nInterface %d : \nCompetences : %d %d\nPoids : %d\nSpecialites : ", i, infos_interface[i].competence[0], infos_interface[i].competence[1], poids_interface(&infos_interface[i]));
        for(int j = 0; j < NBR_SPECIALITES; j++)
        {
        	printf("%d ", infos_interface[i].specialite[j]);
        	
        }
        printf("\n\n");
     }
}


			
void print_solution()
{
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        printf("\nInterface %d :\n", i);
        for(int j = 0; j < 6; j++)
        {
            printf("Jour %d : ", j + 1);
            for(int p = 0; p < 13; p++)
            {
                printf("%d ", infos_interface[i].agenda[j][p]);
            }
            for(int p = 0; p < infos_interface[i].formation[j].size; p++)
            	printf(" %d", infos_interface[i].formation[j].int_array[p]);
            printf("\n");
        }

        printf("distance parcourue : %f", compute_employee_distance(i));
    }
    //printf("\nz is  : %f\n", compute_min_z());
}
