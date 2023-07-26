#include "basic_kernels.cuh"

__global__ void lawrencium::cuda::add_kernel(float *A, float *B, float *C, int N) {
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < N)
    C[i] = A[i] + B[i];
}