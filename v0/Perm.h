#ifndef PERM_H
#define PERM_H

#include <stdio.h>
#include <stdlib.h>

void print_array_int(int *array, int n) {
  printf("[");
  n -= 1;
  for (int i = 0; i < n; i++) {
    printf("%d, ", array[i]);
  }
  if (n >= 0)
    printf("%d", array[n]);
  printf("]\n");
}

void copy_array_int(
  int *src, int *dst,
  int start, int end) {
  for (int i = start; i < end; i++) {
    dst[i] = src[i];
  }
}

#ifndef PERM_T
#define PERM_T int
#define PERM_T_PFLAG "%d"
#define PERM_BASE
#endif

void swap(PERM_T *array, int i, int j) {
  PERM_T aux = array[i];
  array[i] = array[j];
  array[j] = aux;
}

void print_array_perm(
  PERM_T *array, int n) {
  printf("[");
  n -= 1;
  for (int i = 0; i < n; i++) {
    printf(PERM_T_PFLAG", ", array[i]);
  }
  if (n >= 0)
    printf(PERM_T_PFLAG, array[n]);
  printf("]\n");
}

void copy_array_T(
  PERM_T *src, PERM_T *dst,
  int start, int end) {
  for (int i = start; i < end; i++) {
    dst[i] = src[i];
  }
}

void rotate_array(
  PERM_T *array,
  int start, int end) {
  PERM_T aux = array[start];
  copy_array_T(
    array + 1, array, start, end);
  array[end - 1] = aux;
}

typedef struct {
  PERM_T *data;
  int length;
  int *ks;
  int kn;
  int completed;
} Perm;

Perm perm_(
  PERM_T *data, PERM_T *array, int n) {
  copy_array_T(array, data, 0, n);
  int kn = n > 1 ? n - 1 : 0;
  
  int *ks = kn
    ? (int *) malloc(sizeof(PERM_T) * kn)
    : NULL;
  for (int i = 0; i < kn; i++)
    ks[i] = i;

  Perm p = {
    .data = data,
    .length = n,
    .ks = ks,
    .kn = kn,
    .completed = 0
  };
  return p;
}

Perm perm(PERM_T *array, int n) {
  PERM_T *data = 
    (PERM_T *) malloc(sizeof(PERM_T) * n);
  return perm_(data, array, n);
}

Perm copy_perm(Perm p) {
  PERM_T *data = (PERM_T *) malloc(sizeof(PERM_T) * p.length);
  int *ks = (int *) malloc(sizeof(int) * p.kn);
  Perm copy = {
    .data = data,
    .length = p.length,
    .kn = p.kn,
    .ks = ks,
    .completed = p.completed
  };
  copy_array_T(p.data, copy.data, 0, p.length);
  copy_array_int(p.ks, copy.ks, 0, p.kn);
  return copy;
}

void clear_perm(Perm* p) {
  free(p->data);
  if (p->kn) free(p->ks);
}

int completed_perm(Perm *p) {
  return p->completed;
}

void next_perm_mut(Perm *p) {
  if (p->length <= 1) {
    p->completed = 1;
    return;
  }

  if (completed_perm(p)) return;

  int n = p->length;
  int k = p->kn - 1;
  int *ks = p->ks;
  PERM_T *data = p->data;
 // p->_i -= 1;

  if (ks[k] + 1 != n) {
    rotate_array(data, k, n);
    ks[k] += 1;
  } else {
    while (k >= 0 && ks[k] + 1 == n) {
      ks[k] = k;
      rotate_array(data, k, n);
      k -= 1;
    }
    if (k >= 0) {
      rotate_array(data, k, n);
      ks[k] += 1;
    } else {
      p->completed = 1;
    }
  }
}

Perm next_perm_(Perm *p) {
  if (completed_perm(p)) return *p;
  Perm next = copy_perm(*p);
  next_perm_mut(&next);
  return next;
}

Perm next_perm(Perm *p) {
  if (completed_perm(p)) return *p;
  Perm next = next_perm_(p);
  clear_perm(p);
  return next;
}

void print_perm(Perm *p) {
  print_array_perm(p->data, p->length);
}

void print_perm_(Perm *p) {
  printf("%p\n", p->data);
  print_perm(p);
  print_array_int(p->ks, p->kn);
}

Perm next_print(Perm *p) {
  print_perm_(p);
  return next_perm(p);
}

void next_print_mut(Perm *p) {
  print_perm(p);
  next_perm_mut(p);
}

#if defined(PERM_BASE)
int test_perm() {
  int n = 8;
  int start = 8;
  int end = 8;
  int a1[] = {1,2,3,4,5,6,7,8};
  for (int i = start; i <= end; i++) {
    Perm p = perm(a1, i);
    int k = 1;
    while (!completed_perm(&p)) {
      printf("%5d ", k++);
      //p = next_print(&p);
      next_print_self(&p);
    }
    clear_perm(&p);
    printf("\n");
  }

  return 0;
}
#endif

#endif
