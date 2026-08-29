#include "../include/allocator.h"
#include "test.h"

void run_malloc_tests(void) {
    void* p = daedalus_malloc(64);
    TEST_ASSERT(p != NULL, "malloc returns non-null for a valid size");

    void* zero = daedalus_malloc(0);
    TEST_ASSERT(zero == NULL, "malloc returns null for a zero size");

    int* arr = (int*)daedalus_malloc(10 * sizeof(int));
    TEST_ASSERT(arr != NULL, "malloc succeeds for an array");

    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    int intact = 1;
    for (int i = 0; i < 10; i++) {
        if (arr[i] != i) intact = 0;
    }
    TEST_ASSERT(intact, "written values persist after allocation");

    daedalus_free(p);
    daedalus_free(arr);
}
