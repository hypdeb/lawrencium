#ifndef _LAWRENCIUM_CCPG_VECTORS_H_
#define _LAWRENCIUM_CUDA_VECTORS_H_

#include "vectors.h"
#include "helpers.h"
#include "shared.h"
#include <optional>

namespace library = lawrencium::ccpg::library;

constexpr int block_size
    = 128; // Should be set by tuning and depending on the device available.

__global__ void
AddKernel(const float *lhs, const float *rhs, float *result, const int length) {
  const auto index = threadIdx.x;
  if (index < length) {
    result[index] = lhs[index] + rhs[index];
  }
}

std::optional<library::GpuOperationException>
library::AddVectors(const library::GpuVector lhs,
                    const library::GpuVector rhs,
                    library::GpuVector result) {
  if (lhs.length != rhs.length) {
    return library::GpuOperationException{
        .errorMessage = "Left hand side and right hand side vectors do not "
                        "have the same length.",
    };
  }

  const auto vectorMemorySize = lhs.length * sizeof(float);
  float *device_lhs;
  cudaMalloc(&device_lhs, vectorMemorySize);
  cudaMemcpy(
      device_lhs, lhs.elements, vectorMemorySize, cudaMemcpyHostToDevice);
  float *device_rhs;
  cudaMalloc(&device_rhs, vectorMemorySize);
  cudaMemcpy(
      device_rhs, rhs.elements, vectorMemorySize, cudaMemcpyHostToDevice);
  float *device_result;
  cudaMalloc(&device_result, vectorMemorySize);

  const auto numBlocks = lhs.length / block_size + 1;
  AddKernel<<<numBlocks, block_size>>>(
      device_lhs, device_rhs, device_result, lhs.length);
  cudaMemcpy(
      result.elements, device_result, vectorMemorySize, cudaMemcpyDeviceToHost);
  CUDA_CHECK(cudaGetLastError());

  cudaFree(device_lhs);
  cudaFree(device_rhs);
  cudaFree(device_result);
  CUDA_CHECK(cudaGetLastError());

  return std::nullopt;
}

#endif