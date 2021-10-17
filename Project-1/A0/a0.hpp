/*  YOUR_FIRST_NAME
 *  YOUR_LAST_NAME
 *  YOUR_UBIT_NAME
 */

#ifndef A0_HPP
#define A0_HPP
#include <omp.h>
#include <vector>

float get_sub_matrix(int n, int m, int start_n, int start_m, const std::vector<float>& K, std::vector<float>& A)
{
    float sum = 0.0;
    // #pragma omp task shared(sum)
    sum += A[(start_n * m) + start_m] * K[0] \
        + A[(start_n * m) + 1 + start_m] * K[3] \
        + A[(start_n * m) + 2 + start_m] * K[6];
    sum += A[(start_n * m) + start_m] * K[1] \
        + A[(start_n * m) + 1 + start_m] * K[4] \
        + A[(start_n * m) + 2 + start_m] * K[7];
    sum += A[(start_n * m) + start_m] * K[2] \
        + A[(start_n * m) + 1 + start_m] * K[5] \
        + A[(start_n * m) + 2 + start_m] * K[8];
    // #pragma omp task shared(sum)
    sum += A[((start_n + 1) * m) + start_m] * K[0] \
        + A[((start_n + 1) * m) + 1 + start_m] * K[3] \
        + A[((start_n + 1) * m) + 2 + start_m] * K[6];
    sum += A[((start_n + 1) * m) + start_m] * K[1] \
        + A[((start_n + 1) * m) + 1 + start_m] * K[4] \
        + A[((start_n + 1) * m) + 2 + start_m] * K[7];
    sum += A[((start_n + 1) * m) + start_m] * K[2] \
        + A[((start_n + 1) * m) + 1 + start_m] * K[5] \
        + A[((start_n + 1) * m) + 2 + start_m] * K[8];
    // #pragma omp task shared(sum)
    sum += A[((start_n + 2) * m) + start_m] * K[0] \
        + A[((start_n + 2) * m) + 1 + start_m] * K[3] \
        + A[((start_n + 2) * m) + 2 + start_m] * K[6];
    sum += A[((start_n + 2) * m) + start_m] * K[1] \
        + A[((start_n + 2) * m) + 1 + start_m] * K[4] \
        + A[((start_n + 2) * m) + 2 + start_m] * K[7];
    sum += A[((start_n + 2) * m) + start_m] * K[2] \
        + A[((start_n + 2) * m) + 1 + start_m] * K[5] \
        + A[((start_n + 2) * m) + 2 + start_m] * K[8];

    return sum;
}

