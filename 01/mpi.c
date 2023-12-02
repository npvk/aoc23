#include <stdio.h>
#include <mpi.h>

int main(int c, char **v)
{
    // Begin le MPI
    int node;
    int i = 0;
    int max = 0;
    MPI_Init(&c, &v);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);

    if (node == 0)
        printf("I am big rank 0\n");
    else
        printf("I am rank: %d\n", node);
    MPI_Finalize();
}
