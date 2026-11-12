#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "parameters.h"

struct Parameters validateParamK(struct Parameters params, char *optarg) {
    uint64_t k = atoi(optarg);

    if (k <= 0) {
        printf("k must be a natural number\n");
        params.is_correct = false;
        return params;
    }

    params.k = k;
    
    return params;
}

struct Parameters validateParamPnum(struct Parameters params, char *optarg) {
    uint64_t pnum = atoi(optarg);

    if (pnum <= 0) {
        printf("pnum must be a natural number\n");
        params.is_correct = false;
        return params;
    }

    params.pnum = pnum;

    return params;
}

struct Parameters validateParamMod(struct Parameters params, char *optarg) {
    uint64_t mod = atoi(optarg);

    if (mod <= 0) {
        printf("mod must be a natural number\n");
        params.is_correct = false;
        return params;
    }

    params.mod = mod;
    
    return params;
}

struct Parameters getTerminalArgs(int argc, char **argv) {
    struct Parameters params;
    params.k = 0;
    params.pnum = 0;
    params.mod = 0;
    params.is_correct = true;

    while (true) {
        static struct option options[] = {{"k", required_argument, 0, 'k'},
                                          {"pnum", required_argument, 0, 'p'},
                                          {"mod", required_argument, 0, 'm'},
                                          {0, 0, 0, 0}};

        int option_index = 0;
        int c = getopt_long(argc, argv, "k:p:m:", options, NULL);

        if (c == -1) break;

        switch (c) {
            case 0:
                switch (option_index) {
                    case 0:
                        params = validateParamK(params, optarg); break;
                    case 1:
                        params = validateParamPnum(params, optarg); break;
                    case 2:
                        params = validateParamMod(params, optarg); break;

                    default:
                        printf("Index %d is out of options\n", option_index);
                }        
                break;

            case 'k':
                params = validateParamK(params, optarg); break;
            case 'p':
                params = validateParamPnum(params, optarg); break;
            case 'm':
                params = validateParamMod(params, optarg); break;

            default:
                printf("getopt returned character code 0%o?\n", c);
        }

        if (!params.is_correct) {
            return params;
        }
    }

    if (optind < argc) {
        printf("Has at least one no option argument\n");
        params.is_correct = false;
        return params;
    }

    if (params.k == 0 || params.pnum == 0 || params.mod == 0) {
        printf("Usage: %s --k \"num\" --pnum \"num\" --mod \"num\" \n",
               argv[0]);
        params.is_correct = false;
        return params;
    }

    if (params.pnum > params.k) {
        printf("The number of pnum must not exceed the k\n");
        params.is_correct = false;
        return params;
    }

    if (params.k % params.pnum != 0) {
        printf("pnum must be divided by k without remainder\n");
        
        params.is_correct = false;
        return params;
    }

    return params;
}
