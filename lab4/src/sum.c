#include <stdio.h>
#include <stdlib.h>

#include "sum.h"

int Sum(const struct SumArgs *args) {
  int sum = 0;
  
  for (int i = args->begin; i < args->end; i++) {
    sum += args->array[i];
  }

  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = args;

  sum_args->sum = Sum(sum_args);

  return NULL;
}
