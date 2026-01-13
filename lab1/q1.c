#include<stdio.h>
#include<mpi.h>

long power(int x,int n){
    if(n==0)    return 1;
    else    return x*power(x,n-1);

}

int main(int argc, char *argv[])
{
    int x=3;

    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //printf("Ranks: %d\n", rank);
    

    printf("\n pow(%d,%d):%ld \n",x,rank, power(x,rank));

    MPI_Finalize();
    return 0;
}