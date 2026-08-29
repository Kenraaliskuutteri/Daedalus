#include "../include/allocator.h"
#include "test.h"
#include <stdint.h>

void run_calloc_tests(void) {
    int* arr = (int*)daedalus_calloc(8, sizeof(int));
    TEST_ASSERT(arr != NULL, "calloc returns non-null for a valid size");

    int zeroed = 1;
    for (int i = 0; i < 8; i++) {
        if (arr[i] != 0) zeroed = 0;
    }
    TEST_ASSERT(zeroed, "calloc zero-initializes memory");

    void* overflow = daedalus_calloc(SIZE_MAX, 2);
    TEST_ASSERT(overflow == NULL, "calloc rejects a size overflow");

    void* zero = daedalus_calloc(0, 8);
    TEST_ASSERT(zero == NULL, "calloc returns null for zero members");

    daedalus_free(arr);
}
