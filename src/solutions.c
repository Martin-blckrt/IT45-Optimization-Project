#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "solutions.h"
#include "tri.h"
#include "btree.h"

#define DEPTH 8

extern int formation[NBR_FORMATIONS][6];
extern float coord[NBR_NODES][2];
extern double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];

int get_champs_formation(int index_formation, int index_champ) {
    return formation[index_formation][index_champ];
}

void init_distance_matrix() {
    for (int i = 0; i < NBR_SPECIALITES + 1; i++) {
        for (int j = 0; j < NBR_SPECIALITES + 1; j++) {
            if (i == j)
                distances[i][j] = 0;
            else
                distances[i][j] = compute_distance(coord[i][0], coord[i][1], coord[j][0], coord[j][1]);
        }
    }
    print_distances();
}

void init_solution_initiale(Solution *sol)
{
	sol->avg_distance = 0;
	sol->standard_error = 0;
	sol->fcorr = 0;
	sol->z = 0;
	sol->penalties = 0;
}

double compute_distance(double xa, double ya, double xb, double yb) {
    double distance = 0;
    distance = pow(xa - xb, 2) + pow(ya - yb, 2);
    distance = sqrt(distance);
    return distance;
}


void create_from_solution(Solution **sol1, Solution sol2)
{
	if(*sol1 == NULL)
	{
		*sol1 = malloc(sizeof(Solution));
	}
	**sol1 = sol2;
	
	duplicate_formations((*sol1)->interface, sol2.interface);

}



void solve() {
    Solution solution_initiale;
    init_solution_initiale(&solution_initiale);
    find_init_solution(&solution_initiale);
    Arbre arbre = malloc(sizeof(Node));
    arbre->leftchild = NULL;
    arbre->rightchild = NULL;
    arbre->solution = NULL;
    create_from_solution(&(arbre->solution), solution_initiale);
    delete_solution_intarrays(solution_initiale.interface);
    
    improve_solution(&arbre, DEPTH);
    
    //Stockage du dernier étage de l'arbre dans le tableau population, et affichage des différents z
    int size = pow(2, DEPTH);


    Solution *population = malloc(sizeof(Solution) *size);


    find_last_floor(arbre, population, 0);
    
    //Affichage des solutions
    for(int i = 0; i < size; i++)
    {
    	qsort(population[i].interface, NBR_INTERFACES, sizeof(Interface), compare_interfaces_ID);
    	//print_z(population[i]);
    }
    
   Solution best_solution;
   find_best_solution(&best_solution, population, size);
   
   printf("***********************************MEILLEURE SOLUTION AVANT GENETIQUE***************************\n");
   print_solution(best_solution);
   printf("*************************************************************************************************\n");
   
   //print_solution(population[0]);
   //print_solution(population[1]);
   
   croiser(&population[0], &population[1], population, 0);
   
   //print_solution(population[0]);
   //print_solution(population[1]);
   
   //Free resources
    delete_arbre(arbre);
    
    
    for(int i = 0; i < size; i++)
    {
    	delete_solution_intarrays(population[i].interface);
    }
    free(population);
    
    delete_solution_intarrays(best_solution.interface);
}

void croiser(Solution *sol1, Solution *sol2, Solution *pop, int index)
{
	//Création des deux solutions filles
	Solution temp = *sol1;
	Solution temp2 = *sol2;	
	duplicate_formations(temp.interface, sol1->interface);
	duplicate_formations(temp2.interface, sol2->interface);
	
	
	//Remplacement des anciennes solutions
	delete_solution_intarrays(sol1->interface);
	delete_solution_intarrays(sol2->interface);
	pop[index] = temp;
	pop[index+1] = temp2;
}


void find_init_solution(Solution *solution_initiale) {
    init_distance_matrix();
    init_tableau_interfaces(solution_initiale->interface);

    qsort(formation, NBR_FORMATIONS, sizeof(formation[0]), compare_formations);
    qsort(solution_initiale->interface, NBR_INTERFACES, sizeof(solution_initiale->interface[0]), compare_interfaces);
    remplir_agendas(solution_initiale->interface);
    update_solution(solution_initiale);

    printf("****************************SOLUTION INITIALE********************\n");
    print_formation();
    print_solution(*solution_initiale);
    printf("\n********************************************************************************************\n");
}

void improve_solution(Arbre *head, int depth) {

	if(depth == 0)
	{
		//print_z(*((*head)->solution));
		return;
	}
	//Creer deux copies de la solution sol que l'on ajoute à l'arbre binaire
	add_child(head, *((*head)->solution), 0);
	add_child(head, *((*head)->solution), 1);

    for(int i = 0; i < 10; i++)
        improve_standard_error((*head)->leftchild->solution);

    for(int j = 0; j < 30; j++)
        improve_penalties((*head)->rightchild->solution);

    improve_solution(&((*head)->leftchild), depth-1);
    improve_solution(&((*head)->rightchild), depth-1);

}

