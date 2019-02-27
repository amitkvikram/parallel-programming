#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>

using namespace std;

float f(float x){
    return x*x + 4 + x*2;
}

int main(int argc, char *argv[]){
    double a, b;
    int n;

    if(argc < 4){
        cout<<"Command Line Arguments not found";
        exit(EXIT_FAILURE);
    }
    else{
        a = atof(argv[1]);
        b = atof(argv[2]);
        n = atoi(argv[3]);
    }


    double h = (b - a)/n;
    double approx = (f(a)+f(b))/2.0;

    for(int i = 1; i<n; i++){
        double x_i = a + h*i;
        approx += f(x_i);
    }

    approx = approx * h;
    printf("Integral = %lf\n",approx);
}