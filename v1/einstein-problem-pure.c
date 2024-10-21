#include <stdio.h>
#include <time.h>
#include "array.h"
#include "permutation.h"

typedef struct EinsteinProblem
{
    char *colors[5];
    char *beverages[5];
    char *cigarrets[5];
    char *animals[5];
    char *nationalities[5];
    char data[512];
    int complete;
} EinsteinProblem;

int index_of(char **array, char *elem)
{
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(array[i], elem) == 0)
        {
            return i;
        }
    }
    return -1;
}

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
                    same(problem->beverages, "Cerveja", problem->cigarrets, "BlueMaster") &&  //
                    side(problem->beverages, "Agua", problem->cigarrets, "Blend");

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
                    same(problem->animals, "Passaro", problem->cigarrets, "PallHall") &&   //
                    side(problem->animals, "Gato", problem->cigarrets, "Blend") &&         //
                    side(problem->animals, "Cavalo", problem->cigarrets, "Dunhill");

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
    Permutation cigarrets;
    permutation_init_static(&cigarrets, problem->cigarrets);

    do
    {
        int valid = same(problem->cigarrets, "Dunhill", problem->colors, "Amarelo") && //
                    same(problem->cigarrets, "Prince", problem->nationalities, "Alemao");

        if (valid)
            solve_level_4(problem);

        if (problem->complete)
            break;

        permutation_next(&cigarrets);
    } while (!cigarrets.completed);
    permutation_destroy(&cigarrets);
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

void einstein_problem_init(EinsteinProblem *problem)
{
    char *colors[] = {"Vermelho", "Verde", "Amarelo", "Azul", "Branco"};
    char *beverages[] = {"Agua", "Cerveja", "Cha", "Cafe", "Leite"};
    char *cigarrets[] = {"PallHall", "Dunhill", "BlueMaster", "Prince", "Blend"};
    char *animals[] = {"Cachorro", "Gato", "Cavalo", "Zebra", "Passaro"};
    char *nationalities[] = {"Noruegues", "Ingles", "Dinamarques", "Sueco", "Alemao"};

    int base = 16;
    problem->complete = 0;
    memset(problem->data, 0, base * 5 * 5 * sizeof(char));

    for (int i = 0; i < 5; i++)
    {
        problem->colors[i] = &problem->data[(i + (5 * 0)) * base];
        problem->beverages[i] = &problem->data[(i + (5 * 1)) * base];
        problem->cigarrets[i] = &problem->data[(i + (5 * 2)) * base];
        problem->animals[i] = &problem->data[(i + (5 * 3)) * base];
        problem->nationalities[i] = &problem->data[(i + (5 * 4)) * base];

        memcpy(problem->colors[i], colors[i], strlen(colors[i]));
        memcpy(problem->beverages[i], beverages[i], strlen(beverages[i]));
        memcpy(problem->cigarrets[i], cigarrets[i], strlen(cigarrets[i]));
        memcpy(problem->animals[i], animals[i], strlen(animals[i]));
        memcpy(problem->nationalities[i], nationalities[i], strlen(nationalities[i]));
    }
}

void einstein_problem_solve(EinsteinProblem *problem) { solve_level_1(problem); }

void einstein_problem_display(EinsteinProblem *problem)
{
    printf("Einstein Problem: %s\n", problem->complete ? "Solved" : "Not Solved");
    printf("Colors:        ");
    array_of_chars_print(problem->colors, 5);
    printf("Beverages:     ");
    array_of_chars_print(problem->beverages, 5);
    printf("Cigarettes:    ");
    array_of_chars_print(problem->cigarrets, 5);
    printf("Animals:       ");
    array_of_chars_print(problem->animals, 5);
    printf("Nationalities: ");
    array_of_chars_print(problem->nationalities, 5);
}

int main()
{
    EinsteinProblem problem;
    einstein_problem_init(&problem);
    einstein_problem_display(&problem);

    printf("\n");
    clock_t begin = clock();
    einstein_problem_solve(&problem);
    clock_t end = clock();
    printf("\n");

    einstein_problem_display(&problem);

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

#if defined(TIME_IT)
    printf("\n");
    printf("Time spent: %f seconds\n", time_spent);
#endif
    return 0;
}
