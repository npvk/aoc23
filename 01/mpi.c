#include <stdio.h>
#include <mpi.h>

int main(int c, char **v)
{
    // Begin le MPI
    int rank;
    int res;
    int size = 0;
    int count = 0;

    MPI_Init(&c, &v);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    count++;
    MPI_Reduce(&count, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
      printf("Sum: %d\n", res);
    }
    MPI_Finalize();
    return 0;
}
