#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr = NULL;
    int recv_val;
    MPI_Status status;

    if (rank == 0) {
        arr = (int *)malloc(size * sizeof(int));
        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }

        int buf_size = size * sizeof(int) + MPI_BSEND_OVERHEAD;
        void *buffer = malloc(buf_size);
        MPI_Buffer_attach(buffer, buf_size);

        for (int i = 1; i < size; i++) {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        recv_val = arr[0];
        int result;
        result = (rank % 2 == 0) ? recv_val * recv_val : recv_val * recv_val * recv_val;
        printf("Process %d result = %d\n", rank, result);

        MPI_Buffer_detach(&buffer, &buf_size);

        printf("Prakhar Umrao 230962210\n");
    } 
    else {
        MPI_Recv(&recv_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        int result = (rank % 2 == 0) ? recv_val * recv_val : recv_val * recv_val * recv_val;
        printf("Process %d received %d, result = %d\n", rank, recv_val, result);
    }

    MPI_Finalize();
    return 0;
}
