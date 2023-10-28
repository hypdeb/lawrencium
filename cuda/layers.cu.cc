#ifndef _LAWRENCIUM_CUDA_NEURALNETS_H_
#define _LAWRENCIUM_CUDA_NEURALNETS_H_

namespace cuda = lawrencium::cuda;

__global__ void cuda::fcl_forward_pass(const float *inputs,
                                       const int input_dim,
                                       const float *biases,
                                       const float *weights,
                                       const int number_of_neurons,
                                       float *output) {
  const auto index = blockIdx.x * blockDim.x + threadIdx.x;
  if (index < number_of_neurons) {
    float sum = 0;
    for (auto i = 0; i < input_dim; ++i) {
      sum += inputs[i] * weights[i];
    }
    output[index] = biases[index] + sum;
  }
}
#endif