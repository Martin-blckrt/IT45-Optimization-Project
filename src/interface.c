#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "tri.h"
#include "solutions.h"

extern int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES];
extern int competences_interfaces[NBR_INTERFACES][2];
extern int formation[NBR_FORMATIONS][6];
extern double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];

void remplir_agendas(Interface *infos_interface)
{
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

        add_element_intarray(&(infos_interface[p].formation[jour]), i);

    }
    for(int p = 0; p < NBR_INTERFACES; p++)
    {
	    for(int i = 0; i < 6; i++)
	    {
	    	qsort(infos_interface[p].formation[i].int_array, infos_interface[p].formation[i].size, sizeof(int), compare_agenda);
	    }
    }
}


//Vérifie si l'interface interface peut prendre le créneau passé en paramètre
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

void init_tableau_interfaces(Interface *infos_interface)
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

double compute_employee_distance(Interface interface)
{
    IntegerArray* jour = interface.formation;
    double distance = 0;
    for(int k = 0; k < 6; k++)
    {
    	//printf("Jour %d :\n", k+1);
    	int *jour_formations = jour[k].int_array;
    	if(jour[k].size != 0)
    	{
    		//printf("SESSAD -> specialite %d : %f\n", get_champs_formation(jour_formations[0], 1), distances[0][get_champs_formation(jour_formations[0], 1) + 1]);
    		distance += distances[0][get_champs_formation(jour_formations[0], 1) + 1];
    		int j = 0;
    		for(j = 0; j < jour[k].size - 1; j++)
    		{
    		//printf("distance : specialite %d -> specialite %d : %f\n", get_champs_formation(jour_formations[j], 1), get_champs_formation(jour_formations[j+1], 1), distances[get_champs_formation(jour_formations[j], 1) + 1][get_champs_formation(jour_formations[j+1], 1) + 1]);
    			distance += distances[get_champs_formation(jour_formations[j], 1) + 1][get_champs_formation(jour_formations[j+1], 1) + 1];
    		}
    		
    		//printf("distance specialite %d -> SESSAD : %f\n", get_champs_formation(jour_formations[j], 1),  distances[get_champs_formation(jour_formations[j], 1) + 1][0]);
    		distance += distances[get_champs_formation(jour_formations[j], 1) + 1][0];
    	}
    }
    
    return distance;
}

void compute_distance_interfaces(Interface *interface)
{
	for(int i = 0; i < NBR_INTERFACES; i++)
		interface[i].distance_totale = compute_employee_distance(interface[i]);
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

void print_interfaces(Interface *infos_interface)
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
