#ifndef _LAWRENCIUM_SRC_CUDA_HELPERS_H_
#define _LAWRENCIUM_SRC_CUDA_HELPERS_H_

#define CUDA_CHECK(expr)                                                       \
  do {                                                                         \
    cudaError_t err = (expr);                                                  \
    if (err != cudaSuccess) {                                                  \
      fprintf(stderr, "CUDA Error Code  : %d\n     Error String: %s\n", err,   \
              cudaGetErrorString(err));                                        \
    }                                                                          \
  } while (0)

#endif // _LAWRENCIUM_SRC_CUDA_HELPERS_H_