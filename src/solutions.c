#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "solutions.h"
#include "tri.h"
#include "btree.h"

#define DEPTH 8

extern int formation[NBR_FORMATIONS][6];
extern float coord[NBR_NODES][2];
extern double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];

//fonction utilitaire permettant de récupérer le champ d'une formation voulue
int get_champs_formation(int index_formation, int index_champ) {
    return formation[index_formation][index_champ];
}

//Calcul de la matrice des distances entre centres
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

//Mise à 0 de tous les champs
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

//Creer dynamiquement une solution à partir d'une autre
void create_from_solution(Solution **sol1, Solution sol2)
{
	if(*sol1 == NULL)
	{
		*sol1 = malloc(sizeof(Solution));
	}
	**sol1 = sol2;

	//Recopiage des tableaux dynamiques (=formations associées à chaque jour à chaque interface)
	duplicate_formations((*sol1)->interface, sol2.interface);

}

//Fonction de résolution
void solve() {

    srand(time(NULL));

    //Etablissement de la solution initiale
    Solution solution_initiale;
    init_solution_initiale(&solution_initiale);
    find_init_solution(&solution_initiale);

    //Amélioration de la solution initiale par une heuristique "brute" et établissement d'un arbre comprenant un panel de solutions diverses
    Arbre arbre = malloc(sizeof(Node));
    arbre->leftchild = NULL;
    arbre->rightchild = NULL;
    arbre->solution = NULL;
    create_from_solution(&(arbre->solution), solution_initiale);
    delete_solution_intarrays(solution_initiale.interface);
    improve_solution(&arbre, DEPTH);


    //Tentative de trouver une meilleure solution avec une population issue de l'arbre généré précédemment
    //Stockage du dernier étage de l'arbre dans le tableau population, et affichage des différents z (arbitraire, le choix des solutions à stocker peut être à étudier en fonction de la fonction objectf)
    int size = pow(2, DEPTH);
    Solution *population = malloc(sizeof(Solution) *size);
    find_last_floor(arbre, population, 0);

    //Affichage des solutions et tri en fonction de l'ID
    for(int i = 0; i < size; i++)
    {
    	//print_solution(population[i]);
    	//print_z(population[i]);
    }

   Solution *best_solution = malloc(sizeof(Solution));
   best_solution->z = INFINITY;
   find_best_solution(best_solution, population, size);

   printf("***********************************MEILLEURE SOLUTION AVANT GENETIQUE***************************\n");
   print_z(*best_solution);
   printf("*************************************************************************************************\n");

   //Itérations de l'algorithme génétique
   for(int i = 0; i < 1000; i++)
   {
	   for(int j = 0; j < size/2; j++)
	   {
	   	//Comprend le choix des interfaces à croiser, le croisement et les réparations des solutions filles
	   	croiser(&population[j], &population[size-1-j], population, j, size);
	   }

	//Actualisation de la meilleure solution
   	find_best_solution(best_solution, population, size);
   	//print_z(*best_solution);
   }
   //Free resources
    delete_arbre(arbre);

    for(int i = 0; i < size; i++)
    {
    	delete_solution_intarrays(population[i].interface);
    }
    free(population);

    delete_solution_intarrays(best_solution->interface);
    free(best_solution);
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

//Fonction d'amélioration de notre solution initiale par une heuristique classique
void improve_solution(Arbre *head, int depth) {

	if(depth == 0)
	{
		//print_z(*((*head)->solution));
		return;
	}
	//Creer deux copies de la solution sol que l'on ajoute à l'arbre binaire
	add_child(head, *((*head)->solution), 0);
	add_child(head, *((*head)->solution), 1);

	//Ici, on va itérer un certain nombre de fois une amélioration, cette valeur est un paramètre qui va influer sur l'optimalité des solutions que l'on peut trouver pour un arbre d'une profondeur donnée. Dans notre cas, la pénalité étant plus importante, nous privilégions l'amélioration des pénalité à l'amélioration de l'écart type
	//Amélioration du fils gauche au niveau de l'écart type
    for(int i = 0; i < 10; i++)
        improve_standard_error((*head)->leftchild->solution);

	//Amélioration du fils droit au niveau du nombre de pénalités
    for(int j = 0; j < 30; j++)
        improve_penalties((*head)->rightchild->solution);

	//Amélioration des fils gauches et droits
    improve_solution(&((*head)->leftchild), depth-1);
    improve_solution(&((*head)->rightchild), depth-1);

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

//Fonction de croisement de deux solutions sur une interface choisie aléatoirement
void croiser(Solution *sol1, Solution *sol2, Solution *pop, int index, int size)
{
	//Création des deux solutions filles
	Solution temp = *sol1;
	Solution temp2 = *sol2;
	duplicate_formations(temp.interface, sol1->interface);
	duplicate_formations(temp2.interface, sol2->interface);

	//Recherche aléatoire de l'interface sur laquelle le croisement va s'opérer
	int random_interface_index;
	Interface *interface1;
	Interface *interface2;

	do
	{
		random_interface_index = rand()%NBR_INTERFACES;
		interface1 = &sol1->interface[random_interface_index];
		interface2 = &sol2->interface[random_interface_index];
	}while(has_formation(*interface1) == -1 || has_formation(*interface2) == -1); //On cherche une interface pour laquelle un croisement va bien donner une nouvelle interface

	Interface *interface1temp = &temp.interface[random_interface_index];
	Interface *interface2temp = &temp2.interface[random_interface_index];

	//Suppression des formations dans les interfaces correspondantes dans les solutions filles, stockage des formations supprimées afin de vérifier qu'elles sont présentes dans les solutions filles
	IntegerArray tempformation1[3];
	IntegerArray tempformation2[3];

	//Suppression des formations que l'on va croiser (ce qui correspond à la deuxieme moitié de semaine de nos deux interfaces changeantes)
	//Stockage en mémoire des formations supprimées pour vérifier leur présence une fois les solutions filles établies
	for(int i = 3; i < 6; i++)
	{
		duplicate_intarrays(&tempformation1[i-3], interface1temp->formation[i]);
		duplicate_intarrays(&tempformation2[i-3], interface2temp->formation[i]);

		for(int p = 0; p < tempformation1[i-3].size; p++)
			remove_element_intarray(&interface1temp->formation[i], interface1temp->formation[i].int_array[0]);
		for(int p = 0; p < tempformation2[i-3].size; p++)
			remove_element_intarray(&interface2temp->formation[i], interface2temp->formation[i].int_array[0]);

		for(int p = 0; p < 13; p ++)
		{
			interface1temp->agenda[i][p] = 0;
			interface2temp->agenda[i][p] = 0;
		}
	}

	//Croisement des solutions
	for(int i = 0; i < 3; i++)
	{
		int index = 6 - 3 + i;
		for(int j = 0; j < interface2->formation[index].size; j++)
			add_creneau_croiser(interface1temp, *interface2, &tempformation1[index-3], index, j);
		for(int j = 0; j < interface1->formation[index].size; j++)
			add_creneau_croiser(interface2temp, *interface1, &tempformation2[index-3], index, j);
	}

	//Réparation des solutions
	//Ces booléens permettent de repérer une réparation infaisable (i.e une formation manquante attribuable à aucune interface)
	int check_compatibility_temp = 0;
	int check_compatibility_temp2 = 0;

	//Réparation des doublons
	for(int i = 3; i < 6; i++)
	{
		//Réparation des doublons dans les deux solutions filles
		for(int j = 0; j < interface1temp->formation[i].size; j++)
			j+=delete_doublons(interface1temp->formation[i].int_array[j], random_interface_index, temp.interface);
		for(int j = 0; j < interface2temp->formation[i].size; j++)
			j+=delete_doublons(interface2temp->formation[i].int_array[j], random_interface_index, temp2.interface);
	}

	//Réparation des formations manquantes
	for(int i = 3; i < 6; i++)
	{
		//Attribution des formations manquantes dans les deux solutions filles
		for(int j = 0; j < tempformation1[i-3].size; j++)
		{
			//On essaie d'abord de l'attribuer à l'interface initiale
			int *creneau = formation[tempformation1[i-3].int_array[j]];
			int temps_creneau = creneau[5] - creneau[4];
			if(check_compatibility(interface1temp, creneau, temps_creneau) != -1)
				add_element_intarray(&interface1temp->formation[i], tempformation1[i-3].int_array[j]);
			else
			{
				//Si ça n'est pas possible, on l'attribue à la première interface possible
				int p = 0;
				while(check_compatibility(&temp.interface[p], creneau, temps_creneau) == -1 && p < NBR_INTERFACES)
					p++;
				//Si aucune interface n'est compatible, alors solution irréparable
				if(p == NBR_INTERFACES)
                {
                    printf("pas compatible 1\n");
                    check_compatibility_temp = -1;
                }

				else
					add_element_intarray(&temp.interface[p].formation[i], tempformation1[i-3].int_array[j]);
			}
		}
		//Pareil pour la solution fille 2
		for(int j = 0; j < tempformation2[i-3].size; j++)
		{
			int *creneau = formation[tempformation2[i-3].int_array[j]];
			int temps_creneau = creneau[5] - creneau[4];
			if(check_compatibility(interface2temp, creneau, temps_creneau) != -1)
				add_element_intarray(&interface2temp->formation[i], tempformation2[i-3].int_array[j]);
			else
			{
				int p = 0;
				while(check_compatibility(&temp2.interface[p], creneau, temps_creneau) == -1 && p < NBR_INTERFACES)
					p++;
				if(p == NBR_INTERFACES)
                {
                    printf("pas compatible 2\n");
                    check_compatibility_temp2 = -1;
                }
				else
					add_element_intarray(&temp2.interface[p].formation[i], tempformation2[i-3].int_array[j]);
			}
		}
	}

	//Remplacement des anciennes solutions si les nouvelles sont valides
	for(int i = 0; i < 3; i++)
	{
		clean_intarray(&tempformation1[i]);
		clean_intarray(&tempformation2[i]);
	}

	if(check_compatibility_temp == -1)
		delete_solution_intarrays(temp.interface);
	else
	{
		delete_solution_intarrays(sol1->interface);
		for(int p = 0; p < NBR_INTERFACES; p++)
	    	{
		    for(int i = 0; i < 6; i++)
		    	qsort(temp.interface[p].formation[i].int_array, temp.interface[p].formation[i].size, sizeof(int), compare_agenda);
    		}
    		update_solution(&temp);
    		pop[index] = temp;
    		duplicate_formations(pop[index].interface, temp2.interface);
	}

	if(check_compatibility_temp2 == -1)
		delete_solution_intarrays(temp2.interface);
	else
	{
		delete_solution_intarrays(sol2->interface);

		for(int p = 0; p < NBR_INTERFACES; p++)
	    	{
		    for(int i = 0; i < 6; i++)
		    	qsort(temp2.interface[p].formation[i].int_array, temp2.interface[p].formation[i].size, sizeof(int), compare_agenda);
    		}
    		update_solution(&temp2);
    		pop[size - 1 - index] = temp2;
    		duplicate_formations(pop[size-1-index].interface, temp2.interface);

    	}
}

//Fonction entièrement conçue et utilisée pour factoriser du code de la fonction croiser
void add_creneau_croiser(Interface *interface1, Interface interface2, IntegerArray *array_to_update, int i, int j)
{
	int *creneau = formation[interface2.formation[i].int_array[j]];
	int temps_creneau = creneau[5] - creneau[4];
	if(check_compatibility(interface1, creneau, temps_creneau) != -1)
	{
		add_element_intarray(&interface1->formation[i], interface2.formation[i].int_array[j]);
		remove_element_intarray(array_to_update, interface1->formation[i].int_array[j]);

	}

}

//Stock dans best_sol la meilleure solution de pop
void find_best_solution(Solution *best_sol, Solution*pop, int size)
{
	double min_z = INFINITY;
	int index = 0;
	int new_sol = 0;
	for(int i = 0; i < size; i++)
	{

		if(pop[i].z < min_z && pop[i].z < best_sol->z)
		{
			min_z = pop[i].z;
			index = i;
			new_sol = 1;

		}
	}
	if(new_sol == 1)
	{
		//La découverte d'une nouvelle solution signifiant l'allocation de nouvelles ressources, il faut détecter le premier appel à cette fonction car best_sol ne contient aucune mémoire dynamique au premier appel (il ne faut donc pas la libérer)
		if(best_sol->z != INFINITY)
			delete_solution_intarrays(best_sol->interface);
		*best_sol = pop[index];
		duplicate_formations(best_sol->interface, pop[index].interface);
	}


}


//Calcul des champs de la solution sol
void update_solution(Solution *sol) {
    compute_distances_interfaces(sol);
    sol->avg_distance = compute_avg_distance(*sol);
    sol->standard_error = compute_standard_error(sol, sol->avg_distance);
    sol->fcorr = compute_fcorr(sol->avg_distance);
    sol->penalties = compute_penalties(sol);
    sol->z = compute_min_z(sol->avg_distance, sol->standard_error, sol->fcorr, sol->penalties);
}

//Série de fonctions permettant le calcul de z
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

