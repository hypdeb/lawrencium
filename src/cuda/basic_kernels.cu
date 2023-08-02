#include "basic_kernels.cuh"

__global__ void lawrencium::cuda::add_kernel(float *A, float *B, float *C, int N) {
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < N)
    C[i] = A[i] + B[i];
}

__global__ void lawrencium::cuda::sum_rows_of_square_matrix(const float *matrix, float* result, const int sideLength) {
  int rowIdx = threadIdx.x + blockIdx.x * blockDim.x;
  if(rowIdx < sideLength) {
    float sum = 0.0;
    for(int colIdx = 0; colIdx < sideLength; colIdx++) {
      sum += matrix[rowIdx * sideLength + colIdx];
    }
    result[rowIdx] = sum;
  }
}

__global__ void lawrencium::cuda::transpose_square_matrix(const float* inMatrix, float* outMatrix, const int sideLength) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  int idy = blockIdx.y * blockDim.y + threadIdx.y;
  if (idx < sideLength && idy < sideLength) {
    int pos = idy * sideLength + idx;
    int trans_pos = idx * sideLength + idy;
    outMatrix[trans_pos] = inMatrix[pos];
  }
}

__global__ void lawrencium::cuda::all_equal_to(const float* inVector, const int length, const float target, const float tolerance, bool *result) {
  *result = true;
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  const auto upperBound = target + tolerance;
  const auto lowerBound = target - tolerance;
  if (i < length) {

    // I assume that since the operation is idempotent, this is not a problem?
    if (!(inVector[i] <= upperBound && inVector[i] >= lowerBound)) {
      *result = false;
    }
  }
}