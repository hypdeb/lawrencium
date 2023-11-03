#ifndef _LAWRENCIUM_CCPG_MATRIXES_H_
#define _LAWRENCIUM_CCPG_MATRIXES_H_

namespace lawrencium {
namespace ccpg {
namespace library {

struct matrix {
  int width;
  int height;
  float *elements;
};

struct strided_matrix {
  int width;
  int height;
  int stride;
  float *elements;
};

void MatMul(const matrix lh, const matrix rh, matrix result);
void SharedMemoryMatMul(const matrix lh, const matrix rh, matrix result);
} // namespace library
} // namespace ccpg
} // namespace lawrencium

#endif