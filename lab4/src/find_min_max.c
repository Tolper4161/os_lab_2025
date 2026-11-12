#include "find_min_max.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for(unsigned int i = begin; i < end; i++) {
    if (array[i] < min_max.min) {
      min_max.min = array[i];
    }
    if (array[i] > min_max.max) {
      min_max.max = array[i];
    }
  }
  
  return min_max;
}

// int main() {
//   srand(time(NULL));

//   unsigned int n, a, b;

//   printf("Введите количество элементов (больше 4) для генерации: ");
//   scanf("%u", &n);

//   if (n <= 0) {
//     printf("Количество элементов должно быть натуральным числом, большим 4\n");
//     return 0;
//   }

//   int *array = (int*)malloc(n * sizeof(int));

//   if (array == NULL) {
//     printf("Ошибка выделения памяти!\n");
//     return 1;
//   }

//   for (int i = 0; i < n; i++) {
//     array[i] = rand() % 100;
//     printf("%d ", array[i]);
//   }
//   printf("\n\n");

//   printf("Введите начальный индекс поиска (a): ");
//   scanf("%u", &a);

//   if (a <= 0) {
//     printf("Начальный индекс поиска должен быть натуральным числом");
//     return 0;
//   }

//   printf("Введите конечный индекс поиска (b > a): ");
//   scanf("%u", &b);

//   if (b <= 0) {
//     printf("Конечный индекс поиска должен быть натуральным числом");
//     free(array);
//     return 0;
//   }
//   if (b <= a) {
//     printf("Конечный индекс поиска должен превышать a");
//     free(array);
//     return 0;
//   }
//   if (b > n) {
//     printf("Конечный индекс поиска не может быть больше размера массива (%u)\n", n);
//     free(array);
//     return 0;
//   }

//   struct MinMax min_max = GetMinMax(array, a, b);

//   printf("Min = %d\nMax = %d\n", min_max.min, min_max.max);

//   free(array);
//   return 0;
// }
