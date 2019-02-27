#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>

using namespace std;

float f(float x){
    return x*x;
}

int main(int argc, char *argv[]){
    double a, b;
    int n;

    if(argc < 4){
        cout<<"Command Line Arguments not found";
    }
    else{
        a = atof(argv[1]);
        b = atof(argv[2]);
        n = atoi(argv[3]);
    }


    float h = (b - a)/n;
    float approx = (f(a)+f(b))/2.0;

    for(int i = 1; i<n; i++){
        float x_i = a + h*i;
        approx += f(x_i);
    }

    approx = approx * h;
    printf("Area = %f\n",approx);
}