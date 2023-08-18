#include "helpers.h"
#include "ping.h"

#include <math.h>
#include <cmath>

__global__ void kernel() {
  std::sin(0.); // nvcc - ok
  std::sin(0);  // nvcc - error, because no std::sin(int) override is available.
  sin(0);       // nvcc - same as above.

  sinf(0.);       // nvcc - ok
  std::sinf(0.);  // nvcc - no such function
}

void lawrencium::cuda::launch() {
  kernel<<<1, 1>>>();
  CUDA_CHECK(cudaGetLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
}