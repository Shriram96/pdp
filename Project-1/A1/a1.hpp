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

    for (int i = 0; i < Xi.size(); i++)
        counter[Xi[i] + size - 1] = counter[Xi[i] + size - 1] + 1;
    
    MPI_Barrier(comm);
    MPI_Allreduce(&counter, &globalcounter, countersize + 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, comm);
    MPI_Barrier(comm);

    
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


    unsigned long long int totalsize = globalcounter[rank] + globalcounter[rank + 1];

    Xi.resize(totalsize);

    fill_n(Xi.begin(), globalcounter[rank], (2*rank) - size + 1);

    fill_n(Xi.begin() + globalcounter[rank], globalcounter[rank + 1], (2*rank) - size + 2);

    // // Place to debug
    // MPI_Barrier(comm);
    // if (rank == 0)
    // {
    //     std::cout << "Size: " << size << std::endl << "Rank: " << rank << std::endl << "Xi Size: " << Xi.size() << std::endl;
    //     for(int i = 0; i < Xi.size(); i++)
    //     {
    //         std::cout << Xi[i] << '\t';
    //     }
    //     std::cout << std::endl;
    //     std::cout << "Counts:" << std::endl;
    //     for(int i = 0; i < countersize; i++)
    //     {
    //         std::cout << keyvalues[i] << ":\t" << globalcounter[i] << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
    

} // isort

#endif // A1_HPP
