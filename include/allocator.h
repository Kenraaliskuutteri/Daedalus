#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#define _DEFAULT_SOURCE
#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>

#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

typedef struct BlockHeader {
    size_t size;
    bool is_free;
    struct BlockHeader* next;
    struct BlockHeader* prev;
} BlockHeader;

#define BLOCK_HEADER_SIZE ALIGN(sizeof(BlockHeader))

void* daedalus_malloc(size_t size);
void daedalus_free(void* ptr);
void* daedalus_calloc(size_t nmemb, size_t size);
void* daedalus_realloc(void* ptr, size_t size);

void daedalus_heap_status(void);

#endif
