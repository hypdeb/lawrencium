#include "helpers.h"
#include "basic_cuda.cuh"
#include "basic_kernels.cuh"

void lawrencium::cuda::cuda_add(float *A, float *B, float *C, int N) {
  const auto size = N * sizeof(float);

  float *d_A;
  CUDA_CHECK(cudaMalloc(&d_A, size));
  float *d_B;
  CUDA_CHECK(cudaMalloc(&d_B, size));
  float *d_C;
  CUDA_CHECK(cudaMalloc(&d_C, size));
  CUDA_CHECK(cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice));
  CUDA_CHECK(cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice));
  int threadsPerBlock = 256;
  int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
  lawrencium::cuda::add_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

  CUDA_CHECK(cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost));

  CUDA_CHECK(cudaFree(d_A));
  CUDA_CHECK(cudaFree(d_B));
  CUDA_CHECK(cudaFree(d_C));

  CUDA_CHECK(cudaGetLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
};