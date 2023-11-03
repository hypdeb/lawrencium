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
    bitmap[bitmapOffset * 4 + 0] = 255 * juliaValue;
    bitmap[bitmapOffset * 4 + 1] = 255 * juliaValue / 2;
    bitmap[bitmapOffset * 4 + 2] = 255 * juliaValue / 4;
    bitmap[bitmapOffset * 4 + 3] = 255;
  }
}

// Given the offset of some pixel in the bitmap, gets the offset of some
// neighbour by specifying a relative position in the image (2D offset).
// Moreover this function assumes the result will be in bounds.
// Function is named with "Global" because we hope we will be able to write
// another version which doesn't have to look at the whole bitmap, but only at a
// smaller neighbourhood that we can put in shared memory.
__device__ int GetGlobalNeighbourBitmapOffset(const unsigned char *bitmap,
                                              const int image_size,
                                              const int pixelOffset,
                                              const int relativeXOffset,
                                              const int relativeYOffset) {
  return pixelOffset * 4 + (relativeYOffset * image_size + relativeXOffset) * 4;
}

// Returns zero if the value at the given offsets w.r.t. the given pixel is in
// the image, zero otherwise.
__device__ bool GetGlobalBoundCheckingMask(const int image_size,
                                           const int pixelX,
                                           const int pixelY,
                                           const int relativeXOffset,
                                           const int relativeYOffset) {
  const auto targetX = pixelX + relativeXOffset;
  const auto targetY = pixelY + relativeYOffset;
  const auto xIsInBound = targetX < image_size && targetX >= 0;
  const auto yIsInBound = targetY < image_size && targetY >= 0;
  return xIsInBound && yIsInBound;
}

// Non-parametrizable, naive way, in a first step.
__global__ void ConvolutionKernel1(const unsigned char *original,
                                   unsigned char *result,
                                   const int image_size) {

  // One thing I know for sure is that I will look at the values in the kernel a
  // LOT, from all threads and all blocks. I think it's a safe bet to put this
  // in shared memory.
  __shared__ int kernel[9];
  if (threadIdx.x == 0) {
    // Let's start by hard coding an edge detection kernel.
    kernel[0] = 0;
    kernel[1] = -1;
    kernel[2] = 0;
    kernel[3] = -1;
    kernel[4] = 4;
    kernel[5] = -1;
    kernel[6] = 0;
    kernel[7] = -1;
    kernel[8] = 0;
  }

  __syncthreads();
  const auto pixelX = blockIdx.x * blockDim.x + threadIdx.x;
  const auto pixelY = blockIdx.y * blockDim.y + threadIdx.y;
  if (pixelX < image_size && pixelY < image_size) {
    const auto bitmapPixelOffset = pixelY * image_size + pixelX;
    int newBlue = 0;
    int newGreen = 0;
    int newRed = 0;
    int newOpacity = 0;
    for (int xOffset = -1; xOffset < 2; ++xOffset) {
      for (int yOffset = -1; yOffset < 2; ++yOffset) {
        const auto isInBounds = GetGlobalBoundCheckingMask(
            image_size, pixelX, pixelY, xOffset, yOffset);
        if (!isInBounds)
          continue;
        const auto targetPixelBitmapOffset = GetGlobalNeighbourBitmapOffset(
            original, image_size, bitmapPixelOffset, xOffset, yOffset);
        // I think I only need to touch the opacity?
        const auto kernelOffset = (xOffset + 1) * 3 + (yOffset + 1);
        const auto kernelWeight = kernel[kernelOffset];
        const auto currentBlue = original[targetPixelBitmapOffset];
        const auto currentGreen = original[targetPixelBitmapOffset + 1];
        const auto currentRed = original[targetPixelBitmapOffset + 2];
        const auto currentOpacity = original[targetPixelBitmapOffset + 3];
        newBlue += kernelWeight * currentBlue;
        newGreen += kernelWeight * currentGreen;
        newRed += kernelWeight * currentRed;
        newOpacity += kernelWeight * currentOpacity;
      }
    }

    result[bitmapPixelOffset * 4] = max(0, min(255, newBlue));
    result[bitmapPixelOffset * 4 + 1] = max(0, min(255, newGreen));
    result[bitmapPixelOffset * 4 + 2] = max(0, min(255, newRed));
    result[bitmapPixelOffset * 4 + 3] = max(0, min(255, newOpacity));
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

  // I have two kernels, I might have more. Maybe instead of synchronizing I
  // should use a graph ?
  JuliaKernel<<<grid_size, block_size>>>(d_bitmap, image_dimension);
  cudaDeviceSynchronize();
  CUDA_CHECK(cudaGetLastError());
  unsigned char *d_convolutedBitmap;
  CUDA_CHECK(cudaMalloc(&d_convolutedBitmap, numberOfBytesForBitmap));
  ConvolutionKernel1<<<grid_size, block_size>>>(
      d_bitmap, d_convolutedBitmap, image_dimension);
  cudaDeviceSynchronize();
  CUDA_CHECK(cudaGetLastError());
  ConvolutionKernel1<<<grid_size, block_size>>>(
      d_convolutedBitmap, d_bitmap, image_dimension);
  cudaDeviceSynchronize();
  CUDA_CHECK(cudaGetLastError());
  auto hostResult = std::vector<unsigned char>(numberOfBytesForBitmap);
  CUDA_CHECK(cudaMemcpy(hostResult.data(),
                        d_bitmap,
                        numberOfBytesForBitmap,
                        cudaMemcpyDeviceToHost));
  CUDA_CHECK(cudaFree(d_convolutedBitmap));
  CUDA_CHECK(cudaGetLastError());
  return hostResult;
}