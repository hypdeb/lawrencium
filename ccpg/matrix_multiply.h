#ifndef _LAWRENCIUM_CCPG_MATRIX_MULTIPLY_H_
#define _LAWRENCIUM_CUDA_MATRIX_MULTIPLY_H_

namespace lawrencium {
namespace ccpg {
namespace library {

struct matrix {
  int width;
  int height;
  float *elements;
};

void MatMul(const matrix lh, const matrix rh, matrix result);
} // namespace library
} // namespace ccpg
} // namespace lawrencium

#endif