void filter_2d3(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
    unsigned int i = 0;
    unsigned int j = 0;
    float sum = 0.0;

    const int SUMSIZE = 3;
    std::vector<float> KRowSum(SUMSIZE, 0.0);
    std::vector<float> AColSum(SUMSIZE, 0.0);

    KRowSum[0] = K[0] + K[1] + K[2];
    // std::cout << KRowSum[0] << " = " << K[0] << " + " << K[1] << " + " << K[2] << "\n";
    KRowSum[1] = K[3] + K[4] + K[5];
    // std::cout << KRowSum[1] << " = " << K[3] << " + " << K[4] << " + " << K[5] << "\n";
    KRowSum[2] = K[6] + K[7] + K[8];
    // std::cout << KRowSum[2] << " = " << K[6] << " + " << K[7] << " + " << K[8] << "\n";
    
    std::vector<float> A1(A);

    // #pragma omp parallel for default(none) shared(A1) firstprivate(n, m, A, KRowSum, AColSum) private(i, j)
    // for(i = 0; i < (n - 2); i++)
    // {
    //     for(j = 0; j < (m - 2); j++)
    //     {
            
    //         // std::cout << "RowXColumn: " << i << "X" << j << "\n";
    //         AColSum[0] = A[(i * m) + j + 0] + A[((i + 1) * m) + j + 0] + A[((i + 2) * m) + j + 0];
    //         // std::cout << AColSum[0] << " = " << A[(i * m) + j + 0] << " + " << A[((i + 1) * m) + j + 0] << " + " << A[((i + 2) * m) + j + 0] << "\n";
    //         AColSum[1] = A[(i * m) + j + 1] + A[((i + 1) * m) + j + 1] + A[((i + 2) * m) + j + 1];
    //         // std::cout << AColSum[1] << " = " << A[(i * m) + j + 1] << " + " << A[((i + 1) * m) + j + 1] << " + " << A[((i + 2) * m) + j + 1] << "\n";
    //         AColSum[2] = A[(i * m) + j + 2] + A[((i + 1) * m) + j + 2] + A[((i + 2) * m) + j + 2];
    //         // std::cout << AColSum[2] << " = " << A[(i * m) + j + 2] << " + " << A[((i + 1) * m) + j + 2] << " + " << A[((i + 2) * m) + j + 2] << "\n";

    //         // std::cout << "AColSum 0: " << AColSum[0] << "\t" << "KRowSum 0: " << KRowSum[0]<< "\n";
    //         // std::cout << "AColSum 1: " << AColSum[1] << "\t" << "KRowSum 1: " << KRowSum[1]<< "\n";
    //         // std::cout << "AColSum 2: " << AColSum[2] << "\t" << "KRowSum 2: " << KRowSum[2]<< "\n";

    //         A1[((i + 1) * m) + 1 + j] = (AColSum[0] * KRowSum[0]) + (AColSum[1] * KRowSum[1]) + (AColSum[2] * KRowSum[2]);

    //         // std::cout << "TotalSum: " << (AColSum[0] * KRowSum[0]) + (AColSum[1] * KRowSum[1]) + (AColSum[2] * KRowSum[2]) << "\n";
    //     }
    // }


    #pragma omp parallel default(none) shared(A1) firstprivate(n, m, A, KRowSum, AColSum) private(i)
    {
        #pragma omp for
        // #pragma omp single
        // #pragma omp task shared(A1) firstprivate(n, m, A, KRowSum, AColSum) private(i)
        for(int i = 0; i < (m * (n - 2)); i++)
        {
            if((i % m) < 2)
            {
                // std::cout << i << std::endl;
                AColSum[0] = A[i] + A[i + m] + A[i + (2 * m)];
                AColSum[1] = A[i + 1] + A[i + m + 1] + A[i + (2 * m) + 1];
                AColSum[2] = A[i + 2] + A[i + m + 2] + A[i + (2 * m) + 2];

                A[i + m + 1] = (AColSum[0] * KRowSum[0]) + (AColSum[1] * KRowSum[1]) + (AColSum[2] * KRowSum[2]);
            }
        }
    } // OMP Parallel End

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
}

void filter_2d2(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
    unsigned int i = 0;
    unsigned int j = 0;
    float sum = 0.0;
    std::vector<float> A1(A);
    
    // #pragma omp parallel for default(none) shared(n,m,K,A,A1) private(i, j, sum)
    // #pragma omp parallel default(none) shared(n,m,K,A,A1) private(i, j)
    // {
        // #pragma single
        // #pragma omp taskloop untied
        for(i = 0; i < (n - 2); i++)
        {
            // #pragma single
            // #pragma omp taskloop
            for(j = 0; j < (m - 2); j++)
            {
                // #pragma omp critical
                    // std::cout << A[(i * m) + j] << "\t\t";
                    // std::cout << ((i * m) + j) << "\tAt: " << i << " X " << j << "\n";
                    // std::cout << (i * m) + j << "\t" << (i * m) + 1 + j << "\t" << (i * m) + 2 + j << "\n";
                    // std::cout << ((i + 1) * m) + j << "\t" << ((i + 1) * m) + 1 + j << "\t" << ((i + 1) * m) + 2 + j << "\n";
                    // std::cout << ((i + 2) * m) + j << "\t" << ((i + 2) * m) + 1 + j << "\t" << ((i + 2) * m) + 2 + j << "\n";
                // #pragma omp atomic
                // float sum = get_sub_matrix(n, m, i, j, K, A);
                // A1[((i + 1) * m) + 1 + j] = get_sub_matrix(n, m, i, j, K, A);
                // #pragma omp critical
                // A1[((i + 1) * m) + 1 + j] = sum;

                // #pragma omp task shared(sum)
                sum += A[(i * m) + j] * K[0] \
                    + A[(i * m) + 1 + j] * K[3] \
                    + A[(i * m) + 2 + j] * K[6];
                sum += A[(i * m) + j] * K[1] \
                    + A[(i * m) + 1 + j] * K[4] \
                    + A[(i * m) + 2 + j] * K[7];
                sum += A[(i * m) + j] * K[2] \
                    + A[(i * m) + 1 + j] * K[5] \
                    + A[(i * m) + 2 + j] * K[8];
                // #pragma omp task shared(sum)
                sum += A[((i + 1) * m) + j] * K[0] \
                    + A[((i + 1) * m) + 1 + j] * K[3] \
                    + A[((i + 1) * m) + 2 + j] * K[6];
                sum += A[((i + 1) * m) + j] * K[1] \
                    + A[((i + 1) * m) + 1 + j] * K[4] \
                    + A[((i + 1) * m) + 2 + j] * K[7];
                sum += A[((i + 1) * m) + j] * K[2] \
                    + A[((i + 1) * m) + 1 + j] * K[5] \
                    + A[((i + 1) * m) + 2 + j] * K[8];
                // #pragma omp task shared(sum)
                sum += A[((i + 2) * m) + j] * K[0] \
                    + A[((i + 2) * m) + 1 + j] * K[3] \
                    + A[((i + 2) * m) + 2 + j] * K[6];
                sum += A[((i + 2) * m) + j] * K[1] \
                    + A[((i + 2) * m) + 1 + j] * K[4] \
                    + A[((i + 2) * m) + 2 + j] * K[7];
                sum += A[((i + 2) * m) + j] * K[2] \
                    + A[((i + 2) * m) + 1 + j] * K[5] \
                    + A[((i + 2) * m) + 2 + j] * K[8];

                A1[((i + 1) * m) + 1 + j] = sum;

                // if(((i * m) + j) >= (n*m)) std::cout << '(' << i << " X " << m << ')' << " + " << j << " = " << (i * n) + j << std::endl;
            }
        }
    // } // OMP Parallel end
    // A = A1;
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
}


