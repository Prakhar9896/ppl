#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    char S1[100], S2[100];
    int len, chunk;

    if(rank == 0) {
        printf("Enter S1: "); scanf("%s", S1);
        printf("Enter S2: "); scanf("%s", S2);

        len = strlen(S1);

        if(len != strlen(S2)) {
            printf("Error: S1 and S2 must be same length\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        if(len % size != 0) {
            printf("Error: length must be divisible by number of processes\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(S1, len, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(S2, len, MPI_CHAR, 0, MPI_COMM_WORLD);

    chunk = len / size;

    char p1[chunk], p2[chunk];
    MPI_Scatter(S1, chunk, MPI_CHAR, p1, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, chunk, MPI_CHAR, p2, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);

    char local[2 * chunk];
    for(int i = 0; i < chunk; i++) {
        local[2*i]   = p1[i];
        local[2*i+1] = p2[i];
    }

    char result[200];
    MPI_Gather(local, 2*chunk, MPI_CHAR, result, 2*chunk, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        result[2*len] = '\0';
        printf("Resultant: %s\n", result);
        printf("Prakhar Umrao 230962210\n");
    }

    MPI_Finalize();
    return 0;
}
