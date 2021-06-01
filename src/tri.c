#include "tri.h"
#include "interface.h"

extern int formation[NBR_FORMATIONS][6];

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

int compare_interfaces_distance(const void *n1, const void *n2)
{
	const Interface *a = n1;
	const Interface *b = n2;
	
	if(a->distance_totale > b->distance_totale)
		return -1;
	else
		return 1;
}

int compare_penalties(const void *n1, const void *n2)
{
    const Interface *a = n1;
    const Interface *b = n2;

    if (a->nb_penalties > b->nb_penalties)
        return -1;
    else
        return 1;
}

int compare_agenda(const void *n1, const void *n2)
{
	const int *a = (const int*)n1;
	const int *b = (const int*)n2;
	if(formation[*a][4] < formation[*b][4])
		return -1;
	else
		return 1;
}
