# Design

## Block Layout

Each allocation is preceded by a `BlockHeader`:

```c
typedef struct BlockHeader {
    size_t size;
    bool is_free;
    struct BlockHeader* next;
    struct BlockHeader* prev;
} BlockHeader;
```

The heap is an explicit doubly-linked list of these headers, grown on demand via `sbrk`. The pointer returned to the caller is `header + 1`; the header is recovered on `free`/`realloc` by subtracting one `BlockHeader` width from the user pointer.

## Allocation Strategy

`my_malloc` uses first-fit: it walks the list for the first free block large enough to satisfy the request. If none exists, the heap is extended with `sbrk`. A block found via first-fit is split when the remainder is large enough to hold another header plus at least one alignment unit, so oversized reuse doesn't waste more space than necessary.

## Coalescing

`my_free` marks a block free and merges it with an adjacent free neighbor in either direction, using `next`/`prev` to do this in O(1) relative to the block itself. This keeps the free list from fragmenting into many small unusable blocks over time.

## Concurrency

All heap mutation is guarded by a single global mutex. This is simple and correct but serializes all allocations across threads — there is no per-thread arena or lock striping.

## Known Limitations

- Memory is never returned to the OS; `sbrk` only grows.
- No dedicated path for large allocations (e.g. `mmap`-backed blocks).
- A single global lock will bottleneck under heavy multi-threaded allocation churn.
- First-fit is simple but not optimal for fragmentation compared to best-fit or segregated free lists.
