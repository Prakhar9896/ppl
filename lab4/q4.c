#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char word[100];
    char local[100];
    char result[500];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter word: ");
        scanf("%s", word);
    }

    MPI_Bcast(word, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    int idx = 0;
    for (int i = 0; i <= rank; i++) {
        local[idx++] = word[rank];
    }
    local[idx] = '\0';

    MPI_Gather(local, 100, MPI_CHAR,
               result, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Output: ");
        for (int i = 0; i < size; i++)
            printf("%s", &result[i * 100]);
        printf("\n");

        printf("Prakhar Umrao 230962210\n");
    }

    MPI_Finalize();
    return 0;
}
