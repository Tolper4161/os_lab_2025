
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <stdint.h>

#include "factorial.h"
#include "parameters.h"

int main(int argc, char **argv) {

    struct Parameters params = getTerminalArgs(argc, argv);

    if (!params.is_correct) {
        return 1;
    }
    
    uint64_t k = params.k;
    uint64_t pnum = params.pnum;
    uint64_t mod = params.mod;

    uint64_t global_result = 1;

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    struct ThreadArgs *args = malloc(sizeof(struct ThreadArgs) * pnum);
    pthread_t *threads = malloc(sizeof(pthread_t) * pnum);
    
    if (args == NULL || threads == NULL) {
        perror("malloc");
        free(args);
        free(threads);
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    uint64_t chunk_size = k / pnum;

    for (uint64_t i = 0; i < pnum; i++) {
        args[i].start = i * chunk_size + 1;
        args[i].end = (i + 1) * chunk_size;
        args[i].mod = mod;
        args[i].final_result = &global_result;
        args[i].mutex = &mutex;
    }

    uint64_t created = 0;

    for (uint64_t i = 0; i < pnum; i++) {
        int status = pthread_create(
            &threads[i],
            NULL,
            factorial,
            &args[i]
        );

        if (status != 0) {
            printf("pthread_create failed: %d\n", status);
            break;
        }

        created++;
    }

    for (uint64_t i = 0; i < created; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Result: %lu\n", (unsigned long)global_result);

    free(args);
    free(threads);

    return 0;
}
