#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<mpi.h>

using namespace std;

double f(double x){
    return x*x + 4 + x*2;
}

double getTrapezoidArea(double localA, double localB, int localN, double h){
    double approx = (f(localA) + f(localB)) /2.0;
    for(int i = 1; i < localN; i++){
        approx += f(localA + i * h);
    }
    approx*=h;

    return approx;
}

int main(int argc, char *argv[]){
    int commSz, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commSz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    double a, b;
    int n;
    if(argc < 4){
        cout<<"Command Line Arguments not found";
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    else
    {
        a = atof(argv[1]);
        b = atof(argv[2]);
        n = atoi(argv[3]);
    }

    double h = (b - a)/n;
    int localN = n/commSz;
    double localA = a + h * localN * my_rank;
    double localB = a + h * localN * (my_rank + 1);
    double localIntegral = getTrapezoidArea(localA, localB, localN, h);
    
    if(my_rank != 0){
        MPI_Send(&localIntegral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else{
        double totalIntegral = localIntegral;
        for(int i = 1; i < commSz; i++){
            MPI_Recv(&localIntegral, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalIntegral += localIntegral;
        }
        printf("Integral = %lf\n", totalIntegral);
    }

    MPI_Finalize();
}