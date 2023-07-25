#include "helpers.h"
#include "ping.h"

#include <iostream>

__global__ void kernel() {
  printf("cuda kernel called!\n");
}

void lawrencium::cuda::launch() {
  kernel<<<1, 1>>>();
  CUDA_CHECK(cudaGetLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
}