void filter_2d(unsigned long int n, unsigned long int m, const std::vector<float>& K, std::vector<float>& A) {
    // std::cout << "No. of rows: " << n << std::endl << "No. of columns: " << m << std::endl;
    // int total_matrices = 0;
    unsigned int i = 0;
    // std::cout << sizeof(float) << std::endl;
    // unsigned long j = 0;
    // unsigned long k = 0;
    // int sum = 0;
    std::vector<float> A1(A);
    // std::cout << omp_get_max_threads() << std::endl;
    #pragma omp parallel for default(none) shared(n,m,K,A,A1) private(i)
    // {
        // #pragma omp single
        // #pragma omp task
        // #pragma omp taskloop default(none) shared(n,m,K,A,A1) private(i)
        // #pragma omp for
        for(i = 0; ((i < ((m * (n - 2))))); i++)
        {
            float sum = 0.0;
            if(( i % m != 1) && ( i % m != 2) )
            {
                // #pragma omp task shared(A1) untied
                sum += (A[i] * K[0] \
                                + A[i + 1] * K[3] \
                                + A[i + 2] * K[6]);
                sum += (A[i] * K[1] \
                                + A[i + 1] * K[4] \
                                + A[i + 2] * K[7]);
                sum += (A[i] * K[2] \
                                + A[i + 1] * K[5] \
                                + A[i + 2] * K[8]);

                // #pragma omp task shared(A1) untied
                sum += (A[i + m] * K[0] \
                                + A[i + m + 1] * K[3] \
                                + A[i + m + 2] * K[6]);
                sum += (A[i + m] * K[1] \
                                + A[i + m + 1] * K[4] \
                                + A[i + m + 2] * K[7]);
                sum += (A[i + m] * K[2] \
                                + A[i + m + 1] * K[5] \
                                + A[i + m + 2] * K[8]);

                // #pragma omp task shared(A1) untied
                sum += (A[i + (2 * m)] * K[0] \
                                + A[i + (2 * m) + 1] * K[3] \
                                + A[i + (2 * m) + 2] * K[6]);
                sum += (A[i + (2 * m)] * K[1] \
                                + A[i + (2 * m) + 1] * K[4] \
                                + A[i + (2 * m) + 2] * K[7]);
                sum += (A[i + (2 * m)] * K[2] \
                                + A[i + (2 * m) + 1] * K[5] \
                                + A[i + (2 * m) + 2] * K[8]);
            }
            // A1[((i + 1) * n) + (j + 1)] = sum;
            // A1[i + m + 1] = sum;
            // std::cout << omp_get_thread_num() << std::endl;
            // #pragma omp critical
            // std::cout << i + 1 << 'x' << j+1 << " Thread:" << omp_get_thread_num() << std::endl;
        }
    // }
    // A = A1;
} // filter_2d

#endif // A0_HPP
