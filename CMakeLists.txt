cmake_minimum_required(VERSION 3.10)
project(daedalus C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_library(daedalus STATIC src/allocator.c)
target_include_directories(daedalus PUBLIC include)
target_link_libraries(daedalus PUBLIC Threads::Threads)

add_executable(test_runner
    tests/test_main.c
    tests/test_malloc.c
    tests/test_free.c
    tests/test_calloc.c
    tests/test_realloc.c
)
target_link_libraries(test_runner PRIVATE daedalus)

add_executable(example_basic_usage examples/basic_usage.c)
target_link_libraries(example_basic_usage PRIVATE daedalus)

add_executable(bench_malloc benchmarks/bench_malloc.c)
target_link_libraries(bench_malloc PRIVATE daedalus)
