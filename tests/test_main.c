#include <stdio.h>
#include "all_tests.h"

int tests_run = 0;
int tests_failed = 0;

int main(void) {
    run_malloc_tests();
    run_free_tests();
    run_calloc_tests();
    run_realloc_tests();

    printf("%d/%d tests passed\n", tests_run - tests_failed, tests_run);
    return tests_failed == 0 ? 0 : 1;
}
