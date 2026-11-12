#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <stdint.h>
#include <pthread.h>

struct ThreadArgs {
    uint64_t start;
    uint64_t end;
    uint64_t mod;

    uint64_t *final_result;
    pthread_mutex_t *mutex;
};

void *factorial(void *arg);

#endif
