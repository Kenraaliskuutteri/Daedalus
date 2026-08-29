#include "../include/allocator.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    char* greeting = (char*)daedalus_malloc(32);
    strcpy(greeting, "hello from daedalus");
    printf("%s\n", greeting);

    int* nums = (int*)daedalus_calloc(10, sizeof(int));
    for (int i = 0; i < 10; i++) {
        nums[i] = i * i;
    }

    nums = (int*)daedalus_realloc(nums, 20 * sizeof(int));
    printf("nums[9] = %d\n", nums[9]);

    daedalus_free(greeting);
    daedalus_free(nums);

    return 0;
}
