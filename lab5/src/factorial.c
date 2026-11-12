#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <pthread.h>

#include "factorial.h"

void *factorial(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;

    uint64_t local_result = 1;

    for (uint64_t i = args->start; i <= args->end; i++) {
        local_result = (uint64_t)local_result * i % args->mod;
    }

    pthread_mutex_lock(args->mutex);

    *args->final_result = (uint64_t)(*args->final_result) * local_result % args->mod;

    pthread_mutex_unlock(args->mutex);

    return NULL;
}
