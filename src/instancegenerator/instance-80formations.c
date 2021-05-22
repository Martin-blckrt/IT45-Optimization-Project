#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NBR_INTERFACES        96
#define NBR_APPRENANTS        80
#define NBR_FORMATIONS        80
#define NBR_CENTRES_FORMATION 3
#define NBR_SPECIALITES       3
#define NBR_NODES 	      NBR_CENTRES_FORMATION+NBR_INTERFACES+NBR_APPRENANTS

/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1


/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]={
    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {0,1}
};

/* spécialités des interfaces */
#define SPECIALITE_SANS       -1 /* Enseigné dans le centre le plus proche */
#define SPECIALITE_MENUISERIE  0
#define SPECIALITE_ELECTRICITE 1
#define SPECIALITE_MECANIQUE   2

/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {1,0,0},
    {1,1,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,1},
    {1,0,0},
    {0,0,0},
    {1,0,1},
    {0,0,0},
    {1,1,0},
    {1,0,0},
    {0,0,0},
    {0,0,0},
    {0,1,0},
    {0,1,0},
    {0,1,1},
    {0,1,0},
    {0,0,1},
    {1,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,1},
    {0,0,1},
    {0,0,0},
    {0,1,0},
    {0,0,0},
    {0,1,1},
    {0,1,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,0,0},
    {1,0,0},
    {0,0,0},
    {0,0,0},
    {0,1,0},
    {0,0,0},
    {0,0,0},
    {0,0,1},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,1,0},
    {0,0,1},
    {1,0,0},
    {0,0,0},
    {0,0,0},
    {0,1,0},
    {0,0,0},
    {0,0,0},
    {0,0,1},
    {0,0,0},
    {0,1,1},
    {0,0,0},
    {0,0,0},
    {0,0,1},
    {0,0,0},
    {1,0,0},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,0},
    {0,0,0},
    {0,1,1},
    {0,0,0},
    {1,1,0},
    {0,1,0},
    {1,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,1},
    {0,0,0},
    {0,1,0},
    {0,1,0},
    {0,0,0},
    {1,1,0},
    {0,0,0},
    {0,0,1},
    {0,0,0}
};

