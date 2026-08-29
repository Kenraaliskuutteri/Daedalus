#include "../include/allocator.h"
#include "test.h"
#include <string.h>

void run_realloc_tests(void) {
    char* buf = (char*)daedalus_malloc(16);
    strcpy(buf, "daedalus");

    char* grown = (char*)daedalus_realloc(buf, 64);
    TEST_ASSERT(grown != NULL, "realloc succeeds when growing");
    TEST_ASSERT(strcmp(grown, "daedalus") == 0, "realloc preserves existing data");

    void* from_null = daedalus_realloc(NULL, 32);
    TEST_ASSERT(from_null != NULL, "realloc on a null pointer behaves like malloc");

    void* freed = daedalus_realloc(grown, 0);
    TEST_ASSERT(freed == NULL, "realloc with size zero frees and returns null");

    daedalus_free(from_null);
}
