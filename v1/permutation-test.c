#include "array.h"
#include "permutation.h"

int main()
{
  int indexes[] = {0, 1, 2, 3, 4};
  Permutation p;
  permutation_init_static(&p, indexes);

  int i = 0;
  do {
    printf("Permutation % 4d: ", i);
    array_of_int_print(p.items, p.length);
    permutation_next(&p);
    i++;
  } while (!p.completed);

  permutation_destroy(&p);
  return 0;
}
