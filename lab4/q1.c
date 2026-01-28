#include <mpi.h>
#include <stdio.h>

long long factorial(int n) {
    long long f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

int main(int argc, char *argv[]) {
    int rank, size;
    long long fact, scan_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size <= 0) {
        MPI_Finalize();
        return 0;
    }

    fact = factorial(rank + 1);

    MPI_Scan(&fact, &scan_sum, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

    if (rank == size - 1) {
        printf("Sum of factorials = %lld\n", scan_sum);
        printf("Prakhar Umrao 230962210\n");

    }

    MPI_Finalize();
    return 0;
}
