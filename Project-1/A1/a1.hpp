/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>
#include <climits>


void isort(std::vector<short int>& Xi, MPI_Comm comm) {

    int size, rank;

    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    if(size == 1)
    {
        return;
    }

    short int countersize = 2*size-1;
    unsigned long long int counter[countersize + 1] = {0};
    unsigned long long int globalcounter[countersize + 1] = {0};
    short int keyvalues[countersize + 1] = {0};
    keyvalues[countersize] = SHRT_MIN;

    unsigned long long int counteri[2] = {0};
    short int keyvaluesi[2] = {0};

    for (int i = 0; i < Xi.size(); i++)
        counter[Xi[i] + size - 1] = counter[Xi[i] + size - 1] + 1;
    
    MPI_Barrier(comm);
    MPI_Reduce(&counter, &globalcounter, countersize + 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, comm);
    MPI_Barrier(comm);

    
    if (rank == 0)
    {
        for(int i = 0; i < countersize; i++)
        {
            keyvalues[i] = i-size+1;
        }

        for(int i = 0; i < countersize-1; i++)
        {
            if(globalcounter[i] != 0)
            {
                continue;
            }
            else
            {
                if(globalcounter[i + 1] == 0)
                {
                    for(int j = i; j < countersize; j++)
                    {
                        if(globalcounter[j] != 0)
                        {
                            globalcounter[i + 1] = globalcounter[j];
                            globalcounter[j] = 0;

                            short int temp = keyvalues[i + 1];
                            keyvalues[i + 1] = keyvalues[j];
                            keyvalues[j] = temp;
                            break;
                        }
                    }
                }
            }
        }
    }

    MPI_Barrier(comm);
    MPI_Scatter(&globalcounter, 2, MPI_UNSIGNED_LONG_LONG, &counteri, 2, MPI_UNSIGNED_LONG_LONG, 0, comm);
    MPI_Scatter(&keyvalues, 2, MPI_SHORT, &keyvaluesi, 2, MPI_SHORT, 0, comm);
    MPI_Barrier(comm);

    unsigned long long int totalsize = counteri[0] + counteri[1];

    Xi.resize(totalsize);

    fill_n(Xi.begin(), counteri[0], keyvaluesi[0]);

    fill_n(Xi.begin() + counteri[0], counteri[1], keyvalues[1]);

} // isort

#endif // A1_HPP
