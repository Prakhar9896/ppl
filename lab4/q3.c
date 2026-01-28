#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank;
    int matrix[4][4];
    int local_row[4];
    int output[4][4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter 4x4 matrix:\n");
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &matrix[i][j]);
    }

    MPI_Bcast(matrix, 16, MPI_INT, 0, MPI_COMM_WORLD);

    for (int j = 0; j < 4; j++) {
        local_row[j] = 0;
        for (int i = 0; i <= rank; i++) {
            local_row[j] += matrix[i][j];
        }
    }

    MPI_Gather(local_row, 4, MPI_INT,
               output, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Output matrix:\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                printf("%d ", output[i][j]);
            printf("\n");
        }
        printf("Prakhar Umrao 230962210\n");
    }

    MPI_Finalize();
    return 0;
}
