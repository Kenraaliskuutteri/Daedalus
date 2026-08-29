#include "../include/allocator.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static BlockHeader* heap_start = NULL;
static pthread_mutex_t global_malloc_lock = PTHREAD_MUTEX_INITIALIZER;

static BlockHeader* find_free_block(BlockHeader** last, size_t size) {
    BlockHeader* current = heap_start;
    while (current && !(current->is_free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

static BlockHeader* request_space(BlockHeader* last, size_t size) {
    BlockHeader* block = sbrk(0);
    void* request = sbrk(size + BLOCK_HEADER_SIZE);

    if (request == (void*)-1) {
        return NULL;
    }

    if (last) {
        last->next = block;
    }

    block->size = size;
    block->next = NULL;
    block->prev = last;
    block->is_free = false;
    return block;
}

static void split_block(BlockHeader* block, size_t size) {
    if (block->size < size + BLOCK_HEADER_SIZE + ALIGNMENT) {
        return;
    }

    BlockHeader* new_block = (BlockHeader*)((char*)(block + 1) + size);
    new_block->size = block->size - size - BLOCK_HEADER_SIZE;
    new_block->is_free = true;
    new_block->next = block->next;
    new_block->prev = block;

    if (new_block->next) {
        new_block->next->prev = new_block;
    }

    block->size = size;
    block->next = new_block;
}

static void coalesce(BlockHeader* block) {
    if (block->next && block->next->is_free) {
        block->size += BLOCK_HEADER_SIZE + block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }

    if (block->prev && block->prev->is_free) {
        coalesce(block->prev);
    }
}

void* daedalus_malloc(size_t size) {
    if (size == 0) return NULL;

    size_t aligned_size = ALIGN(size);
    BlockHeader* block;

    pthread_mutex_lock(&global_malloc_lock);

    if (!heap_start) {
        block = request_space(NULL, aligned_size);
        if (!block) {
            pthread_mutex_unlock(&global_malloc_lock);
            return NULL;
        }
        heap_start = block;
    } else {
        BlockHeader* last = heap_start;
        block = find_free_block(&last, aligned_size);
        if (!block) {
            block = request_space(last, aligned_size);
            if (!block) {
                pthread_mutex_unlock(&global_malloc_lock);
                return NULL;
            }
        } else {
            split_block(block, aligned_size);
            block->is_free = false;
        }
    }

    pthread_mutex_unlock(&global_malloc_lock);
    return (void*)(block + 1);
}

void daedalus_free(void* ptr) {
    if (!ptr) return;

    pthread_mutex_lock(&global_malloc_lock);

    BlockHeader* block = (BlockHeader*)ptr - 1;
    block->is_free = true;
    coalesce(block);

    pthread_mutex_unlock(&global_malloc_lock);
}

void* daedalus_calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) return NULL;
    if (nmemb > SIZE_MAX / size) return NULL;

    size_t total_size = nmemb * size;
    void* ptr = daedalus_malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}

void* daedalus_realloc(void* ptr, size_t size) {
    if (!ptr) return daedalus_malloc(size);
    if (size == 0) {
        daedalus_free(ptr);
        return NULL;
    }

    BlockHeader* block = (BlockHeader*)ptr - 1;
    size_t aligned_size = ALIGN(size);
    if (block->size >= aligned_size) return ptr;

    void* new_ptr = daedalus_malloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);
        daedalus_free(ptr);
    }
    return new_ptr;
}

void daedalus_heap_status(void) {
    BlockHeader* current = heap_start;
    printf("\n--- Heap Status ---\n");
    while (current) {
        printf("[%p] size=%zu free=%s\n",
               (void*)current, current->size, current->is_free ? "yes" : "no");
        current = current->next;
    }
    printf("-------------------\n");
}
