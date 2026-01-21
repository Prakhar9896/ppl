#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int M;
    if (rank == 0) {
        printf("Enter M (elements per process): ");
        scanf("%d", &M);
    }
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int arr[M * size];
    int recv[M];

    if (rank == 0) {
        printf("Enter %d integers:\n", M * size);
        for (int i = 0; i < M * size; i++)
            scanf("%d", &arr[i]);
    }

    MPI_Scatter(arr, M, MPI_INT, recv, M, MPI_INT, 0, MPI_COMM_WORLD);

    float local_avg = 0;
    for (int i = 0; i < M; i++) local_avg += recv[i];
    local_avg /= M;

    float total_avg;
    MPI_Reduce(&local_avg, &total_avg, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        total_avg /= size;
        printf("Overall Average = %.2f\n", total_avg);
        printf("\nPrakhar Umrao 230962210\n");
    }

    MPI_Finalize();
    return 0;
}
