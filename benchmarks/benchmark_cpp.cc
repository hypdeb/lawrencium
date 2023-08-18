#include "benchmark/benchmark.h"
#include "src/cpp/common.h"
#include "src/cpp/matrixes.h"
#include <vector>

static void CreateMatrixWithViews(benchmark::State &state) {
  const uint sideLength = 1000;
  for (auto _ : state) {
    const auto matrix = lawrencium::cpp::matrixes::DiagonalMatrix<
        float, decltype(sideLength)>(sideLength, 0.02);
  }
}

static void CreateMatrixWithRawLoop(benchmark::State &state) {
  const int sideLength = 1000;
  for (auto _ : state) {
    const auto matrix
        = lawrencium::cpp::DiagonalMatrixRawLoop<float>(sideLength, 0.02);
  }
}

BENCHMARK(CreateMatrixWithViews);
BENCHMARK(CreateMatrixWithRawLoop);

BENCHMARK_MAIN();