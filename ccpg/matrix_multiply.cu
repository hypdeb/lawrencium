#include "matrix_multiply.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

/**
 * \brief The thread block size.
 */
constexpr int block_size = 1;

__global__ void MatMulKernel(lawrencium::ccpg::library::matrix left_hand,
                             lawrencium::ccpg::library::matrix right_hand,
                             lawrencium::ccpg::library::matrix result) {
  float result_value = 0;
  const auto row = blockIdx.y * blockDim.y + threadIdx.y;
  const auto col = blockIdx.x * blockDim.x + threadIdx.x;
  for (auto e = 0; e < left_hand.width; ++e) {
    result_value += left_hand.elements[row * left_hand.width + e] *
                    right_hand.elements[e * right_hand.width + col];
  }

  result.elements[row * result.width + col] = result_value;
}

void lawrencium::ccpg::library::MatMul(const lawrencium::ccpg::library::matrix lh, const lawrencium::ccpg::library::matrix rh, lawrencium::ccpg::library::matrix result) {
  // TODO: extract this creation of device matrix.
  // TODO: understand why it's okay for the height and width to be host-side.
  lawrencium::ccpg::library::matrix device_lh = {
      .width = lh.width,
      .height = lh.height,
  };
  const auto lh_elements_memory_size = static_cast<size_t>(lh.width) *
                                       static_cast<size_t>(lh.height) *
                                       sizeof(float);
  cudaMalloc(&device_lh.elements, lh_elements_memory_size);
  cudaMemcpy(device_lh.elements, lh.elements, lh_elements_memory_size,
             cudaMemcpyHostToDevice);

  lawrencium::ccpg::library::matrix device_rh = {
      .width = rh.width,
      .height = rh.height,
  };
  const auto rh_elements_memory_size = static_cast<size_t>(rh.width) *
                                       static_cast<size_t>(rh.height) *
                                       sizeof(float);
  cudaMalloc(&device_rh.elements, rh_elements_memory_size);
  cudaMemcpy(device_rh.elements, rh.elements, rh_elements_memory_size,
             cudaMemcpyHostToDevice);

  lawrencium::ccpg::library::matrix device_result = {
      .width = result.width,
      .height = result.height,
  };
  const auto result_elements_memory_size = static_cast<size_t>(result.width) *
                                           static_cast<size_t>(result.height) *
                                           sizeof(float);
  cudaMalloc(&device_result.elements, result_elements_memory_size);

  dim3 dimBlock(block_size, block_size);
  dim3 dimGrid(rh.width / dimBlock.x, lh.height / dimBlock.y);
  MatMulKernel<<<dimGrid, dimBlock>>>(device_lh, device_rh, device_result);
  cudaDeviceSynchronize();
  cudaMemcpy(result.elements, device_result.elements,
             result_elements_memory_size, cudaMemcpyDeviceToHost);

  cudaFree(device_lh.elements);
  cudaFree(device_rh.elements);
  cudaFree(device_result.elements);
  cudaDeviceSynchronize();
}
