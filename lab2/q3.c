#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int rank, size, received_val;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int arr[size];
        printf("Master (Rank 0): Enter %d array elements:\n", size);
        fflush(stdout);

        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }

        int buffer_size = (sizeof(int) + MPI_BSEND_OVERHEAD) * (size - 1);
        void *buffer = malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        for (int i = 1; i < size; i++) {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        received_val = arr;

        void *temp_ptr;
        int temp_size;
        MPI_Buffer_detach(&temp_ptr, &temp_size);
        free(temp_ptr);

    } else {
        MPI_Recv(&received_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    if (rank % 2 == 0) {
        printf("Rank %d (Even): Received %d, Square is %d\n", rank, received_val, received_val * received_val);
    } else {
        printf("Rank %d (Odd): Received %d, Cube is %d\n", rank, received_val, received_val * received_val * received_val);
    }

    if (rank == 0) {
        printf("\nStudent Name: Prakhar Umrao | Roll No: 230962210\n");
    }

    MPI_Finalize();
    return 0;
}