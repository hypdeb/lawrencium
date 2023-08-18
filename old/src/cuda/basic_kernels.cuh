#ifndef _LAWRENCIUM_SRC_BASIC_KERNELS_H_
#define _LAWRENCIUM_SRC_BASIC_KERNELS_H_

#include "cuda.h"

namespace lawrencium {
namespace cuda {

__global__ void add_kernel(float *A, float *B, float *C, int N);

__global__ void sum_rows_of_square_matrix(const float *matrix, float *result, const int sideLength);

__global__ void transpose_square_matrix(const float* inMatrix, float* outMatrix, const int sideLength);

__global__ void all_equal_to(const float* inVector, const int length, const float target, const float tolerance, bool *result);
} // namespace cuda
} // namespace lawrencium

#endif // _LAWRENCIUM_SRC_BASIC_KERNELS_H_