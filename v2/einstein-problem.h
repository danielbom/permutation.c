#ifndef _EINSTEIN_PROBLEM
#define _EINSTEIN_PROBLEM
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void einstein_problem_solve(EinsteinProblem *problem);

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

#endif
