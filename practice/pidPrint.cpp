#include<bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *argv[]){
    printf("Process Id: %d\n", getpid());
    printf("Parent Id: %d\n", getppid());
}