#include "matrixes.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

namespace library = lawrencium::ccpg::library;

constexpr int block_size = 16;

__global__ void MatMulKernel(library::matrix left_hand,
                             library::matrix right_hand,
                             library::matrix result) {
  float result_value = 0;
  const auto row = blockIdx.y * blockDim.y + threadIdx.y;
  const auto col = blockIdx.x * blockDim.x + threadIdx.x;
  for (auto e = 0; e < left_hand.width; ++e) {
    result_value += left_hand.elements[row * left_hand.width + e]
                    * right_hand.elements[e * right_hand.width + col];
  }

  result.elements[row * result.width + col] = result_value;
}

__device__ float
GetElement(const library::strided_matrix matrix, int row, int col) {
  return matrix.elements[row * matrix.stride + col];
}

__device__ void
SetElement(library::strided_matrix matrix, int row, int col, float value) {
  matrix.elements[row * matrix.stride + col] = value;
}

__device__ library::strided_matrix
GetSubMatrix(library::matrix matrix, int stride, int row, int col) {
  return library::strided_matrix{
      .width = block_size,
      .height = block_size,
      .stride = stride,
      .elements
      = &matrix.elements[stride * block_size * row + block_size * col],
  };
}

__global__ void SharedMemoryMatMulKernel(const library::matrix left_hand,
                                         const library::matrix right_hand,
                                         library::matrix result,
                                         int stride) {
  const auto blockRow = blockIdx.y;
  const auto blockCol = blockIdx.x;

  library::strided_matrix result_sub_matrix
      = GetSubMatrix(result, blockRow, blockCol, stride);

  float result_value = 0;

  const auto row = threadIdx.y;
  const auto col = threadIdx.x;

  // Iterate over the tiles.
  for (int m = 0; m < (left_hand.width / block_size); ++m) {
    const auto left_hand_sub_matrix
        = GetSubMatrix(left_hand, blockRow, m, stride);
    const auto right_hand_sub_matrix
        = GetSubMatrix(right_hand, m, blockCol, stride);
    __shared__ float lhs[block_size][block_size];
    __shared__ float rhs[block_size][block_size];
    lhs[row][col] = GetElement(left_hand_sub_matrix, row, col);
    rhs[row][col] = GetElement(right_hand_sub_matrix, row, col);
    __syncthreads();
    for (int e = 0; e < block_size; ++e) {
      result_value += lhs[row][e] * rhs[e][col];
    }
    __syncthreads();
  }

  SetElement(result_sub_matrix, row, col, result_value);
}

void library::SharedMemoryMatMul(const library::matrix lh,
                                 const library::matrix rh,
                                 library::matrix result) {
  library::matrix device_lh = {
      .width = lh.width,
      .height = lh.height,
  };
  const auto lh_elements_memory_size = static_cast<size_t>(lh.width)
                                       * static_cast<size_t>(lh.height)
                                       * sizeof(float);
  cudaMalloc(&device_lh.elements, lh_elements_memory_size);
  cudaMemcpy(device_lh.elements,
             lh.elements,
             lh_elements_memory_size,
             cudaMemcpyHostToDevice);

  library::matrix device_rh = {
      .width = rh.width,
      .height = rh.height,
  };
  const auto rh_elements_memory_size = static_cast<size_t>(rh.width)
                                       * static_cast<size_t>(rh.height)
                                       * sizeof(float);
  cudaMalloc(&device_rh.elements, rh_elements_memory_size);
  cudaMemcpy(device_rh.elements,
             rh.elements,
             rh_elements_memory_size,
             cudaMemcpyHostToDevice);

  library::matrix device_result = {
      .width = result.width,
      .height = result.height,
  };
  const auto result_elements_memory_size = static_cast<size_t>(result.width)
                                           * static_cast<size_t>(result.height)
                                           * sizeof(float);
  cudaMalloc(&device_result.elements, result_elements_memory_size);

  dim3 dimBlock(block_size, block_size);
  dim3 dimGrid(rh.width / dimBlock.x, lh.height / dimBlock.y);
  SharedMemoryMatMulKernel<<<dimGrid, dimBlock>>>(
      device_lh, device_rh, device_result, block_size);
  cudaDeviceSynchronize();
  cudaMemcpy(result.elements,
             device_result.elements,
             result_elements_memory_size,
             cudaMemcpyDeviceToHost);

  cudaFree(device_lh.elements);
  cudaFree(device_rh.elements);
  cudaFree(device_result.elements);
  cudaDeviceSynchronize();
}

void library::MatMul(const library::matrix lh,
                     const library::matrix rh,
                     library::matrix result) {
  // TODO: extract this creation of device matrix.
  // TODO: understand why it's okay for the height and width to be host-side.
  library::matrix device_lh = {
      .width = lh.width,
      .height = lh.height,
  };
  const auto lh_elements_memory_size = static_cast<size_t>(lh.width)
                                       * static_cast<size_t>(lh.height)
                                       * sizeof(float);
  cudaMalloc(&device_lh.elements, lh_elements_memory_size);
  cudaMemcpy(device_lh.elements,
             lh.elements,
             lh_elements_memory_size,
             cudaMemcpyHostToDevice);

  library::matrix device_rh = {
      .width = rh.width,
      .height = rh.height,
  };
  const auto rh_elements_memory_size = static_cast<size_t>(rh.width)
                                       * static_cast<size_t>(rh.height)
                                       * sizeof(float);
  cudaMalloc(&device_rh.elements, rh_elements_memory_size);
  cudaMemcpy(device_rh.elements,
             rh.elements,
             rh_elements_memory_size,
             cudaMemcpyHostToDevice);

  library::matrix device_result = {
      .width = result.width,
      .height = result.height,
  };
  const auto result_elements_memory_size = static_cast<size_t>(result.width)
                                           * static_cast<size_t>(result.height)
                                           * sizeof(float);
  cudaMalloc(&device_result.elements, result_elements_memory_size);

  dim3 dimBlock(block_size, block_size);
  dim3 dimGrid(rh.width / dimBlock.x, lh.height / dimBlock.y);
  MatMulKernel<<<dimGrid, dimBlock>>>(device_lh, device_rh, device_result);
  cudaDeviceSynchronize();
  cudaMemcpy(result.elements,
             device_result.elements,
             result_elements_memory_size,
             cudaMemcpyDeviceToHost);

  cudaFree(device_lh.elements);
  cudaFree(device_rh.elements);
  cudaFree(device_result.elements);
  cudaDeviceSynchronize();
}
