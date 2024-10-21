#ifndef _ARRAY_H
#define _ARRAY_H
#include <stdlib.h>
#include <stdio.h>

void array_of_int_print(int *array, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void array_of_chars_print(char **array, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%16s ", array[i]);
  }
  printf("\n");
}

#endif // _ARRAY_H
