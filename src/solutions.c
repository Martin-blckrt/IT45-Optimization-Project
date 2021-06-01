#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "solutions.h"
#include "tri.h"
#include "interface.h"

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

double compute_distance(double xa, double ya, double xb, double yb) {
    double distance = 0;
    distance = pow(xa - xb, 2) + pow(ya - yb, 2);
    distance = sqrt(distance);
    return distance;
}

void solve() {
    Solution solution_initiale;

    find_init_solution(&solution_initiale);
    
    improve_solution(&solution_initiale);
}

void find_init_solution(Solution *solution_initiale) {
    init_distance_matrix();
    init_tableau_interfaces(solution_initiale->interface);

    qsort(formation, NBR_FORMATIONS, sizeof(formation[0]), compare_formations);
    qsort(solution_initiale->interface, NBR_INTERFACES, sizeof(solution_initiale->interface[0]), compare_interfaces);
    //Affichage tableau formation et interfaces pour débuggage    

    printf("\n*********************FORMATIONS****************\n");
    print_formation();

    remplir_agendas(solution_initiale->interface);
    update_solution(solution_initiale);
    print_solution(*solution_initiale);
}

void improve_solution(Solution *sol) {

    //Creer deux copies de la solution sol

    //Ajouter les deux copies à l'arbre
    	
    	//SItuation de bug : première boucle de 0 à 100, deuxieme boucle de 0 à 100 et troisieme boucle de 0 à 20, ça bug avec pas mal de grosses valeurs pour la 3e boucle
	/*for(int i = 0; i < 1; i++)
	{
		for(int j = 0; j < 1; j++)
		{
			printf("debut std\n");
			improve_standard_error(sol);
			printf("fin std\n");
		}
		for(int j = 0; j <10; j++)
		{
			printf("debut penalty\n");
			improve_penalties(sol);
			printf("fin penalty\n");
			
		}
	}*/

}

/*Fonction permettant d'améliorer l'écart type des distances parcourues par les interfaces. 
Pour ce faire, on tri les interfaces en fonction de leur distance parcourue, et on supprime des créneaux de l'interface ayant le plus de distance parcourue pour les ajouter dans les interfaces ayant
le moins de distance parcourue, jusqu'à arriver à la valeure moyenne des distances parcourues*/

void improve_standard_error(Solution *sol) {

    qsort(sol->interface, NBR_INTERFACES, sizeof(sol->interface[0]), compare_interfaces_distance);
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
	//Si aucune interface 
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
                            remove_element_intarray(&(jour[k]), p);
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
		sol->interface[i].distance_totale = compute_employee_distance(sol->interface[i]);
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
    for (int i = 0; i < NBR_FORMATIONS; i++) {
        printf("\nIndex formation : %d\n", i);
        printf("Apprenant %d : \n", formation[i][0]);
        printf("Specialite : %d\n", formation[i][1]);
        printf("Competence requise : %d\n", formation[i][2]);
        printf("Jour de la formation : %d\n", formation[i][3]);
        printf("Heure de debut de la formation : %d\n", formation[i][4]);
        printf("Heure de fin de la formation : %d\n", formation[i][5]);
    }
}


void print_solution(Solution solution) {
    printf("\n**********************INTERFACES************************\n");
    print_interfaces(solution.interface);
    printf("\n*****************************AGENDA*************************\n");
    for (int i = 0; i < NBR_INTERFACES; i++) {
        printf("\nInterface %d :\n", i);
        for (int j = 0; j < 6; j++) {
            printf("Jour %d : ", j + 1);
            for (int p = 0; p < 13; p++) {
                printf("%d ", solution.interface[i].agenda[j][p]);
            }
            if (solution.interface[i].formation[j].size != 0)
                printf("Index formations : ");
            for (int p = 0; p < solution.interface[i].formation[j].size; p++)
                printf(" %d", solution.interface[i].formation[j].int_array[p]);
            printf("\n");
        }

        printf("distance parcourue : %f\n", solution.interface[i].distance_totale);
        printf("Penalites : %d\n", solution.interface[i].nb_penalties);
    }
    printf("\n*****************************SOLUTION*************************\n");
    printf("z is  : %f\navg distance : %f\nstandard error : %f\nfcorr : %f\npenalties : %d\n", solution.z,
           solution.avg_distance, solution.standard_error, solution.fcorr, solution.penalties);
}


