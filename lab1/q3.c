#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank,size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char s[4]= "NEAR";

    if(rank==0){
        s[0]= s[0]+32;
        printf("\ntoggled to position %d. String is %s\n",rank,s);
    }
    else if(rank==1){
        s[1]= s[1]+32;
        printf("\ntoggled to position %d. String is %s\n",rank,s);
    }
    else if(rank==2){
        s[2]= s[2]+32;
        printf("\ntoggled to position %d. String is %s\n",rank,s);
    }
    else if(rank==3){
        s[3]= s[3]+32;
        printf("\ntoggled to position %d. String is %s\n",rank,s);
    }

    MPI_Finalize();
    return 0;
}
