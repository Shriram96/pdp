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
        // std::sort(Xi.begin(), Xi.end());
        return;
    }

    short int countersize = 2*size-1;
    // std::vector<int> counter(countersize, 0);
    // std::vector<int> globalcounter(countersize, 0);
    unsigned long long int counter[countersize + 1] = {0};
    unsigned long long int globalcounter[countersize + 1] = {0};
    short int keyvalues[countersize + 1] = {0};
    keyvalues[countersize] = SHRT_MIN;

    for (int i = 0; i < Xi.size(); i++)
        counter[Xi[i] + size - 1] = counter[Xi[i] + size - 1] + 1;
    
    MPI_Barrier(comm);
    MPI_Allreduce(&counter, &globalcounter, countersize, MPI_UNSIGNED_LONG_LONG, MPI_SUM, comm);
    MPI_Barrier(comm);
    // MPI_Reduce(&counter, &globalcounter, countersize, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, comm);

    for(int i = 0; i < countersize; i++)
    {
        keyvalues[i] = i-size+1;
    }

    // MPI_Barrier(comm);
    // if (rank == 0)
    // {
    //     std::cout << "Counts:" << std::endl;
    //     for(int i = 0; i < countersize; i++)
    //     {
    //         std::cout << keyvalues[i] << ":\t" << globalcounter[i] << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
    // MPI_Barrier(comm);

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

                        keyvalues[i + 1] = keyvalues[j];
                        keyvalues[j] = SHRT_MIN;
                        break;
                    }
                }
            }
        }
    }

    unsigned long long int totalsize = 0;
    totalsize += globalcounter[rank];
    
    if((rank + 1) <= (size - 1)) // Handles odd number of nodes case
    {
        totalsize += globalcounter[rank + 1];
    }

    Xi.resize(totalsize);

    fill_n(Xi.begin(), globalcounter[rank], keyvalues[rank]);

    if((rank + 1) <= (size - 1)) // Handles odd number of nodes case
    {
        fill_n(Xi.begin() + globalcounter[rank], globalcounter[rank + 1], keyvalues[rank + 1]);
    }

    MPI_Barrier(comm);
    // for(int j = 0; j < size; j++)
    // {
        if (rank == 0)
        {
            std::cout << "Size: " << size << std::endl << "Rank: " << rank << std::endl << "Xi Size: " << Xi.size() << std::endl;
            for(int i = 0; i < Xi.size(); i++)
            {
                std::cout << Xi[i] << '\t';
            }
            std::cout << std::endl;
            std::cout << "Counts:" << std::endl;
            for(int i = 0; i < countersize; i++)
            {
                std::cout << keyvalues[i] << ":\t" << globalcounter[i] << std::endl;
            }
            std::cout << std::endl;
        }
        // MPI_Barrier(comm);
        // if (rank == (size - 1))
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
    //     MPI_Barrier(comm);
    // }

} // isort

#endif // A1_HPP
