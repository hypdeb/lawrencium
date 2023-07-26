#ifndef _LAWRENCIUM_SRC_BASIC_KERNELS_H_
#define _LAWRENCIUM_SRC_BASIC_KERNELS_H_

#include "cuda.h"

namespace lawrencium {
namespace cuda {

__global__ void add_kernel(float *A, float *B, float *C, int N);
} // namespace cuda
} // namespace lawrencium

#endif // _LAWRENCIUM_SRC_BASIC_KERNELS_H_