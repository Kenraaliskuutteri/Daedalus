#include "../include/allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERATIONS 100000

static double bench_daedalus(void) {
    clock_t start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        void* p = daedalus_malloc(64);
        daedalus_free(p);
    }
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

static double bench_system(void) {
    clock_t start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        void* p = malloc(64);
        free(p);
    }
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

int main(void) {
    printf("daedalus: %.4fs\n", bench_daedalus());
    printf("system:   %.4fs\n", bench_system());
    return 0;
}
