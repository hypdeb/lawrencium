#ifndef _LAWRENCIUM_SRC_CUDA_ADD_H_
#define _LAWRENCIUM_SRC_CUDA_ADD_H_

#include "cuda.h"

namespace lawrencium {
namespace cuda {
void cuda_add(float *A, float *B, float *C, int N);
} // namespace cuda
} // namespace lawrencium

#endif // _LAWRENCIUM_SRC_CUDA_ADD_H_