/*  YOUR_FIRST_NAME
 *  YOUR_LAST_NAME
 *  YOUR_UBIT_NAME
 */

#ifndef A0_HPP
#define A0_HPP
#include <omp.h>
#include <vector>

void get_sub_matrix1(int n, int m, int start_n, int start_m, const std::vector<float>& K, std::vector<float>& A)
{
    int columnsum = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    // #pragma omp for
    for(i = start_n; i < start_n + 3; i++)
    {
        int rowsum = 0;
        // #pragma omp for
        for(j = start_m; j < start_m + 3; j++)
        {
            int sum = 0;
            for(k = 0; k < 3; k++)
            {
                // std::cout << ' ' << A.at( (i * n) + j) << '\t';
                // std::cout << ((i * n) + j) << '\t';
                // std::cout << ((i * n) + (k+start_m)) << '*' << ((k * 3) + (j-start_m)) << '+';
                sum += A.at((i * n) + (k+start_m)) * K.at((k * 3) + (j-start_m));
            }
            rowsum += sum;
        }
        columnsum += rowsum;
    }
    std::cout << "3)Sum: " << columnsum << "\t" << "At: " << start_n + 1 << "x" << start_m + 1 << std::endl;
}

int get_sub_matrix(int n, int m, int start_n, int start_m, const std::vector<float>& K, std::vector<float>& A)
{
    int sum = 0;
    // for(unsigned int k = 0; k <= 2; k++)
    // {
    //     sum += (A[((start_n + k) * n) + start_m] * K[0] \
    //                                 + A[((start_n + k) * n) + (start_m + 1)] * K[3] \
    //                                 + A[((start_n + k) * n) + (start_m + 2)] * K[6]);
    //     sum += (A[((start_n + k) * n) + start_m] * K[1] \
    //                                 + A[((start_n + k) * n) + (start_m + 1)] * K[4] \
    //                                 + A[((start_n + k) * n) + (start_m + 2)] * K[7]);
    //     sum += (A[((start_n + k) * n) + start_m] * K[2] \
    //                                 + A[((start_n + k) * n) + (start_m + 1)] * K[5] \
    //                                 + A[((start_n + k) * n) + (start_m + 2)] * K[8]);
    // }
    // std::cout << "1)Sum: " << sum << "\t" << "At: " << start_n + 1 << "x" << start_m + 1 << std::endl;
    sum = 0;
    sum += (A.at((start_n * n) + start_m) * K.at(0) \
        + A.at((start_n * n) + (start_m + 1)) * K.at(3) \
        + A.at((start_n * n) + (start_m + 2)) * K.at(6));
    sum += (A.at((start_n * n) + start_m) * K.at(1) \
        + A.at((start_n * n) + (start_m + 1)) * K.at(4) \
        + A.at((start_n * n) + (start_m + 2)) * K.at(7));
    sum += (A.at((start_n * n) + start_m) * K.at(2) \
        + A.at((start_n * n) + (start_m + 1)) * K.at(5) \
        + A.at((start_n * n) + (start_m + 2)) * K.at(8));

    sum += (A.at(((start_n + 1) * n) + start_m) * K.at(0) \
        + A.at(((start_n + 1) * n) + (start_m + 1)) * K.at(3) \
        + A.at(((start_n + 1) * n) + (start_m + 2)) * K.at(6));
    sum += (A.at(((start_n + 1) * n) + start_m) * K.at(1) \
        + A.at(((start_n + 1) * n) + (start_m + 1)) * K.at(4) \
        + A.at(((start_n + 1) * n) + (start_m + 2)) * K.at(7));
    sum += (A.at(((start_n + 1) * n) + start_m) * K.at(2) \
        + A.at(((start_n + 1) * n) + (start_m + 1)) * K.at(5) \
        + A.at(((start_n + 1) * n) + (start_m + 2)) * K.at(8));

    sum += (A.at(((start_n + 2) * n) + start_m) * K.at(0) \
        + A.at(((start_n + 2) * n) + (start_m + 1)) * K.at(3) \
        + A.at(((start_n + 2) * n) + (start_m + 2)) * K.at(6));
    sum += (A.at(((start_n + 2) * n) + start_m) * K.at(1) \
        + A.at(((start_n + 2) * n) + (start_m + 1)) * K.at(4) \
        + A.at(((start_n + 2) * n) + (start_m + 2)) * K.at(7));
    sum += (A.at(((start_n + 2) * n) + start_m) * K.at(2) \
        + A.at(((start_n + 2) * n) + (start_m + 1)) * K.at(5) \
        + A.at(((start_n + 2) * n) + (start_m + 2)) * K.at(8));

    // std::cout << "2)Sum: " << sum << "\t" << "At: " << start_n + 1 << "x" << start_m + 1 << std::endl;
    return sum;
}


void filter_2d(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
    // std::cout << "No. of rows: " << n << std::endl << "No. of columns: " << m << std::endl;
    // int total_matrices = 0;
    unsigned int i = 0;
    // unsigned long j = 0;
    // unsigned long k = 0;
    // int sum = 0;
    std::vector<float> A1(n * m, 0.0);
    // std::cout << omp_get_max_threads() << std::endl;
    #pragma omp parallel default(none) shared(n,m,K,A,A1) private(i)
    {
        // #pragma omp single
        #pragma omp taskloop
        for(i = 0; i < ( (n * m) - ((2*m) - 2)); i++)
        {
            // #pragma omp task shared(A1) untied
            A1[i + m + 1] += (A[i] * K[0] \
                            + A[i + 1] * K[3] \
                            + A[i + 2] * K[6]);
            A1[i + m + 1] += (A[i] * K[1] \
                            + A[i + 1] * K[4] \
                            + A[i + 2] * K[7]);
            A1[i + m + 1] += (A[i] * K[2] \
                            + A[i + 1] * K[5] \
                            + A[i + 2] * K[8]);

            // #pragma omp task shared(A1) untied
            A1[i + m + 1] += (A[i+m] * K[0] \
                            + A[i + m + 1] * K[3] \
                            + A[i + m + 2] * K[6]);
            A1[i + m + 1] += (A[i+m] * K[1] \
                            + A[i + m + 1] * K[4] \
                            + A[i + m + 2] * K[7]);
            A1[i + m + 1] += (A[i+m] * K[2] \
                            + A[i + m + 1] * K[5] \
                            + A[i + m + 2] * K[8]);

            // #pragma omp task shared(A1) untied
            A1[i + m + 1] += (A[i + (2 * m)] * K[0] \
                            + A[i + (2 * m) + 1] * K[3] \
                            + A[i + (2 * m) + 2] * K[6]);
            A1[i + m + 1] += (A[i + (2 * m)] * K[1] \
                            + A[i + (2 * m) + 1] * K[4] \
                            + A[i + (2 * m) + 2] * K[7]);
            A1[i + m + 1] += (A[i + (2 * m)] * K[2] \
                            + A[i + (2 * m) + 1] * K[5] \
                            + A[i + (2 * m) + 2] * K[8]);
            // A1[((i + 1) * n) + (j + 1)] = sum;
            // std::cout << omp_get_thread_num() << std::endl;
            // #pragma omp critical
            // std::cout << i + 1 << 'x' << j+1 << " Thread:" << omp_get_thread_num() << std::endl;
        }
    }
    A = A1;
} // filter_2d

#endif // A0_HPP
