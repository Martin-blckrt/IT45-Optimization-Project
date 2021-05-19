#include <stdio.h>

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
float coord[NBR_NODES][2]={

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

void fill_array(int array_to_fill[][6], int filler[][6], int index1, int index2)
{
    for(int i = 0; i < 6; i++)
        array_to_fill[index1][i] = filler[index2][i];
}

void merge(int debut, int middle, int fin)
{
    int borne1 = middle - debut + 1;
    int borne2 = fin - middle;
    int temp_left[borne1][6];
    int temp_right[borne2][6];

    for(int j = 0; j < borne2; j++)
        fill_array(temp_right, formation, j, middle + 1 + j);

    for(int i = 0; i < borne1; i++)
        fill_array(temp_left, formation, i, debut + i);


    int i = 0;
    int j = 0;
    int k = debut;

    while(i < borne1 && j < borne2)
    {
        if((temp_left[i][5] - temp_left[i][4]) <= (temp_right[j][5] - temp_right[j][4]))
        {

            fill_array(formation, temp_right, k, j);
            j++;
        }
        else
        {
            fill_array(formation, temp_left, k, i);
            i++;
        }
        k++;
    }
    while(i < borne1)
    {
        fill_array(formation, temp_left, k, i);
        k++;
        i++;
    }

    while(j < borne2)
    {
        fill_array(formation, temp_right, k, j);
        k++;
        j++;
    }


}

void tri_horaires_formation(int debut, int fin)
{
    if(debut < fin)
    {
        int middle = debut + (fin - debut) / 2;


        tri_horaires_formation(debut, middle);
        tri_horaires_formation(middle+1, fin);
        merge(debut, middle, fin);
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

int poids_interfaces(int spe[][3], int comp[][2], int index)
{
    int poids = 0;
    if(comp[index][0] == 1 && comp[index][1] == 1)
        poids = -NBR_SPECIALITES - 1;
    return poids + spe[index][0] + spe[index][1] + spe[index][2];

}

void print_interfaces()
{
    for(int i = 0; i < NBR_INTERFACES; i++)
        printf("\nInterface %d : \nCompetences : %d %d\nSpecialites : %d %d %d\n\n", i, competences_interfaces[i][0], competences_interfaces[i][1],
               specialite_interfaces[i][0], specialite_interfaces[i][1], specialite_interfaces[i][2]);
}

void merge_update_interfaces(int update_spe[][3], int update_comp[][2], int spe_updater[][3], int comp_updater[][2], int index1, int index2)
{
    for(int i = 0; i < NBR_SPECIALITES; i++)
        update_spe[index1][i] = spe_updater[index2][i];
    for(int i = 0; i < 2; i++)
        update_comp[index1][i] = comp_updater[index2][i];
}

void merge_interfaces(int debut, int middle, int fin)
{
    int borne1 = middle - debut + 1;
    int borne2 = fin - middle;
    int temp_comp_left[borne1][2];
    int temp_comp_right[borne2][2];
    int temp_spe_left[borne1][NBR_SPECIALITES];
    int temp_spe_right[borne2][NBR_SPECIALITES];

    for(int j = 0; j < borne2; j++)
        merge_update_interfaces(temp_spe_right, temp_comp_right, specialite_interfaces, competences_interfaces, j, middle + 1 + j);

    for(int i = 0; i < borne1; i++)
        merge_update_interfaces(temp_spe_left, temp_comp_left, specialite_interfaces, competences_interfaces, i, debut + i);

    int i = 0;
    int j = 0;
    int k = debut;

    while(i < borne1 && j < borne2)
    {
        if(poids_interfaces(temp_spe_left, temp_comp_left, i) <= poids_interfaces(temp_spe_right, temp_comp_right, j))
        {
            merge_update_interfaces(specialite_interfaces, competences_interfaces, temp_spe_right, temp_comp_right, k, j);
            j++;

        }
        else
        {
            merge_update_interfaces(specialite_interfaces, competences_interfaces, temp_spe_left, temp_comp_left, k, i);
            i++;
        }
        k++;
    }
    while(i < borne1)
    {
        merge_update_interfaces(specialite_interfaces, competences_interfaces, temp_spe_left, temp_comp_left, k, i);
        k++;
        i++;
    }

    while(j < borne2)
    {
        merge_update_interfaces(specialite_interfaces, competences_interfaces, temp_spe_right, temp_comp_right, k, j);
        k++;
        j++;
    }

}
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

void find_init_solution()
{
    tri_horaires_formation(0, NBR_FORMATIONS);
    tri_interfaces(0, NBR_INTERFACES);
    //print_formation();
    //print_interfaces();


}

int main() {
    printf("NBR_INTERFACES=%d\n",NBR_INTERFACES) ;
    printf("NBR_APPRENANTS=%d\n",NBR_APPRENANTS) ;
    printf("NBR_FORMATIONS=%d\n",NBR_FORMATIONS) ;
    printf("NBR_NODES=%d\n",NBR_NODES) ;

    find_init_solution();
    return 0 ;
}

