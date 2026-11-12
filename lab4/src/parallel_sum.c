#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <pthread.h>
#include <getopt.h>
#include <time.h>

#include "utils.h"
#include "sum.h"

int main(int argc, char **argv) {

  uint32_t threads_num = 0;
  uint32_t array_size = 0;
  uint32_t seed = 0;

  struct timespec start, end;
  
  while (true) {
    static struct option options[] = {{"threads_num", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"seed", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            threads_num = atoi(optarg);

            if (threads_num <= 0) {
              printf("threads_num must be a natural number\n");
              return 1;
            }

            break;
          case 1:
            array_size = atoi(optarg);

            if (array_size <= 0) {
              printf("array_size must be a natural number\n");
              return 1;
            }

            break;
          case 2:
            seed = atoi(optarg);
            
            if (seed <= 0) {
              printf("seed must be a natural number\n");
              return 1;
            }
            
            break;

          default:
            printf("Index %d is out of options\n", option_index);
        }
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (threads_num == 0 || array_size == 0 || seed == 0) {
    printf("Usage: %s --threads_num \"num\" --array_size \"num\" --seed \"num\" \n",
           argv[0]);
    return 1;
  }

  if (threads_num > array_size) {
    printf("The number of pnum must not exceed the size of the array_size\n");
    return 1;
  }

  if (array_size % threads_num != 0) {
    printf("The size of the array must be divided by the number of processes without remainder\n");
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  if (array == NULL) {
    perror("malloc");
    return 1;
  }
  GenerateArray(array, array_size, seed);
  
  for (int i = 0; i < array_size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  struct SumArgs args[threads_num];

  for (uint32_t i = 0; i < threads_num; i++) {
    args[i].array = array;
    args[i].begin = array_size / threads_num * i;
    args[i].end = array_size / threads_num * (i + 1);
  }

  pthread_t *threads = malloc(sizeof(pthread_t) * threads_num);
  if (threads == NULL) {
    perror("malloc");
    free(array);
    return 1;
  }

  clock_gettime(CLOCK_MONOTONIC, &start);

  uint32_t created = 0;

  for (uint32_t i = 0; i < threads_num; i++) {
    int error = pthread_create(&threads[i], NULL, ThreadSum, &args[i]);

    if (error != 0) {
        printf("pthread_create failed: %d\n", error);
        break;
    }

    created++;
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      printf("pthread_join failed!\n");
      return 1;
    }
    total_sum += args[i].sum;
  }

  clock_gettime(CLOCK_MONOTONIC, &end);

  double time_delta =
    (end.tv_sec - start.tv_sec) +
    (end.tv_nsec - start.tv_nsec) / 1e9;

  free(array);
  free(threads);

  printf("Total: %d\n", total_sum);
  printf("Time: %.6f seconds\n", time_delta);

  return 0;
}
