#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank;
    int matrix[3][3], key;
    int local_count = 0, total_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter 3x3 matrix:\n");
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                scanf("%d", &matrix[i][j]);

        printf("Enter element to search: ");
        scanf("%d", &key);
    }

    MPI_Bcast(matrix, 9, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int j = 0; j < 3; j++) {
        if (matrix[rank][j] == key)
            local_count++;
    }

    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total occurrences of %d = %d\n", key, total_count);

        printf("Prakhar Umrao 230962210\n");

    }

    MPI_Finalize();
    return 0;
}
