/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

__global__ void evaluate(float *x, float *y, unsigned long long int n, float h,float A){
    extern __shared__ float buf[];
    float* Xs = buf;

    int m = blockDim.x;
    int idx = threadIdx.x;
    int bdx = blockIdx.x;
    int i = bdx*m + idx;
    float k = 0.0;

    float xi = x[i];
    __syncthreads();
    for (int l = 0; l < gridDim.x; l++) {
        Xs[idx] = x[l*m + idx];
        __syncthreads();
        for (int j = 0; j < m && (l*m + j<n); j++) {
            float a = (xi - Xs[j])/h;
            k += expf(-powf(a,2)/2);
        }
        // __syncthreads();
    }
    y[i] = A*k;
}

void gaussian_kde(unsigned long long int n, float h, const std::vector<float>& x, std::vector<float>& y) {
   int m = 32;

   float *deviceX, *deviceY;

   unsigned long long int size = n*sizeof(float);
   float A = 1/(n*h*sqrtf(2*M_PI));

   cudaMalloc(&deviceX, size);
   cudaMalloc(&deviceY, size);

   cudaMemcpy(deviceX, x.data(), size, cudaMemcpyHostToDevice);
   evaluate<<<(unsigned long long int)ceil((float)n/(float)m),m,m*sizeof(float)>>>(deviceX, deviceY,n,h,A);
   cudaMemcpy(y.data(), deviceY, size, cudaMemcpyDeviceToHost);

   // cout<<A<<endl;
   cudaFree(deviceX);
   cudaFree(deviceY);
} // gaussian_kde

#endif // A3_HPP
