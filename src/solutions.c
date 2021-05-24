#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solutions.h"
#include "tri.h"
#include "interface.h"


extern int formation[NBR_FORMATIONS][6];
extern float coord[NBR_NODES][2];
double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];
Interface infos_interface[NBR_INTERFACES];



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

void find_init_solution()
{
    init_distance_matrix();
    init_tableau_interfaces();

    qsort(formation, NBR_FORMATIONS, sizeof(formation[0]), compare_formations);
    qsort(infos_interface, NBR_INTERFACES, sizeof(infos_interface[0]), compare_interfaces);
    //Affichage tableau formation et interfaces pour débuggage    
    printf("\n**********************INTERFACES************************\n");
    print_interfaces();
    printf("\n*********************FORMATIONS****************\n");
    print_formation();
    remplir_agendas();
    printf("\n*****************************AGENDA*************************\n");
    print_solution();
     

}



double compute_employee_distance(int i)
{
    Interface interface = infos_interface[i];
    IntegerArray* jour = interface.formation;
    double distance = 0;
    for(int k = 0; k < 6; k++)
    {
    	printf("Jour %d :\n", k+1);
    	int *jour_formations = jour[k].int_array;
    	if(jour[k].size != 0)
    	{
    		printf("SESSAD -> specialite %d : %f\n", get_champs_formation(jour_formations[0], 1), distances[0][get_champs_formation(jour_formations[0], 1) + 1]);
    		distance += distances[0][get_champs_formation(jour_formations[0], 1) + 1];
    		int j = 0;
    		for(j = 0; j < jour[k].size - 1; j++)
    		{
    		printf("distance : specialite %d -> specialite %d : %f\n", get_champs_formation(jour_formations[j], 1), get_champs_formation(jour_formations[j+1], 1), distances[get_champs_formation(jour_formations[j], 1) + 1][get_champs_formation(jour_formations[j+1], 1) + 1]);
    			distance += distances[get_champs_formation(jour_formations[j], 1) + 1][get_champs_formation(jour_formations[j+1], 1) + 1];
    		}
    		
    		printf("distance specialite %d -> SESSAD : %f\n", get_champs_formation(jour_formations[j], 1),  distances[get_champs_formation(jour_formations[j], 1) + 1][0]);
    		distance += distances[get_champs_formation(jour_formations[j], 1) + 1][0];
    	}
    }
    
    return distance;
}

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

int compute_penalties()
{
    int total = 0;
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

double compute_min_z()
{
    double total = 0, avg = 0, std = 0, fcorr = 0, penalty = 0;
    avg = compute_avg_distance();
    std = compute_standard_error(avg);
    fcorr = compute_fcorr(avg);
    penalty = compute_penalties();
    total = 0.5 * (avg + std) + 0.5 * fcorr * penalty;
    return total;
}



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
            if(infos_interface[i].formation[j].size != 0)
            	printf("Index formations : ");
            for(int p = 0; p < infos_interface[i].formation[j].size; p++)
            	printf(" %d", infos_interface[i].formation[j].int_array[p]);
            printf("\n");
        }

        printf("distance parcourue : %f\n", compute_employee_distance(i));
    }
    //printf("\nz is  : %f\n", compute_min_z());
}
