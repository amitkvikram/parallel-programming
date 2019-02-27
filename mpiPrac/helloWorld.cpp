#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<mpi.h>

using namespace std;

const int g_MAX_STRING = 100;

int main(){
    char greeting[g_MAX_STRING];
    int comm_sz;
    int my_rank;
    int count;
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank != 0){
        sprintf(greeting, "Greeting From process %d of %d", my_rank, comm_sz);
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else{
        printf("Greeting From process %d of %d\n",my_rank, comm_sz);
        for(int i = 1; i < comm_sz; i++){
            MPI_Recv(greeting, g_MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_CHAR, &count);
            printf("%d char %s\n", count, greeting);
        }
    }

    MPI_Finalize();
}

