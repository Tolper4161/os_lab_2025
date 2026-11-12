#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <stdint.h>
#include <stdbool.h>

struct Parameters {
    uint64_t k;
    uint64_t pnum;
    uint64_t mod;
    bool is_correct;
};

struct Parameters getTerminalArgs(int argc, char **argv);

#endif
