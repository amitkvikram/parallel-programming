#include<bits/stdc++.h>
using namespace std;

extern char **environ;


int main(int argc, char *argv[]){
    //It will print the command line argument, more specifically argument sent when called exec
    for(int i = 0; i < argc; i++){
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    // char *thisEnv = *environ;
    // int i = 0;
    // while(thisEnv != 0){
    //     printf("environ[%d]: %s\n", i, thisEnv);
    //     i++;
    //     thisEnv = *(environ + i);
    // }
}