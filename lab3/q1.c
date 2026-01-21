#include <mpi.h>
#include <stdio.h>

long factorial(int n) {
    long f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num;
    long fact, sum;

    if (rank == 0) {
        int arr[size];
        printf("Enter %d numbers:\n", size);
        for (int i = 0; i < size; i++)
            scanf("%d", &arr[i]);

        for (int i = 1; i < size; i++)
            MPI_Send(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);

        num = arr[0];
    } else {
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    fact = factorial(num);

    MPI_Reduce(&fact, &sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of factorials = %ld\n", sum);
        printf("Prakhar Umrao 230962210");
    }

    MPI_Finalize();
    return 0;
}
