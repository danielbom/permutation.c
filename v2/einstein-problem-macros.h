#include <stdio.h>
#include <time.h>
#include "permutation.h"
#include "einstein-problem.h"

#define left(xs, x, ys, y) (index_of(xs, x) + 1 == index_of(ys, y))
#define side(xs, x, ys, y) (left(xs, x, ys, y) || left(ys, y, xs, x))
#define same(xs, x, ys, y) (index_of(xs, x) == index_of(ys, y))
#define in_index(xs, x, i) (index_of(xs, x) == i)

#define SOLVE_LEVEL(level, next, values)                      \
    static void solve_level_##level(EinsteinProblem *problem) \
    {                                                         \
        Permutation permutation;                              \
        permutation_init_static(&permutation, values);        \
        do                                                    \
        {                                                     \
            if (rule_##level(problem))                        \
                solve_level_##next(problem);                  \
            if (problem->complete)                            \
                break;                                        \
            permutation_next(&permutation);                   \
        } while (!permutation.completed);                     \
        permutation_destroy(&permutation);                    \
    }

#define rule_5(problem)                                                        \
    (in_index(problem->beverages, "Leite", 2) &&                               \
     same(problem->beverages, "Cha", problem->nationalities, "Dinamarques") && \
     same(problem->beverages, "Cafe", problem->colors, "Verde") &&             \
     same(problem->beverages, "Cerveja", problem->cigarettes, "BlueMaster") &&  \
     side(problem->beverages, "Agua", problem->cigarettes, "Blend"))

#define rule_4(problem)                                                     \
    (same(problem->animals, "Cachorro", problem->nationalities, "Sueco") && \
     same(problem->animals, "Passaro", problem->cigarettes, "PallHall") &&   \
     side(problem->animals, "Gato", problem->cigarettes, "Blend") &&         \
     side(problem->animals, "Cavalo", problem->cigarettes, "Dunhill"))

#define rule_3(problem)                                                 \
    (same(problem->cigarettes, "Dunhill", problem->colors, "Amarelo") && \
     same(problem->cigarettes, "Prince", problem->nationalities, "Alemao"))

#define rule_2(problem)                                                     \
    (in_index(problem->nationalities, "Noruegues", 0) &&                    \
     same(problem->nationalities, "Ingles", problem->colors, "Vermelho") && \
     side(problem->nationalities, "Noruegues", problem->colors, "Azul"))

#define rule_1(problem) \
    left(problem->colors, "Verde", problem->colors, "Branco")

void solve_level_6(EinsteinProblem *problem) { problem->complete = 1; }

SOLVE_LEVEL(5, 6, problem->beverages)
SOLVE_LEVEL(4, 5, problem->animals)
SOLVE_LEVEL(3, 4, problem->cigarettes)
SOLVE_LEVEL(2, 3, problem->nationalities)
SOLVE_LEVEL(1, 2, problem->colors)

void einstein_problem_solve(EinsteinProblem *problem) { solve_level_1(problem); }
