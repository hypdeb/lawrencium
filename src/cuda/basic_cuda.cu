#include "helpers.h"
#include "basic_cuda.cuh"
#include "basic_kernels.cuh"

void lawrencium::cuda::cuda_add(float *A, float *B, float *C, int N) {
  const auto size = N * sizeof(float);

  float *d_A;
  CUDA_CHECK(cudaMalloc(&d_A, size));
  float *d_B;
  CUDA_CHECK(cudaMalloc(&d_B, size));
  float *d_C;
  CUDA_CHECK(cudaMalloc(&d_C, size));
  CUDA_CHECK(cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice));
  CUDA_CHECK(cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice));
  int threadsPerBlock = 256;
  int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
  lawrencium::cuda::add_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

  CUDA_CHECK(cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost));

  CUDA_CHECK(cudaFree(d_A));
  CUDA_CHECK(cudaFree(d_B));
  CUDA_CHECK(cudaFree(d_C));

  CUDA_CHECK(cudaGetLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
};

bool lawrencium::cuda::is_doubly_stochastic(const float *matrix, const int sideLength) {
  const auto numElements = sideLength * sideLength;

  // Space required in bytes for a square matrix of size sideLength * sideLength
  const auto matrixSizeInBytes = numElements * sizeof(float);

  // Allocate space for the original matrix.
  float *dMatrix;
  CUDA_CHECK(cudaMalloc(&dMatrix, matrixSizeInBytes));

  // Space required in bytes for a square matrix of size sideLength * sideLength
  const auto sumsSizeInBytes = sideLength * sizeof(float);

  // Allocate space for vector of sums of rows / columns.
  float *dSums;
  CUDA_CHECK(cudaMalloc(&dSums, sumsSizeInBytes));

  // We start by summing the rows.
  const int threadsPerBlock = 256;
  const int blocksPerGrid = (numElements + threadsPerBlock - 1) / threadsPerBlock;
  lawrencium::cuda::sum_rows_of_square_matrix<<<blocksPerGrid, threadsPerBlock>>>(dMatrix, dSums, sideLength);
  CUDA_CHECK(cudaPeekAtLastError());
  CUDA_CHECK(cudaDeviceSynchronize());

  // Then we check that all the elements are 1. We need some boolean indicator on GPU, which we then copy back.
  bool *dStochasticity;
  const auto sizeOfBool = sizeof(bool);
  CUDA_CHECK(cudaMalloc(&dStochasticity, sizeOfBool));

  bool rowStochasticity;
  lawrencium::cuda::all_equal_to<<<blocksPerGrid, threadsPerBlock>>>(dSums, sideLength, 1.0f, 1e-6f, dStochasticity);
  CUDA_CHECK(cudaPeekAtLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
  CUDA_CHECK(cudaMemcpy(&rowStochasticity, dStochasticity, sizeOfBool, cudaMemcpyDeviceToHost));

  // If it's already not stochastic here, early return. But we need to clean up... #localfunctions :)
  if (!rowStochasticity) {
    CUDA_CHECK(cudaFree(dMatrix));
    CUDA_CHECK(cudaFree(dSums));
    CUDA_CHECK(cudaFree(dStochasticity));
    return false;
  }

  // Allocate space for the transposed matrix, which we need because it is allegedly faster to transpose and sum the rows, than to sum the columns.
  float *dTransposedMatrix;
  CUDA_CHECK(cudaMalloc(&dTransposedMatrix, matrixSizeInBytes));

  // We do the transposition.
  lawrencium::cuda::transpose_square_matrix<<<blocksPerGrid, threadsPerBlock>>>(dMatrix, dTransposedMatrix, sideLength);
  CUDA_CHECK(cudaPeekAtLastError());
  CUDA_CHECK(cudaDeviceSynchronize());

  // Now we can already get rid of the original.
  CUDA_CHECK(cudaFree(dMatrix));

  // Then we do the summing, checking equality, and copying back.
  lawrencium::cuda::sum_rows_of_square_matrix<<<blocksPerGrid, threadsPerBlock>>>(dTransposedMatrix, dSums, sideLength);
  CUDA_CHECK(cudaPeekAtLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
  lawrencium::cuda::all_equal_to<<<blocksPerGrid, threadsPerBlock>>>(dSums, sideLength, 1.0f, 1e-6f, dStochasticity);
  CUDA_CHECK(cudaPeekAtLastError());
  CUDA_CHECK(cudaDeviceSynchronize());
  CUDA_CHECK(cudaMemcpy(&rowStochasticity, dStochasticity, sizeOfBool, cudaMemcpyDeviceToHost));

  // Now we do not have anything more to do on GPU, so we clean up.
  CUDA_CHECK(cudaFree(dMatrix));
  CUDA_CHECK(cudaFree(dTransposedMatrix));
  CUDA_CHECK(cudaFree(dSums));
  CUDA_CHECK(cudaFree(dStochasticity));

  // And finally we return the stochasticity of the rows of the transposed matrix / columns of the original matrix.
  return rowStochasticity;
}