/*Fonction permettant d'améliorer l'écart type des distances parcourues par les interfaces.
Pour ce faire, on tri les interfaces en fonction de leur distance parcourue, et on supprime des créneaux de l'interface ayant le plus de distance parcourue pour les ajouter dans les interfaces ayant
le moins de distance parcourue, jusqu'à arriver à la valeure moyenne des distances parcourues*/

void improve_standard_error(Solution *sol) {

    qsort(sol->interface, NBR_INTERFACES, sizeof(sol->interface[0]), compare_interfaces_distance);
    //print_solution(*sol);
    int index = 0;
    int jour = 0;
    int interface_receveuse_index = NBR_INTERFACES - 1;

    //Boucle tant que l'interface est au dessus du seuil moyen
    while (sol->interface[0].distance_totale > sol->avg_distance) {

        //Si l'interface n'a déjà pas de formation ce jour-ci, alors on passe au jour suivant
        while(sol->interface[0].formation[jour].size == index) {
            jour++;
            index = 0;
        }

	//Vérification de la distance parcourue de l'interface receveuse afin que celle-ci ne devienne pas plus grande que la distance moyenne parcourue
        //Vérification de la compatibilité du créneau avec l'interface recevante, si incompatibilité, on prend la 2e interface avec le moins de distance parcourue

        int *creneau = formation[sol->interface[0].formation[jour].int_array[index]];

        int temps_creneau = creneau[5] - creneau[4];
        if(sol->interface[interface_receveuse_index].distance_totale > sol->avg_distance)
        	interface_receveuse_index--;

        while (interface_receveuse_index > 0 && check_compatibility(&(sol->interface[interface_receveuse_index]), creneau, temps_creneau) == -1)
        {
    		interface_receveuse_index--;
    		//Avant de vérifier la compatibilité de la nouvelle interface, on vérifie que sa distance parcourue est bien inférieure à celle de la moyenne
    		if(sol->interface[interface_receveuse_index].distance_totale > sol->avg_distance)
    			interface_receveuse_index--;
        }


        //Si interface_receveuse_index = 0, cela signifie qu'aucune interface était à la fois compatible avec le créneau et avait une distance totale inférieure à celle de la moyenne, on passe donc au créneau suivant
        if(interface_receveuse_index > 0)
	{
		//Mise à jour du tableau agenda et IntegerArray correspondants, passage au créneau suivant par suppression de la formation dans le tableau des formations (l'index 0 est donc remplacé par la formation suivante)
		add_element_intarray(&(sol->interface[interface_receveuse_index].formation[jour]), sol->interface[0].formation[jour].int_array[index]);
		remove_element_intarray(&(sol->interface[0].formation[jour]), sol->interface[0].formation[jour].int_array[index]);
		remove_creneau_agenda(sol->interface[0].agenda[jour], creneau, temps_creneau);

		//Mise à jour de la solution et des interfaces
		update_solution(sol);

	}
	else
            index++;


	interface_receveuse_index = NBR_INTERFACES - 1;


    }

    for(int p = 0; p < NBR_INTERFACES; p++)
    {
	    for(int i = 0; i < 6; i++)
	    {
	    	qsort(sol->interface[p].formation[i].int_array, sol->interface[p].formation[i].size, sizeof(int), compare_agenda);
	    }
    }
    //Mise à jour de la solution
    update_solution(sol);


}


void improve_penalties(Solution *sol) {
    qsort(sol->interface, NBR_INTERFACES, sizeof(sol->interface[0]), compare_penalties);

    IntegerArray *jour = sol->interface[0].formation;

    //pour chaque jour
    for (int k = 0; k < 6; k++)
    {
        int *jour_formations = jour[k].int_array;

        //pour chaque formation du jour
        for (int p = 0; p < jour[k].size; p++)
        {
            int *creneau = formation[jour_formations[p]];
            int temps_creneau = creneau[5] - creneau[4];
            //si ce creneau genere une penalite pour l'interface qui l'a actuellement
            if (sol->interface[0].specialite[get_champs_formation(jour_formations[p], 1)] != 1)
            {
                for (int j = 1; j < NBR_INTERFACES - 1; j++)
                {
                    //si l'interface j a la meme spe que le creneau
                    if (sol->interface[j].specialite[get_champs_formation(jour_formations[p], 1)] == 1)
                    {
                        //si le creneau et l'interface j sont comptabiles
                        if (check_compatibility(&(sol->interface[j]), creneau, temps_creneau) == -0)
                        {
                            //Mise à jour du tableau agenda et IntegerArray correspondants
                            add_element_intarray(&(sol->interface[j].formation[k]), jour_formations[p]);
                            remove_element_intarray(&(jour[k]), jour_formations[p]);
                            remove_creneau_agenda(sol->interface[0].agenda[k], creneau, temps_creneau);

                            //Mise à jour des distances parcourues
                            sol->interface[j].distance_totale = compute_employee_distance(sol->interface[j]);
                            sol->interface[0].distance_totale = compute_employee_distance(sol->interface[0]);

                            //Mise à jour des penalites
                            sol->interface[j].nb_penalties = compute_penalty_interface(sol->interface[j]);
                            sol->interface[0].nb_penalties = compute_penalty_interface(sol->interface[0]);

                            //si on a assigné le creneau on peut sortir et aller au creneau d'après
                            break;
                        }
                    }
                }
            //break arrives here
            }
        }
    }

    //Mise à jour de la solution
    update_solution(sol);
}

