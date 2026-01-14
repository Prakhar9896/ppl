#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rank, size, number;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Master process (Rank 0): Enter a number to send to all slaves: ");
        fflush(stdout);
        scanf("%d", &number);

        for (int i = 1; i < size; i++) {
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        printf("Master process (Rank 0): Sent number %d to all %d slave processes.\n", number, size - 1);

        printf("\nStudent Name: Prakhar Umrao | Roll No: 230962210\n");


    } else {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        fflush(stdout);
        
        printf("Slave process (Rank %d): Received number %d from Master.\n", rank, number);
    }


    MPI_Finalize();
    return 0;
}