/* coordonnées des centres de formation, des interfaces et des apprenants */
double coord[NBR_NODES][2]={

    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {123,11}, /* centre 0 */

    /* Centres de formation */
    {108,2}, /* ecole formation SPECIALITE_MENUISERIE */
    {66,145}, /* ecole formation SPECIALITE_ELECTRICITE */
    {105,142}, /* ecole formation SPECIALITE_MECANIQUE */

    /* Apprenants */
    {126,176}, /* apprenant 0 */
    {52,130}, /* apprenant 1 */
    {43,119}, /* apprenant 2 */
    {119,53}, /* apprenant 3 */
    {165,36}, /* apprenant 4 */
    {118,178}, /* apprenant 5 */
    {82,28}, /* apprenant 6 */
    {105,125}, /* apprenant 7 */
    {136,199}, /* apprenant 8 */
    {56,14}, /* apprenant 9 */
    {148,14}, /* apprenant 10 */
    {6,174}, /* apprenant 11 */
    {117,179}, /* apprenant 12 */
    {130,98}, /* apprenant 13 */
    {107,167}, /* apprenant 14 */
    {131,96}, /* apprenant 15 */
    {58,35}, /* apprenant 16 */
    {124,26}, /* apprenant 17 */
    {48,18}, /* apprenant 18 */
    {165,35}, /* apprenant 19 */
    {148,94}, /* apprenant 20 */
    {152,21}, /* apprenant 21 */
    {121,155}, /* apprenant 22 */
    {71,54}, /* apprenant 23 */
    {154,179}, /* apprenant 24 */
    {57,3}, /* apprenant 25 */
    {7,18}, /* apprenant 26 */
    {102,169}, /* apprenant 27 */
    {54,197}, /* apprenant 28 */
    {49,106}, /* apprenant 29 */
    {157,164}, /* apprenant 30 */
    {188,29}, /* apprenant 31 */
    {144,7}, /* apprenant 32 */
    {76,163}, /* apprenant 33 */
    {30,127}, /* apprenant 34 */
    {22,13}, /* apprenant 35 */
    {63,125}, /* apprenant 36 */
    {66,155}, /* apprenant 37 */
    {171,70}, /* apprenant 38 */
    {17,124}, /* apprenant 39 */
    {7,81}, /* apprenant 40 */
    {48,30}, /* apprenant 41 */
    {45,69}, /* apprenant 42 */
    {144,150}, /* apprenant 43 */
    {66,97}, /* apprenant 44 */
    {181,169}, /* apprenant 45 */
    {174,107}, /* apprenant 46 */
    {127,184}, /* apprenant 47 */
    {68,193}, /* apprenant 48 */
    {0,46}, /* apprenant 49 */
    {198,131}, /* apprenant 50 */
    {123,47}, /* apprenant 51 */
    {167,83}, /* apprenant 52 */
    {8,24}, /* apprenant 53 */
    {106,150}, /* apprenant 54 */
    {35,28}, /* apprenant 55 */
    {44,82}, /* apprenant 56 */
    {24,145}, /* apprenant 57 */
    {143,8}, /* apprenant 58 */
    {99,185}, /* apprenant 59 */
    {68,81}, /* apprenant 60 */
    {125,169}, /* apprenant 61 */
    {165,139}, /* apprenant 62 */
    {199,107}, /* apprenant 63 */
    {185,100}, /* apprenant 64 */
    {66,195}, /* apprenant 65 */
    {29,20}, /* apprenant 66 */
    {44,90}, /* apprenant 67 */
    {177,199}, /* apprenant 68 */
    {150,41}, /* apprenant 69 */
    {87,127}, /* apprenant 70 */
    {160,125}, /* apprenant 71 */
    {172,134}, /* apprenant 72 */
    {107,10}, /* apprenant 73 */
    {93,22}, /* apprenant 74 */
    {133,154}, /* apprenant 75 */
    {133,48}, /* apprenant 76 */
    {57,104}, /* apprenant 77 */
    {70,64}, /* apprenant 78 */
    {158,88}/* apprenant 79 */
};

#define NBR_FORMATION          80

#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6

