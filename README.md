# Daedalus

A custom, lightweight memory allocator written in C. 

Daedalus provides custom implementations for standard dynamic memory management functions (`malloc`, `free`, `calloc`, and `realloc`). It includes a full unit testing suite, performance benchmarks against the system allocator, and dual build configuration via `Makefile` and `CMake`.

## Features

- **Core Memory Allocations**: Complete custom implementations of standard heap functions.
- **Double Build Support**: Ready-to-use support for both GNU `Make` and `CMake` workflow environments.
- **Unit Testing Suite**: Modular test cases covering allocation, reallocation, clearing, and freeing mechanisms.
- **Performance Benchmarking**: Included tools to measure speed and efficiency against `stdlib`.
- **Clean Structure**: Separated source, header, test, and benchmark directory organization.

---

## Getting Started

### Prerequisites

To build and run Daedalus, you need:
- A standard C compiler (`gcc` or `clang`)
- GNU `make` or `cmake` (3.10 or higher

### Building with Makefile

```bash
git clone https://github.com/Kenraaliskuutteri/Daedalus.git
cd Daedalus
make
