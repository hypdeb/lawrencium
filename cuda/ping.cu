#include "helpers.h"
#include "ping.h"

#include <math.h>
#include <cmath>
#include <cuda_runtime.h>

__global__ void kernel() {
  sin(0.); // nvcc - ok
}

void lawrencium::cuda::launch() {
  kernel<<<1, 1>>>();
  CUDA_CHECK(cudaGetLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
}