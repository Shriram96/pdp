/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

void find_y(const std::vector<float>& x, std::vector<float>& y, unsigned long long int n, float h,float A){

    unsigned long long int i = 0;
    unsigned long long int j = 0;
    float sum = 0.0;

    #pragma omp parallel default(none) shared(x, y, n, h, A) private(i, j, sum)
    {
        #pragma omp for
        for(i = 0; i < n; i++)
        {
            // #pragma omp single
            #pragma omp taskloop untied
            for(j = 0; j < n; j++)
            {
                float a = (x[i] - x[j])/h;
                sum += expf(-powf(a,2)/2);
            }
            y[i] = A * sum;
        }
    }
}

void gaussian_kde(unsigned long long int n, float h, const std::vector<float>& x, std::vector<float>& y) {

   float A = 1/(n*h*sqrtf(2*M_PI));
   find_y(x, y, n, h, A);

//    for(unsigned long long int i = 0; i < y.size(); i++)
//    {
//        cout<<y[i]<<"\t";
//    }
//    cout<<endl<<"A: "<<A<<endl;
} // gaussian_kde

#endif // A3_HPP