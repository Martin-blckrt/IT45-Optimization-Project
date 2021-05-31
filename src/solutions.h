#include "constants.h"
#include "interface.h"

typedef struct
{
	Interface interface[NBR_INTERFACES];
	double avg_distance;
	double standard_error;
	double fcorr;
	double z;
	int penalties;
} Solution;

int get_champs_formation(int, int);

void solve();

void find_init_solution(Solution *);

void improve_solution(Solution *);

void improve_standard_error(Solution*);

void update_solution(Solution *);

double compute_distance(double, double, double, double);

double compute_avg_distance(Solution);

double compute_standard_error(Solution, double);

double compute_fcorr(double);

int compute_penalties(Solution);

double compute_min_z(double avg, double std, double fcorr, double penalty);

void print_formation();

void print_solution(Solution);

void print_distances();
