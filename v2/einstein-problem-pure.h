#include <stdio.h>
#include <time.h>
#include "array.h"
#include "permutation.h"
#include "einstein-problem.h"

#define left(xs, x, ys, y) (index_of(xs, x) + 1 == index_of(ys, y))
#define side(xs, x, ys, y) (left(xs, x, ys, y) || left(ys, y, xs, x))
#define same(xs, x, ys, y) (index_of(xs, x) == index_of(ys, y))
#define in_index(xs, x, i) (index_of(xs, x) == i)

static void solve_level_5(EinsteinProblem *problem)
{
    Permutation beverages;
    permutation_init_static(&beverages, problem->beverages);

    do
    {
        int valid = in_index(problem->beverages, "Leite", 2) &&                               //
                    same(problem->beverages, "Cha", problem->nationalities, "Dinamarques") && //
                    same(problem->beverages, "Cafe", problem->colors, "Verde") &&             //
                    same(problem->beverages, "Cerveja", problem->cigarettes, "BlueMaster") &&  //
                    side(problem->beverages, "Agua", problem->cigarettes, "Blend");

        if (valid)
            problem->complete = 1;

        if (problem->complete)
            break;

        permutation_next(&beverages);
    } while (!beverages.completed);
    permutation_destroy(&beverages);
}

static void solve_level_4(EinsteinProblem *problem)
{
    Permutation animals;
    permutation_init_static(&animals, problem->animals);

    do
    {
        int valid = same(problem->animals, "Cachorro", problem->nationalities, "Sueco") && //
                    same(problem->animals, "Passaro", problem->cigarettes, "PallHall") &&   //
                    side(problem->animals, "Gato", problem->cigarettes, "Blend") &&         //
                    side(problem->animals, "Cavalo", problem->cigarettes, "Dunhill");

        if (valid)
            solve_level_5(problem);

        if (problem->complete)
            break;

        permutation_next(&animals);
    } while (!animals.completed);
    permutation_destroy(&animals);
}

static void solve_level_3(EinsteinProblem *problem)
{
    Permutation cigarettes;
    permutation_init_static(&cigarettes, problem->cigarettes);

    do
    {
        int valid = same(problem->cigarettes, "Dunhill", problem->colors, "Amarelo") && //
                    same(problem->cigarettes, "Prince", problem->nationalities, "Alemao");

        if (valid)
            solve_level_4(problem);

        if (problem->complete)
            break;

        permutation_next(&cigarettes);
    } while (!cigarettes.completed);
    permutation_destroy(&cigarettes);
}

static void solve_level_2(EinsteinProblem *problem)
{
    Permutation nationalities;
    permutation_init_static(&nationalities, problem->nationalities);

    do
    {
        int valid = in_index(problem->nationalities, "Noruegues", 0) &&                    //
                    same(problem->nationalities, "Ingles", problem->colors, "Vermelho") && //
                    side(problem->nationalities, "Noruegues", problem->colors, "Azul");

        if (valid)
            solve_level_3(problem);

        if (problem->complete)
            break;

        permutation_next(&nationalities);
    } while (!nationalities.completed);
    permutation_destroy(&nationalities);
}

static void solve_level_1(EinsteinProblem *problem)
{
    Permutation colors;
    permutation_init_static(&colors, problem->colors);

    do
    {
        int valid = left(problem->colors, "Verde", problem->colors, "Branco");

        if (valid)
            solve_level_2(problem);

        if (problem->complete)
            break;

        permutation_next(&colors);
    } while (!colors.completed);
    permutation_destroy(&colors);
}

void einstein_problem_solve(EinsteinProblem *problem) { solve_level_1(problem); }