void find_best_solution(Solution *best_sol, Solution*pop, int size)
{
	double min_z = INFINITY;
	int index = 0;
	for(int i = 0; i < size-1; i++)
	{
		if(pop[i].z < min_z)
		{
			min_z = pop[i].z;
			index = i;
		}
	}
	*best_sol = pop[index];
	duplicate_formations(best_sol->interface, pop[index].interface);
	
}

void update_solution(Solution *sol) {
    compute_distances_interfaces(sol);
    sol->avg_distance = compute_avg_distance(*sol);
    sol->standard_error = compute_standard_error(sol, sol->avg_distance);
    sol->fcorr = compute_fcorr(sol->avg_distance);
    sol->penalties = compute_penalties(sol);
    sol->z = compute_min_z(sol->avg_distance, sol->standard_error, sol->fcorr, sol->penalties);
}

void compute_distances_interfaces(Solution *sol)
{
	for(int i = 0; i < NBR_INTERFACES; i++)
	{
		sol->interface[i].distance_totale = compute_employee_distance(sol->interface[i]);
	}
}

double compute_avg_distance(Solution sol) {
    double total = 0;
    for (int i = 0; i < NBR_INTERFACES; i++) {
        total += sol.interface[i].distance_totale;
    }
    total = total / NBR_INTERFACES;
    return total;
}

double compute_standard_error(Solution *sol, double avg) {
    double total = 0;
    for (int i = 0; i < NBR_INTERFACES; i++) {
        double current = 0, temp = 0;
        current = sol->interface[i].distance_totale;
        temp = current - avg;
        total += pow(temp, 2);
    }
    total = total / NBR_INTERFACES;
    total = sqrt(total);
    return total;
}

double compute_fcorr(double avg) {
    double total = 0;
    total = avg * NBR_INTERFACES;
    total = total / NBR_FORMATIONS;
    return total;
}

int compute_penalties(Solution *sol) {
    int total = 0;
    Interface *infos_interface = sol->interface;

    for (int i = 0; i < NBR_INTERFACES; i++)
    {
        infos_interface[i].nb_penalties = compute_penalty_interface(infos_interface[i]);
        total += infos_interface[i].nb_penalties;
    }
    return total;
}

double compute_min_z(double avg, double std, double fcorr, double penalty) {
    return 0.5 * (avg + std) + 0.5 * fcorr * penalty;
}

void print_distances() {
    for (int i = 0; i < NBR_SPECIALITES + 1; i++) {
        printf("Depart %d : \n", i - 1);
        for (int j = 0; j < NBR_SPECIALITES + 1; j++) {
            printf("Arrivee %d : %f\n", j - 1, distances[i][j]);
        }
        printf("\n");
    }
}

void print_formation() {

	printf("\n*********************FORMATIONS****************\n");
    for (int i = 0; i < NBR_FORMATIONS; i++) {
        printf("\nIndex formation (!= numero apprenant) : %d\n", i);
        printf("Apprenant %d : \n", formation[i][0]);
        printf("Specialite : %d\n", formation[i][1]);
        printf("Competence requise : %d\n", formation[i][2]);
        printf("Jour de la formation : %d\n", formation[i][3]);
        printf("Heure de debut de la formation : %d\n", formation[i][4]);
        printf("Heure de fin de la formation : %d\n", formation[i][5]);
    }
}

void print_z(Solution solution)
{
	printf("\n*****************************SOLUTION*************************\n");
    	printf("z is  : %f \navg distance : %f \nstandard error : %f \nfcorr : %f \npenalties : %d \n", solution.z,
           solution.avg_distance, solution.standard_error, solution.fcorr, solution.penalties);
}

void print_interfaces(Interface *interface)
{
	printf("\n**********************INTERFACES************************ \n");
	for(int i = 0; i < NBR_INTERFACES; i++)
	{
		printf("Index interface (indépendant de l'interface) : %d \n", i);
		print_interface(interface[i]);
	}
}

void print_solution(Solution solution) {
    	print_interfaces(solution.interface);
	print_z(solution);

}

void delete_solution(Solution *sol)
{
	delete_solution_intarrays(sol->interface);
	free(sol);
}

void delete_solution_intarrays(Interface *interface)
{
	for(int i = 0; i < NBR_INTERFACES; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			clean_intarray(&interface[i].formation[j]);
		}
	}
}

