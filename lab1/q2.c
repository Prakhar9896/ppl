#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank,size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a=10,b=20;

    if(rank==0) printf("\nAddition: %d + %d = %d\n",a,b,a+b);
    else if(rank==1) printf("Subtraction: %d - %d = %d\n",a,b,a-b);
    else if(rank==2) printf("Multiplication: %d * %d = %d\n",a,b,a*b);
    else if(rank==3) printf("Division: %d / %d = %d\n",a,b,a/b);
    
    MPI_Finalize();
    return 0;
}
