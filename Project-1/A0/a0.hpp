/*  YOUR_FIRST_NAME
 *  YOUR_LAST_NAME
 *  YOUR_UBIT_NAME
 */

#ifndef A0_HPP
#define A0_HPP
#include <omp.h>
#include <vector>

void filter_2d(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
    unsigned int i = 0;
    unsigned int j = 0;
    float sum = 0.0;

    const int SUMSIZE = 3;
    std::vector<float> KRowSum(SUMSIZE, 0.0);

    KRowSum[0] = K[0] + K[1] + K[2];
    KRowSum[1] = K[3] + K[4] + K[5];
    KRowSum[2] = K[6] + K[7] + K[8];
    
    std::vector<float> A1(A);

    #pragma omp parallel default(none) shared(A1, n, m, A, KRowSum) private(i, j)
    {
        #pragma omp single
        // #pragma omp for schedule(guided)
        // #pragma omp for collapse(2)
        for(i = 0; i < (n - 2); i++)
        {
            // #pragma omp single
            #pragma omp task
            for(j = 0; j < (m - 2); j++)
            {
                float AColSum0 = A[(i * m) + j + 0] + A[((i + 1) * m) + j + 0] + A[((i + 2) * m) + j + 0];
                float AColSum1 = A[(i * m) + j + 1] + A[((i + 1) * m) + j + 1] + A[((i + 2) * m) + j + 1];
                float AColSum2 = A[(i * m) + j + 2] + A[((i + 1) * m) + j + 2] + A[((i + 2) * m) + j + 2];

                A1[((i + 1) * m) + 1 + j] = (AColSum0 * KRowSum[0]) + (AColSum1 * KRowSum[1]) + (AColSum2 * KRowSum[2]);
            }
        }
    }

    // Check A and A1
    // std::cout << std::endl << std::endl;
    // for(i = 0; i < n; i++)
    // {
    //     for(j = 0; j < m; j++)
    //     {
    //         std::cout << A[(i * m) + j] << "\t\t\t";
    //     }
    //     std::cout << std::endl;
    // }
    
    // std::cout << std::endl << std::endl;
    // for(i = 0; i < n; i++)
    // {
    //     for(j = 0; j < m; j++)
    //     {
    //         std::cout << A1[(i * m) + j] << "\t\t\t";
    //     }
    //     std::cout << std::endl;
    // }

    A = A1;
} // filter_2d

#endif // A0_HPP
