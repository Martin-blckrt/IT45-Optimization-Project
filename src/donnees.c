#include "constants.h"
#include "interface.h"
                  
                  
/* code des compétence en langage des signes et en codage LPC */
                  
/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]={
    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {1,1},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,1},
    {0,1},
    {0,1},
    {1,0},
    {1,1},
    {1,0},
    {0,1},
    {1,1},
    {1,1},
    {1,0},
    {1,0}
};
                  
/* spécialités des interfaces */
                  
/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    {0,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,1},
    {0,0,0,0,1},
    {0,0,0,0,0},
    {0,1,0,0,0},
    {0,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {0,0,0,0,0},
    {0,1,0,0,0},
    {0,1,0,1,1},
    {0,0,0,0,0},
    {0,0,1,1,1},
    {1,0,0,0,0},
    {0,0,0,1,0},
    {1,0,0,0,1},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,1,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {109,25}, /* centre 0 */
                  
    /* Centres de formation */
    {97,124}, /* ecole formation SPECIALITE_MENUISERIE */
    {42,62}, /* ecole formation SPECIALITE_ELECTRICITE */
    {84,123}, /* ecole formation SPECIALITE_MECANIQUE */
    {188,15}, /* ecole formation SPECIALITE_INFORMATIQUE */
    {18,28}, /* ecole formation SPECIALITE_CUISINE */
                  
    /* Apprenants */

};
                  
                  
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATIONS][6]={
   {0,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,8,10},
   {1,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,15,19},
   {2,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,14,18},
   {3,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,13,19},
   {4,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {5,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,13,19},
   {6,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,10,12},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {8,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,15,19},
   {9,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,8,10},
   {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,8,12},
   {11,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {12,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,13,16},
   {13,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,15,18},
   {14,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,16,18},
   {15,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MARDI,9,11},
   {16,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {17,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,8,10},
   {18,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,9,12},
   {19,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {20,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,13,18},
   {21,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,13,16},
   {22,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,9,12},
   {23,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MARDI,10,12},
   {24,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,14,17},
   {25,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,9,12},
   {26,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MERCREDI,8,10},
   {27,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,13,15},
   {28,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,8,11},
   {29,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,10,12},
   {30,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {31,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,13,17},
   {32,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,14,19},
   {33,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {34,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,15,18},
   {35,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,8,12},
   {36,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,10,12},
   {37,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,14,19},
   {38,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,16,19},
   {39,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,14,17},
   {40,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,13,16},
   {41,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,15,19},
   {42,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,8,11},
   {43,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,13,19},
   {44,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,16,18},
   {45,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,8,11},
   {46,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,13,19},
   {47,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,14,16},
   {48,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,10,12},
   {49,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,14,19},
   {50,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,16,19},
   {51,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,15,17},
   {52,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,8,11},
   {53,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,10,12},
   {54,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,10,12},
   {55,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,8,12},
   {56,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,10,12},
   {57,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,15,18},
   {58,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,8,10},
   {59,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,16,18},
   {60,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,10,12},
   {61,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,8,11},
   {62,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,13,15},
   {63,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,13,17},
   {64,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,9,12},
   {65,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {66,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,9,11},
   {67,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,14,18},
   {68,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {69,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,15,18},
   {70,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,14,18},
   {71,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,14,18},
   {72,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,13,17},
   {73,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,8,12},
   {74,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {75,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,9,12},
   {76,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MARDI,15,18},
   {77,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MERCREDI,14,19},
   {78,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {79,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,10,12}
};
                  
//Variables globales utilisees dans le reste du programme
double distances[NBR_SPECIALITES + 1][NBR_SPECIALITES + 1];
