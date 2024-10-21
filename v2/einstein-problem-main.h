#include <time.h>
#include "einstein-problem.h"

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
