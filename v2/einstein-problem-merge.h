#include <stdio.h>
#include <time.h>
#include "array.h"
#include "permutation.h"
#include "einstein-problem.h"

static inline int left(char **xs, char *x, char **ys, char *y) { return index_of(xs, x) + 1 == index_of(ys, y); }
static inline int side(char **xs, char *x, char **ys, char *y) { return left(xs, x, ys, y) || left(ys, y, xs, x); }
static inline int same(char **xs, char *x, char **ys, char *y) { return index_of(xs, x) == index_of(ys, y); }
static inline int in_index(char **xs, char *x, int i) { return index_of(xs, x) == i; }

static inline void solve_level(EinsteinProblem *problem, char **values, int (*rule)(EinsteinProblem *p), void (*next)(EinsteinProblem *p))
{
    Permutation permutation;
    permutation_init(&permutation, values, sizeof(values[0]), 5);
    int i = 0;
    do
    {
        if (rule(problem))
            next(problem);
        if (problem->complete)
            break;
        permutation_next(&permutation);
    } while (!permutation.completed);
    permutation_destroy(&permutation);
}

int rule_5(EinsteinProblem *problem)
{
    return (in_index(problem->beverages, "Leite", 2) &&
            same(problem->beverages, "Cha", problem->nationalities, "Dinamarques") &&
            same(problem->beverages, "Cafe", problem->colors, "Verde") &&
            same(problem->beverages, "Cerveja", problem->cigarettes, "BlueMaster") &&
            side(problem->beverages, "Agua", problem->cigarettes, "Blend"));
}

int rule_4(EinsteinProblem *problem)
{
    return (same(problem->animals, "Cachorro", problem->nationalities, "Sueco") &&
            same(problem->animals, "Passaro", problem->cigarettes, "PallHall") &&
            side(problem->animals, "Gato", problem->cigarettes, "Blend") &&
            side(problem->animals, "Cavalo", problem->cigarettes, "Dunhill"));
}

int rule_3(EinsteinProblem *problem)
{
    return (same(problem->cigarettes, "Dunhill", problem->colors, "Amarelo") &&
            same(problem->cigarettes, "Prince", problem->nationalities, "Alemao"));
}

int rule_2(EinsteinProblem *problem)
{
    return (in_index(problem->nationalities, "Noruegues", 0) &&
            same(problem->nationalities, "Ingles", problem->colors, "Vermelho") &&
            side(problem->nationalities, "Noruegues", problem->colors, "Azul"));
}

int rule_1(EinsteinProblem *problem)
{
    return left(problem->colors, "Verde", problem->colors, "Branco");
}

void solve_level_6(EinsteinProblem *problem) { problem->complete = 1; }
void solve_level_5(EinsteinProblem *problem) { solve_level(problem, problem->beverages, rule_5, solve_level_6); }
void solve_level_4(EinsteinProblem *problem) { solve_level(problem, problem->animals, rule_4, solve_level_5); }
void solve_level_3(EinsteinProblem *problem) { solve_level(problem, problem->cigarettes, rule_3, solve_level_4); }
void solve_level_2(EinsteinProblem *problem) { solve_level(problem, problem->nationalities, rule_2, solve_level_3); }
void solve_level_1(EinsteinProblem *problem) { solve_level(problem, problem->colors, rule_1, solve_level_2); }

void einstein_problem_solve(EinsteinProblem *problem) { solve_level_1(problem); }
