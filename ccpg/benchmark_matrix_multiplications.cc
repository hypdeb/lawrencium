#include "benchmark/benchmark.h"
#include "common/utils.h"
#include "matrixes.h"

constexpr int side_length = 1024;

static void mat_mul_without_shared_memory(benchmark::State &state) {
  auto lh_elements
      = lawrencium::common::RandomVector(side_length * side_length);
  const auto lh = lawrencium::ccpg::library::matrix{
      .width = side_length,
      .height = side_length,
      .elements = lh_elements.data(),
  };
  auto rh_elements
      = lawrencium::common::RandomVector(side_length * side_length);
  const auto rh = lawrencium::ccpg::library::matrix{
      .width = side_length,
      .height = side_length,
      .elements = rh_elements.data(),
  };
  auto result_elements = std::vector<float>(side_length * side_length);
  auto result = lawrencium::ccpg::library::matrix{
      .width = side_length,
      .height = side_length,
      .elements = result_elements.data(),
  };
  for (auto _ : state) {
    lawrencium::ccpg::library::MatMul(lh, rh, result);
  }
}

static void mat_mul_with_shared_memory(benchmark::State &state) {
  auto lh_elements
      = lawrencium::common::RandomVector(side_length * side_length);
  const auto lh = lawrencium::ccpg::library::matrix{
      .width = side_length,
      .height = side_length,
      .elements = lh_elements.data(),
  };
  auto rh_elements
      = lawrencium::common::RandomVector(side_length * side_length);
  const auto rh = lawrencium::ccpg::library::matrix{
      .width = side_length,
      .height = side_length,
      .elements = rh_elements.data(),
  };
  auto result_elements = std::vector<float>(side_length * side_length);
  auto result = lawrencium::ccpg::library::matrix{
      .width = side_length,
      .height = side_length,
      .elements = result_elements.data(),
  };
  for (auto _ : state) {
    lawrencium::ccpg::library::SharedMemoryMatMul(lh, rh, result);
  }
}

BENCHMARK(mat_mul_without_shared_memory);
BENCHMARK(mat_mul_with_shared_memory);

BENCHMARK_MAIN();