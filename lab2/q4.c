#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, val;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        char buf[32];

        fgets(buf, sizeof(buf), stdin);
        val = atoi(buf);

        printf("Enter a number: %d\n", val);

        MPI_Send(&val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&val, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);

        printf("Final value at root (after circulation) = %d\n", val);
        printf("Prakhar Umrao 230962210\n");
    }
    else {
        MPI_Recv(&val, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        val++;

        if (rank == size - 1)
            MPI_Send(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        else
            MPI_Send(&val, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
