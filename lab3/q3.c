#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isVowel(char c) {
    c = tolower(c);
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u');
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char str[200];
    int len;

    if (rank == 0) {
        printf("Enter a string: ");
        fflush(stdout);
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0'; 
        len = strlen(str);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int counts[size], displs[size];

    int base = len / size;
    int extra = len % size;

    for (int i = 0; i < size; i++) {
        counts[i] = base + (i < extra ? 1 : 0);
    }

    displs[0] = 0;
    for (int i = 1; i < size; i++)
        displs[i] = displs[i - 1] + counts[i - 1];

    char local[counts[rank]];

    MPI_Scatterv(str, counts, displs, MPI_CHAR,
                 local, counts[rank], MPI_CHAR,
                 0, MPI_COMM_WORLD);

    int local_count = 0;
    for (int i = 0; i < counts[rank]; i++)
        if (!isVowel(local[i]))
            local_count++;

    int total_count = 0;
    MPI_Reduce(&local_count, &total_count, 1,
               MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total non-vowels: %d\n", total_count);
        printf("Prakhar Umrao 230962210\n");
    }

    MPI_Finalize();
    return 0;
}
