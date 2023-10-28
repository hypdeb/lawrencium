#ifndef _LAWRENCIUM_SRC_CUDA_PING_H_
#define _LAWRENCIUM_SRC_CUDA_PING_H_
namespace lawrencium {
namespace cuda {
__global__ void FclForwardPass(const float *inputs,
                               const int input_dim,
                               const float *biases,
                               const float *weights,
                               const int number_of_neurons,
                               float *output);
}
} // namespace lawrencium

#endif