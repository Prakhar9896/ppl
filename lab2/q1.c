#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv) {
    int rank, size;
    char word[100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) printf("This program requires at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        strcpy(word, "HeLLO");
        printf("Process 0: Sending word '%s' to Process 1\n", word);
        
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        
        MPI_Recv(word, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
        printf("Process 0: Received toggled word '%s' back from Process 1\n", word);

    } else if (rank == 1) {
        MPI_Recv(word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        
        for (int i = 0; word[i]!= '\0'; i++) {
            if (isupper(word[i])) word[i] = tolower(word[i]);
            else if (islower(word[i])) word[i] = toupper(word[i]);
        }
        
        printf("Process 1: Toggled word to '%s' and sending back\n", word);
        
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }


    MPI_Finalize();
    printf("Prakhar Umrao 230962210\n");
    return 0;
}