/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATION][6]={
   {0,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,9,11},
   {1,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,8,11},
   {2,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,16},
   {3,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,13,16},
   {4,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,17},
   {5,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,13,15},
   {6,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,15,17},
   {7,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,8,10},
   {8,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {9,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,14,19},
   {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,15,19},
   {11,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,14,16},
   {12,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,10,12},
   {13,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,10,12},
   {14,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {15,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,19},
   {16,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,16,19},
   {17,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,15,18},
   {18,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,14,19},
   {19,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,9,12},
   {20,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,14,18},
   {21,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,13,19},
   {22,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,8,10},
   {23,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,9,12},
   {24,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,10,12},
   {25,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {26,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,15,17},
   {27,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,9,12},
   {28,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,15,17},
   {29,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,14,17},
   {30,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,9,12},
   {31,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,14,17},
   {32,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,9,11},
   {33,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,15,19},
   {34,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,15,18},
   {35,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,9,12},
   {36,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,10,12},
   {37,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,16,18},
   {38,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,14,18},
   {39,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {40,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,15,18},
   {41,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,9,11},
   {42,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,10,12},
   {43,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,8,12},
   {44,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,10,12},
   {45,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {46,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,13,16},
   {47,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,14,19},
   {48,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {49,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,9,12},
   {50,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,14,19},
   {51,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,9,11},
   {52,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,8,10},
   {53,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {54,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,13,16},
   {55,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,9,12},
   {56,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,10,12},
   {57,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,14,19},
   {58,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,8,10},
   {59,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,16,19},
   {60,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,9,12},
   {61,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,8,11},
   {62,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,9,12},
   {63,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {64,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,8,11},
   {65,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,9,11},
   {66,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,9,12},
   {67,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,13,16},
   {68,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,16,19},
   {69,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,10,12},
   {70,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {71,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {72,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {73,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,8,10},
   {74,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,8,11},
   {75,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {76,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {77,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,9,11},
   {78,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,15,18},
   {79,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,9,11}
};

//Tableau représentant les agendas des interfaces, il est structuré de la manière suivante :
//- Le premier index correspondant à l'interface concernée
//- Le deuxième index correspond au jour de l'agenda
//- Le troisième index correspond à l'heure du jour (allant de 0 à 13, représentant les heures de 6 à 19)
int agenda_interfaces[NBR_INTERFACES][6][13];

typedef struct {
    int* intArray;
    int size;
    int capacity;
} IntegerArray;

//Tableau associant à chaque formation l'interface correspondante
IntegerArray formation_interface[NBR_INTERFACES];

IntegerArray initIntArray(int initSize)
{
    IntegerArray array;
    array.intArray = (int*)malloc(sizeof(int) * initSize);
    array.capacity = initSize;
    array.size = 0;
    return array;
}

void addElementIntArray(IntegerArray* a, int value)
{
    if(a != NULL)
    {
        if(a->size + 1 > a->capacity)
        {
            a->intArray = realloc(a->intArray, (a->capacity*=2) * sizeof(int));
        }
        a->size++;
        a->intArray[a->size-1] = value;
    }
}

void removeElementIntArray(IntegerArray* a)
{
    if(a->size>0)
    {
        a->intArray[a->size - 1] = 0;
        a->size--;
        a->intArray = realloc(a->intArray, a->size * sizeof(int));
    }
    else
    {
        a->intArray = NULL;
        free(a->intArray);
    }
}

void cleanIntArray(IntegerArray* a)
{
    while(a->intArray != NULL)
    {
        removeElementIntArray(&*a);
    }
}

//Permet de changer la ligne d'un tableau à 6 dimension grâce à une autre ligne de tableau
void fill_array(int *array_to_fill, int *filler)
{
    for(int i = 0; i < 6; i++)
        array_to_fill[i] = filler[i];
}

//Fusion de de deux tableaux délimités par debut-middle et middle+1 - fin
void merge(int debut, int middle, int fin)
{
    int borne1 = middle - debut + 1; //Borne de fin permettant de délimiter le tableau de gauche
    int borne2 = fin - middle; //Borne de fin permettant de délimiter le tableau de droite

    //Tableaux de gauche et de droite
    int temp_left[borne1][6];
    int temp_right[borne2][6];

    //Remplissage des tableaux temporaires représentant la partie gauche et la partie droite de notre tableau final
    for(int j = 0; j < borne2; j++)
        fill_array(temp_right[j], formation[middle + 1 + j]);

    for(int i = 0; i < borne1; i++)
        fill_array(temp_left[i], formation[debut + i]);


    int i = 0;
    int j = 0;
    int k = debut;

    while(i < borne1 && j < borne2)
    {
        //On tri sur la durée de la formation décroissante
        if((temp_left[i][5] - temp_left[i][4]) <= (temp_right[j][5] - temp_right[j][4]))
        {
            fill_array(formation[k], temp_right[j]);
            j++;
        }
        else
        {
            fill_array(formation[k], temp_left[i]);
            i++;
        }
        k++;
    }
    while(i < borne1)
    {
        fill_array(formation[k], temp_left[i]);
        k++;
        i++;
    }

    while(j < borne2)
    {
        fill_array(formation[k], temp_right[j]);
        k++;
        j++;
    }


}

//Cette fonction est un merge sort classique permettant de trier les formations des plus longues aux moins longues
void tri_horaires_formation(int debut, int fin)
{
    if(debut < fin)
    {
        int middle = debut + (fin - debut) / 2;

        tri_horaires_formation(debut, middle);//Tri tableau de gauche
        tri_horaires_formation(middle+1, fin);//Tri tableau de droite
        merge(debut, middle, fin);//Fusion des tableaux
    }

}

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

//Calcule le poids d'une interface afin d'avoir les interfaces ayant beaucoup de spécialités en haut de liste et les interfaces avec double compétences
//en fin de liste
int poids_interfaces(int spe[3], int comp[3])
{
    int poids = 0;
    if(comp[0] == 1 && comp[1] == 1)
        poids = -NBR_SPECIALITES - 1;
    return poids + spe[0] + spe[1] + spe[2];

}

void print_interfaces()
{
    for(int i = 0; i < NBR_FORMATIONS; i++)
        printf("\nInterface %d : \nCompetences : %d %d\nSpecialites : %d %d %d\n\n", i, competences_interfaces[i][0], competences_interfaces[i][1],
               specialite_interfaces[i][0], specialite_interfaces[i][1], specialite_interfaces[i][2]);
}

void merge_update_interfaces(int* update_spe, int* update_comp, int* spe_updater, int* comp_updater)
{
    for(int i = 0; i < NBR_SPECIALITES; i++)
        update_spe[i] = spe_updater[i];
    for(int i = 0; i < 2; i++)
        update_comp[i] = comp_updater[i];
}

void merge_interfaces(int debut, int middle, int fin)
{
    //Délimitations des 2 tableaux
    int borne1 = middle - debut + 1;
    int borne2 = fin - middle;

    //Tableaux temporaires (il y en a deux car on tri en même temps le tableau compétence et le tableau spécialités)
    int temp_comp_left[borne1][2];
    int temp_comp_right[borne2][2];
    int temp_spe_left[borne1][NBR_SPECIALITES];
    int temp_spe_right[borne2][NBR_SPECIALITES];

    //Remplissage des tableaux temporaires
    for(int j = 0; j < borne2; j++)
        merge_update_interfaces(temp_spe_right[j], temp_comp_right[j], specialite_interfaces[middle + 1 + j], competences_interfaces[middle + 1 + j]);

    for(int i = 0; i < borne1; i++)
        merge_update_interfaces(temp_spe_left[i], temp_comp_left[i], specialite_interfaces[debut + i], competences_interfaces[debut + i]);

    int i = 0;
    int j = 0;
    int k = debut;

    while(i < borne1 && j < borne2)
    {
        //Tri en fonction du poids retourné par la fonction (un poids fort indique une interface en tête de liste)
        if(poids_interfaces(temp_spe_left[i], temp_comp_left[i]) <= poids_interfaces(temp_spe_right[j], temp_comp_right[j]))
        {
            merge_update_interfaces(specialite_interfaces[k], competences_interfaces[k], temp_spe_right[j], temp_comp_right[j]);
            j++;

        }
        else
        {
            merge_update_interfaces(specialite_interfaces[k], competences_interfaces[k], temp_spe_left[i], temp_comp_left[i]);
            i++;
        }
        k++;
    }
    while(i < borne1)
    {
        merge_update_interfaces(specialite_interfaces[k], competences_interfaces[k], temp_spe_left[i], temp_comp_left[i]);
        k++;
        i++;
    }

    while(j < borne2)
    {
        merge_update_interfaces(specialite_interfaces[k], competences_interfaces[k], temp_spe_right[j], temp_comp_right[j]);
        k++;
        j++;
    }

}

//Merge sort classique
void tri_interfaces(int debut, int fin)
{
    if(debut < fin)
    {
        int middle = debut + (fin - debut) / 2;

        tri_interfaces(debut, middle);
        tri_interfaces(middle + 1, fin);
        merge_interfaces(debut, middle, fin);
    }
}

void init_agenda()
{
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            for(int p = 0; p < 13; p++)
                agenda_interfaces[i][j][p] = 0;
        }
    }
}

//Vérifie si l'interface à l'index index peut prendre le créneau passé en paramètre
//Elle le peut si :
//- Elle a la compétence requise (codage LPC ou langage des signes)
//- Elle n'a pas déjà de formation prévu à cette horaire
//- L'amplitude de sa journée ne dépasse pas 12h
//- Son nombre d'heures hebdomadaire ne dépasse pas 35h
//- Son nombre d'heures quotidiennes ne dépasse pas 8h
int check_compatibility(int index, int *creneau, int temps_creneau)
{
    //Verification compatibilité compétence
    if(creneau[2] == 0 && competences_interfaces[index][0] == 0)
        return -1;

    int jour_sem = creneau[3] - 1; //Jour de la formation passée en paramètre
    int map = creneau[4] - 6; //Le tableau agenda allant de 0 à 13, il faut mapper les heures de 6 à 19 pour qu'elles correspondent aux index du tableau

    //Verification de la compatibilité d'emploi du temps
    for(int i = 0; i < temps_creneau; i++)
    {
        if(agenda_interfaces[index][jour_sem][map + i] == 1) //Si il y a déjà un 1 dans le tableau agenda, alors cela signifie que l'heure est déjà prise
            return -1;
    }


    //On insere le nouveau creneau dans l'agenda de l'interface afin d'ensuite effectuer les tests de vérification
    int temp[13];
    for(int i = 0; i < 13; i++)
        temp[i] = agenda_interfaces[index][jour_sem][i];
    for(int i = 0; i < temps_creneau; i++)
        agenda_interfaces[index][jour_sem][map + i] = 1;

    //Verification de l'amplitude de la journée (12h maximum entre la première et dernière heure de travail)
    int p = 0;
    int premiere_heure = 0;
    while(p < 13 && agenda_interfaces[index][jour_sem][p] == 0)
        p++;

    if(p < 13)
    {
        premiere_heure = agenda_interfaces[index][jour_sem][p];
        int derniere_heure = 0;
        int p = 12;
        while(agenda_interfaces[index][jour_sem][p] == 0)
            p--;
        if(derniere_heure - premiere_heure > 12)
        {
            for(int i = 0; i < 13; i++)
            {
                agenda_interfaces[index][jour_sem][i] = temp[i];

            }
            return -1;
        }

    }

    //Verification du nombre d'heures de la journée
    int heures_journalieres = 0;
    for(int i = 0; i < 13; i++)
        heures_journalieres += agenda_interfaces[index][jour_sem][i];

    if(heures_journalieres > 8)
    {
        for(int i = 0; i < 13; i++)
        {
            agenda_interfaces[index][jour_sem][i] = temp[i];

        }
        return -1;
    }

    //Verification heures hebdomadaires
    int heures_hebdomadaires = 0;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            heures_hebdomadaires += agenda_interfaces[index][i][j];
        }
    }
    if(heures_hebdomadaires > 35)
    {
        for(int i = 0; i < 13; i++)
        {
            agenda_interfaces[index][jour_sem][i] = temp[i];

        }
        return -1;
    }

    for(int i = 0; i < temps_creneau; i++)
        {
            agenda_interfaces[index][jour_sem][creneau[4] - 6 + i] = 1;
        }

    return 0;
}

double computeDistance(double xa, double ya, double xb, double yb)
{
    double distance = 0;
    distance = pow(xa-xb, 2) + pow(ya-yb, 2);
    distance = sqrt(distance);
    return distance;
}


double computeEmployeeDistance(int i)
{
    double distance = 0;
    if (formation_interface[i].size == 0)
    {
        return 0;
    }
    else
    {
        for (int index = 0; index < formation_interface[i].size; index++)
        {
            // rajouter la distance du centre 0 au centre de formation
            distance += computeDistance(coord[0][0], coord[0][1], coord[formation[formation_interface[i].intArray[index]][1]+1][0], coord[formation[formation_interface[i].intArray[index]][1]+1][1]);

            // tant qu'il reste des formations ce jour la
            while (index != formation_interface[i].size && formation[formation_interface[i].intArray[index]][3] == formation[formation_interface[i].intArray[index+1]][3])
            {
                // rajouter la distance entre les centres de formation
                distance += computeDistance(coord[formation[formation_interface[i].intArray[index]][1]+1][0], coord[formation[formation_interface[i].intArray[index]][1]+1][1], coord[formation[formation_interface[i].intArray[index+1]][1]+1][0], coord[formation[formation_interface[i].intArray[index+1]][1]+1][1]);
                index += 1;
            }
            // rajouter le retour au centre 0
            distance += computeDistance(coord[0][0], coord[0][1], coord[formation[formation_interface[i].intArray[index]][1]+1][0], coord[formation[formation_interface[i].intArray[index]][1]+1][1]);

        }
    }
    return distance;
}

double computeAvgDistance()
{
    double total = 0;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
        total += computeEmployeeDistance(i);
    }
    total = total / NBR_INTERFACES;
    return total;
}

double computeStandardError(double avg)
{
    double total = 0;
    for (int i=0; i < NBR_INTERFACES; i++)
    {
        double current = 0, temp = 0;
        current = computeEmployeeDistance(i);
        temp = current - avg;
        total += pow(temp, 2);
    }
    total = total / NBR_INTERFACES;
    total = sqrt(total);
    return total;
}

double computeFcorr(double avg)
{
    double total = 0;
    total = avg * NBR_INTERFACES;
    total = total / NBR_FORMATION;
    return total;
}

int computePenalties()
{

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
                printf("%d ", agenda_interfaces[i][j][p]);
            }
            printf("\n");
        }
        printf("\nFormations prises en charge : ");
        for(int j = 0; j < formation_interface[i].size; j++)
        {
            printf("%d\n", formation_interface[i].intArray[j]);
        }
        printf("distance parcourue : %f", computeEmployeeDistance(i));
    }
}

void find_init_solution()
{


    tri_horaires_formation(0, NBR_FORMATIONS);
    tri_interfaces(0, NBR_FORMATIONS);

    //Affichage tableau formation et interfaces pour débuggage
    printf("\n*********************FORMATIONS****************\n");
    print_formation();
    printf("\n**********************INTERFACES************************\n");
    print_interfaces();
    //Initialisation de l'agenda à 0
    init_agenda();


    for(int i = 0; i < NBR_INTERFACES; i++)
        formation_interface[i] = initIntArray(1);

    //On cherche une solution en faisant rentrer le plus de formations dans les premieres interfaces
    for(int i = 0; i < NBR_FORMATIONS; i++)
    {
        int temps_creneau = formation[i][5] - formation[i][4]; //Durée d'une formation

        //On recherche la première interface pouvant prendre la formation, si on arrive au bout du tableau des interfaces sans avoir trouvé
        //d'interface valide, alors l'algorithme n'est pas capable de trouver de solution initiale valide
        int p = 0;
        while(check_compatibility(p, formation[i], temps_creneau) == -1 && p < NBR_FORMATIONS)
            p++;

        if(p >= NBR_FORMATIONS)
        {
            printf("Impossible d'assigner un des creneaux");
            exit(EXIT_FAILURE);
        }

        addElementIntArray(&formation_interface[p], i);

    }

    printf("\n*****************************AGENDA*************************\n");
    print_solution();

}

int main() {
    printf("NBR_INTERFACES=%d\n",NBR_INTERFACES) ;
    printf("NBR_APPRENANTS=%d\n",NBR_APPRENANTS) ;
    printf("NBR_FORMATIONS=%d\n",NBR_FORMATIONS) ;
    printf("NBR_NODES=%d\n",NBR_NODES) ;

    find_init_solution();
    return 0 ;
}

