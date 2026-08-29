#include "../include/allocator.h"
#include "test.h"

void run_free_tests(void) {
    void* p = daedalus_malloc(48);
    TEST_ASSERT(p != NULL, "allocation before free succeeds");
    daedalus_free(p);

    void* q = daedalus_malloc(48);
    TEST_ASSERT(q != NULL, "allocation after free succeeds");
    daedalus_free(q);

    daedalus_free(NULL);
    TEST_ASSERT(1, "freeing a null pointer is a no-op");
}
