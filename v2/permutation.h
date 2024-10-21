#ifndef _PERMUTATION_H
#define _PERMUTATION_H
#include <stdlib.h>
#include <string.h>

typedef struct Permutation
{
  void *items;
  int size;
  int length;

  int completed;
  int *_ks;
} Permutation;

#define permutation_init_static(permutation, items) \
  permutation_init(permutation, items, sizeof(items[0]), sizeof(items) / sizeof(items[0]))

void permutation_init(Permutation *permutation, void* items, int size, int length);
void permutation_next(Permutation *permutation);
void permutation_destroy(Permutation *permutation);

#endif // _PERMUTATION_H

// TODO: #ifdef PERMUTATION_IMPLEMENTATION
#ifndef PERMUTATION_IMPLEMENTATION

inline static void rotate(void *array, int size, int start, int end)
{
  char tmp[64];
  memcpy(tmp, (char*)array + (size * start), size);
  memmove((char*)array + (size * start), (char*)array + (size * (start + 1)), size * (end - start - 1));
  memcpy((char*)array + (size * (end - 1)), tmp, size);
}

void permutation_init(Permutation *permutation, void* items, int size, int length)
{
  permutation->items = items;
  permutation->size = size;

  permutation->_ks = (int *)malloc((length - 1) * sizeof(int));
  permutation->length = length;
  permutation->completed = 0;

  for (int i = 0; i < length - 1; i++)
  {
    permutation->_ks[i] = i;
  }
}

void permutation_next(Permutation *permutation)
{
  int k = permutation->length - 2;

  if (permutation->_ks[k] + 1 != permutation->length)
  {
    rotate(permutation->items, permutation->size, k, permutation->length);
    permutation->_ks[k]++;
  }
  else
  {
    while (k >= 0 && permutation->_ks[k] + 1 == permutation->length)
    {
      permutation->_ks[k] = k;
      rotate(permutation->items, permutation->size, k, permutation->length);
      k--;
    }

    if (k >= 0)
    {
      rotate(permutation->items, permutation->size, k, permutation->length);
      permutation->_ks[k]++;
    } 
    else 
    {
      permutation->completed = 1;
    }
  }
}

void permutation_destroy(Permutation *permutation)
{
  free(permutation->_ks);
  permutation->length = 0;
  permutation->completed = 0;
}

#endif // PERMUTATION_IMPLEMENTATION
