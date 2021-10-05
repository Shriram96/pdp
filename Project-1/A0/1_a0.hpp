/*  YOUR_FIRST_NAME
 *  YOUR_LAST_NAME
 *  YOUR_UBIT_NAME
 */

#ifndef A0_HPP
#define A0_HPP

#include <vector>

void get_sub_matrix(int n, int m, int start_n, int start_m, const std::vector<float>& K, std::vector<float>& A)
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
    std::cout << "Sum: " << columnsum << "At: " << start_n + 1 << "x" << start_m + 1;
}


void filter_2d(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
    std::cout << "No. of rows: " << n << std::endl << "No. of columns: " << m << std::endl;
    int total_matrices = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    // #pragma omp parallel shared(n, m, K, A, std::cout)
    {
        // #pragma omp for
        for(i = 0; i <= n-3; i++)
        {
            // #pragma omp for
            for(j = 0; j <= m-3; j++)
            {
                std::cout << ++total_matrices << ")" << std::endl;
                get_sub_matrix(n, m, i, j, K, A);
                std::cout << std::endl << std::endl << std::endl;
            }
        }
    }
} // filter_2d

#endif // A0_HPP
