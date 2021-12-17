/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>


__global__ void calculate(float *x, float *y, unsigned long long int n, float h,float static_value){
    extern __shared__ float buf[];
    float* Xs = buf;
	float K = 0.0;

    int block_dim = blockDim.x; // Only takes 32
    int t_idx = threadIdx.x; // Takes between 0..32
    int b_idx = blockIdx.x; // Takes between 0..n/m

    int i = b_idx * block_dim + t_idx;

    float xi = x[i];
    for (int j = 0; j < gridDim.x; j++) // Looping through each block in the grid. // 0..n/m
	{
        Xs[t_idx] = x[j * block_dim + t_idx];
        __syncthreads();

        for (int l = 0; (l < block_dim) && ((j * block_dim + l) < n); l++) // Looping through each thread in the block. // 0..32
		{
            float a = (xi - Xs[l]) / h;
            K += expf(-powf(a, 2) / 2);
        }
        __syncthreads();
    }
    y[i] = static_value*K;
}

void gaussian_kde(unsigned long long int n, float h, const std::vector<float>& x, std::vector<float>& y) {

	float static_value = 1/(n * h * sqrtf(2 * M_PI));

   	int block_threads = 32;
	int buf_size = block_threads * sizeof(float);
	unsigned long long int block_nums = n / block_threads;
	if(n % block_threads != 0) 
		block_nums += 1;

    float *d_x, *d_y;
	unsigned long long int size = n * sizeof(float);
    cudaMalloc(&d_x, size);
    cudaMalloc(&d_y, size);

	cudaMemcpy(d_x, x.data(), size, cudaMemcpyHostToDevice);
	calculate<<<block_nums, block_threads, buf_size>>>(d_x, d_y, n, h, static_value);
	cudaMemcpy(y.data(), d_y, size, cudaMemcpyDeviceToHost);

	cudaFree(d_x);
	cudaFree(d_y);
} // gaussian_kde

#endif // A3_HPP
