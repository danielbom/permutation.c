#include <stdio.h>
#include <time.h>
#include "array.h"
#include "permutation.h"

typedef struct EinsteinProblem
{
    char *colors[5];
    char *beverages[5];
    char *cigarettes[5];
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

void einstein_problem_init(EinsteinProblem *problem)
{
    char *colors[] = {"Vermelho", "Verde", "Amarelo", "Azul", "Branco"};
    char *beverages[] = {"Agua", "Cerveja", "Cha", "Cafe", "Leite"};
    char *cigarettes[] = {"PallHall", "Dunhill", "BlueMaster", "Prince", "Blend"};
    char *animals[] = {"Cachorro", "Gato", "Cavalo", "Zebra", "Passaro"};
    char *nationalities[] = {"Noruegues", "Ingles", "Dinamarques", "Sueco", "Alemao"};

    int base = 16;
    problem->complete = 0;
    memset(problem->data, 0, 512);

    for (int i = 0; i < 5; i++)
    {
        problem->colors[i] = &problem->data[(i + (5 * 0)) * base];
        problem->beverages[i] = &problem->data[(i + (5 * 1)) * base];
        problem->cigarettes[i] = &problem->data[(i + (5 * 2)) * base];
        problem->animals[i] = &problem->data[(i + (5 * 3)) * base];
        problem->nationalities[i] = &problem->data[(i + (5 * 4)) * base];

        memcpy(problem->colors[i], colors[i], strlen(colors[i]));
        memcpy(problem->beverages[i], beverages[i], strlen(beverages[i]));
        memcpy(problem->cigarettes[i], cigarettes[i], strlen(cigarettes[i]));
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
    array_of_chars_print(problem->cigarettes, 5);
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
