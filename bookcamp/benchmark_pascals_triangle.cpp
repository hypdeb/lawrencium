#include "benchmark/benchmark.h"
#include "pascals_triangle.h"

namespace bookcamp = lawrencium::bookcamp;

static void pascals_triangle_with_copy(benchmark::State &state) {
  const int num_rows = 100;
  for (auto _ : state) {
    const auto triangle = bookcamp::generate_triangle_copy(num_rows);
  }
}

static void pascals_triangle_without_copy(benchmark::State &state) {
  const int num_rows = 100;
  for (auto _ : state) {
    const auto triangle = bookcamp::generate_triangle(num_rows);
  }
}

BENCHMARK(pascals_triangle_with_copy);
BENCHMARK(pascals_triangle_without_copy);

BENCHMARK_MAIN();