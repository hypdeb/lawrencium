#include "julia.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "helpers.h"
#include <vector>

namespace julia = lawrencium::ccpg::julia;

__device__ float julia::cuComplex::magnitude2() const { return r * r + i * i; }

__device__ julia::cuComplex
julia::cuComplex::operator*(const julia::cuComplex &a) const {
  return cuComplex{
      .r = r * a.r - i * a.i,
      .i = i * a.r + r * a.i,
  };
}

__device__ julia::cuComplex
julia::cuComplex::operator+(const julia::cuComplex &a) const {
  return cuComplex{
      .r = r + a.r,
      .i = i + a.i,
  };
}

__device__ int
EvaluateJulia(const int x, const int y, const int image_dimension) {
  const float jx = (float)(x - image_dimension / 2) / (image_dimension / 2);
  const float jy = (float)(y - image_dimension / 2) / (image_dimension / 2);

  const auto c = julia::cuComplex{
      .r = -0.8,
      .i = 0.158,
  };

  auto a = julia::cuComplex{
      .r = jx,
      .i = jy,
  };

  for (int i = 0; i < 200; i++) {
    a = a * a + c;
    if (a.magnitude2() > 1000) {
      return 0;
    }
  }
  return 1;
}

__global__ void JuliaKernel(unsigned char *bitmap, const int image_size) {
  const auto pixelX = blockIdx.x * blockDim.x + threadIdx.x;
  const auto pixelY = blockIdx.y * blockDim.y + threadIdx.y;
  if (pixelX < image_size && pixelY < image_size) {
    const auto bitmapOffset = pixelY * image_size + pixelX;
    const auto juliaValue = EvaluateJulia(pixelX, pixelY, image_size);

    // Don't mind the constants... just playing around with colours.
    bitmap[bitmapOffset * 4 + 0] = 196 * juliaValue;
    bitmap[bitmapOffset * 4 + 1] = 0;
    bitmap[bitmapOffset * 4 + 2] = 128 * juliaValue;
    bitmap[bitmapOffset * 4 + 3] = 128 + 128 * juliaValue;
  }
}

std::vector<unsigned char> julia::DrawOnGpu(const int image_dimension) {
  const auto totalSizeInPixels = image_dimension * image_dimension;
  const auto numberOfBytesPerPixel = 4;
  const auto numberOfBytesForBitmap = totalSizeInPixels * numberOfBytesPerPixel;
  unsigned char *d_bitmap;
  CUDA_CHECK(cudaMalloc(&d_bitmap, numberOfBytesForBitmap));
  const dim3 block_size(16, 16);
  const auto num_blocks = image_dimension / 16 + 1;
  const dim3 grid_size(num_blocks, num_blocks);
  JuliaKernel<<<grid_size, block_size>>>(d_bitmap, image_dimension);
  cudaDeviceSynchronize();
  CUDA_CHECK(cudaGetLastError());
  auto hostResult = std::vector<unsigned char>(numberOfBytesForBitmap);
  CUDA_CHECK(cudaMemcpy(hostResult.data(),
                        d_bitmap,
                        numberOfBytesForBitmap,
                        cudaMemcpyDeviceToHost));
  CUDA_CHECK(cudaFree(d_bitmap));
  CUDA_CHECK(cudaGetLastError());
  return hostResult;
}