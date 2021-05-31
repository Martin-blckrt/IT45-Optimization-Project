#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solutions.h"
#include "tri.h"
#include "interface.h"


extern int formation[NBR_FORMATIONS][6];
extern float coord[NBR_NODES][2];
extern double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];

Solution solution_initiale;

int get_champs_formation(int index_formation, int index_champ)
{
	return formation[index_formation][index_champ];
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

void solve()
{
	find_init_solution();
	improve_solution(&solution_initiale);
}
void find_init_solution()
{
    init_distance_matrix();
    init_tableau_interfaces(solution_initiale.interface);

    qsort(formation, NBR_FORMATIONS, sizeof(formation[0]), compare_formations);
    qsort(solution_initiale.interface, NBR_INTERFACES, sizeof(solution_initiale.interface[0]), compare_interfaces);
    //Affichage tableau formation et interfaces pour débuggage    
    
    printf("\n*********************FORMATIONS****************\n");
    print_formation();
    
    remplir_agendas(solution_initiale.interface);
    compute_distance_interfaces(solution_initiale.interface);
    update_solution(&solution_initiale);
    print_solution(solution_initiale);
     

}

void improve_solution(Solution *sol)
{
	
	//Creer deux copies de la solution sol
	
	//Ajouter les deux copies à l'arbre
	
	improve_standard_error(sol);
	//improve_penalties
	update_solution(sol);
}

/*Fonction permettant d'améliorer l'écart type des distances parcourues par les interfaces. 
Pour ce faire, on tri les interfaces en fonction de leur distance parcourue, et on supprime des créneaux de l'interface ayant le plus de distance parcourue pour les ajouter dans les interfaces ayant
le moins de distance parcourue, jusqu'à arriver à la valeure moyenne des distances parcourues*/

void improve_standard_error(Solution* sol)
{
	int index = 0;
	int jour = 0;
	int interface_receveuse_index = NBR_INTERFACES - 1;
	
	//Boucle tant que l'interface est au dessus du seuil moyen
	while(sol->interface[0].distance_totale > sol->avg_distance)
	{
		//Si l'interface n'a déjà pas de formation ce jour-ci, alors on passe au jour suivant
		if(sol->interface[0].formation[jour].size == 0)
		{
			jour++;
			index = 0;
		}
		
		//Vérification de la compatibilité du créneau avec l'interface recevante, si incompatibilité, on prend la 2e interface avec le moins de distance parcourue
		int *creneau = formation[sol->interface[0].formation[jour].int_array[index]];
		int temps_creneau = creneau[5] - creneau[4];
		while(check_compatibility(&(sol->interface[interface_receveuse_index]), creneau, temps_creneau) == -1 && sol->interface[interface_receveuse_index].distance_totale < sol->avg_distance)
			interface_receveuse_index--;
		printf("jour : %d, index : %d, interface_receveuse : %d\n", jour, index, interface_receveuse_index);
		fflush(stdout);
		
		//Mise à jour du tableau agenda et IntegerArray correspondants
		add_element_intarray(&(sol->interface[interface_receveuse_index].formation[jour]), sol->interface[0].formation[jour].int_array[index]);
		remove_element_intarray(&(sol->interface[0].formation[jour]), index);
		remove_creneau_agenda(sol->interface[0].agenda[jour], creneau, temps_creneau);
		
		//Mise à jour des distances parcourues
		sol->interface[interface_receveuse_index].distance_totale = compute_employee_distance(sol->interface[interface_receveuse_index]);
		sol->interface[0].distance_totale = compute_employee_distance(sol->interface[0]);
		
		//On passe à la formation suivante
		index++;
		
	}
	
	//Mise à jour de la solution
	update_solution(sol);
	print_solution(*sol);
}


void update_solution(Solution *sol)
{
	sol->avg_distance = compute_avg_distance(*sol);
	sol->standard_error = compute_standard_error(*sol, sol->avg_distance);
	sol->fcorr = compute_fcorr(sol->avg_distance);
	sol->penalties = compute_penalties(*sol);
	sol->z = compute_min_z(sol->avg_distance, sol->standard_error, sol->fcorr, sol->penalties);
}


double compute_avg_distance(Solution sol)
{
    double total = 0;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
        total += sol.interface[i].distance_totale;
    }
    total = total / NBR_INTERFACES;
    return total;
}

double compute_standard_error(Solution sol, double avg)
{
    double total = 0;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
        double current = 0, temp = 0;
        current = sol.interface[i].distance_totale;
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

int compute_penalties(Solution sol)
{
    int total = 0;
    Interface *infos_interface = sol.interface;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
    	Interface interface = infos_interface[i];
    	for(int j = 0; j < 6; j++)
    	{
        	int* formations = interface.formation[j].int_array;
        	int nb_formations = interface.formation[j].size;
		for (int index = 0; index < nb_formations; index++)
		{
		    if (interface.specialite[get_champs_formation(formations[index], 1)] != 1)
		    {
		        total += 1;
		    }
		}
	}
    }
    return total;
}

double compute_min_z(double avg, double std, double fcorr, double penalty) {return 0.5 * (avg + std) + 0.5 * fcorr * penalty;}



void print_distances()
{
	for(int i = 0; i < NBR_SPECIALITES + 1; i++)
	{
		printf("Depart %d : \n", i - 1);
		for(int j = 0; j < NBR_SPECIALITES + 1; j++)
		{
			printf("Arrivee %d : %f\n", j - 1, distances[i][j]);
		}
		printf("\n");
	}
}

void print_formation()
{
    for(int i = 0; i < NBR_FORMATIONS; i++)
    {
    	printf("\nIndex formation : %d\n", i);
        printf("Apprenant %d : \n", formation[i][0]);
        printf("Specialite : %d\n", formation[i][1]);
        printf("Competence requise : %d\n", formation[i][2]);
        printf("Jour de la formation : %d\n", formation[i][3]);
        printf("Heure de debut de la formation : %d\n", formation[i][4]);
        printf("Heure de fin de la formation : %d\n",formation[i][5]);
    }
}

			
void print_solution(Solution solution)
{
    printf("\n**********************INTERFACES************************\n");
    print_interfaces(solution_initiale.interface);
    printf("\n*****************************AGENDA*************************\n");
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        printf("\nInterface %d :\n", i);
        for(int j = 0; j < 6; j++)
        {
            printf("Jour %d : ", j + 1);
            for(int p = 0; p < 13; p++)
            {
                printf("%d ", solution.interface[i].agenda[j][p]);
            }
            if(solution.interface[i].formation[j].size != 0)
            	printf("Index formations : ");
            for(int p = 0; p < solution.interface[i].formation[j].size; p++)
            	printf(" %d", solution.interface[i].formation[j].int_array[p]);
            printf("\n");
        }

        printf("distance parcourue : %f\n", solution.interface[i].distance_totale);
    }
    printf("\n*****************************SOLUTION*************************\n");
    printf("z is  : %f\navg distance : %f\nstandard error : %f\nfcorr : %f\npenalties : %d\n", solution.z, solution.avg_distance, solution.standard_error, solution.fcorr, solution.penalties);
}
