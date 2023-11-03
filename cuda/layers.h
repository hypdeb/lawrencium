#ifndef _LAWRENCIUM_CUDA_LAYERS_H_
#define _LAWRENCIUM_CUDA_LAYERS_H_

namespace lawrencium {
namespace cuda {

struct Kernel {
  int width;
  int height;
  int padding;
  int stride;
};

struct Batch {
  int batchSize;
  int numChannels;
  int width;
  int height;
  float *samples[]; // Batch size X numChannels X width X height.
};

void Convolve(const Batch input, Batch output, Kernel kernel);

} // namespace cuda
} // namespace lawrencium

#endif