/*  YOUR_FIRST_NAME
 *  YOUR_LAST_NAME
 *  YOUR_UBIT_NAME
 */

#ifndef A0_HPP
#define A0_HPP

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
    std::cout << "Sum: " << columnsum << "\t" << "At: " << start_n + 1 << "x" << start_m + 1;
}

int get_sub_matrix(int n, int m, int start_n, int start_m, const std::vector<float>& K, std::vector<float>& A)
{
    int sum = 0;
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

    // std::cout << "Sum: " << sum << "\t" << "At: " << start_n + 1 << "x" << start_m + 1;
    return sum;
}


void filter_2d(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
    // std::cout << "No. of rows: " << n << std::endl << "No. of columns: " << m << std::endl;
    // int total_matrices = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    std::vector<float> A1(n * m);
    #pragma omp parallel for shared(K,A,A1) private(i,j) collapse(2)
    // {
        // #pragma omp for schedule(static)
        for(i = 0; i <= n-3; i++)
        {
            // #pragma omp task shared(A, A1, K)
            for(j = 0; j <= m-3; j++)
            {
                // std::cout << ++total_matrices << ")" << std::endl;
                A1[(i * n) + j] = get_sub_matrix(n, m, i, j, K, A);
                // get_sub_matrix1(n, m, i, j, K, A);
                // std::cout << std::endl << std::endl << std::endl;
            }
        }
    // }
    A = A1;
} // filter_2d

#endif // A0_HPP
