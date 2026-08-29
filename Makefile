CC = gcc
CFLAGS = -Wall -Wextra -g -O0 -Iinclude
LDFLAGS = -pthread

SRC = src/allocator.c
OBJ = $(SRC:.c=.o)
TARGET = libdaedalus.a

TEST_SRC = tests/test_main.c tests/test_malloc.c tests/test_free.c tests/test_calloc.c tests/test_realloc.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = test_runner

EXAMPLE_SRC = examples/basic_usage.c
EXAMPLE_OBJ = $(EXAMPLE_SRC:.c=.o)
EXAMPLE_TARGET = example_basic_usage

BENCH_SRC = benchmarks/bench_malloc.c
BENCH_OBJ = $(BENCH_SRC:.c=.o)
BENCH_TARGET = bench_malloc

all: $(TARGET) $(TEST_TARGET) $(EXAMPLE_TARGET) $(BENCH_TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

$(TEST_TARGET): $(TEST_OBJ) $(TARGET)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) -L. -l:$(TARGET) $(LDFLAGS)

$(EXAMPLE_TARGET): $(EXAMPLE_OBJ) $(TARGET)
	$(CC) $(CFLAGS) -o $@ $(EXAMPLE_OBJ) -L. -l:$(TARGET) $(LDFLAGS)

$(BENCH_TARGET): $(BENCH_OBJ) $(TARGET)
	$(CC) $(CFLAGS) -o $@ $(BENCH_OBJ) -L. -l:$(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f src/*.o tests/*.o examples/*.o benchmarks/*.o $(TARGET) $(TEST_TARGET) $(EXAMPLE_TARGET) $(BENCH_TARGET)

.PHONY: all clean test
