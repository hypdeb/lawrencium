#ifndef _LAWRENCIUM_SRC_CUDA_BASIC_CUDA_H_
#define _LAWRENCIUM_SRC_CUDA_BASIC_CUDA_H_

namespace lawrencium {
namespace cuda {
void cuda_add(float *A, float *B, float *C, int N);

bool is_doubly_stochastic(const float *A, const int N);
} // namespace cuda
} // namespace lawrencium

#endif // _LAWRENCIUM_SRC_CUDA_BASIC_CUDA_H_