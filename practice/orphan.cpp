#include<bits/stdc++.h>
#include<unistd.h>
#include <sys/wait.h>

int main() 
{ 
    // Create a child process       
    int pid = fork(); 
    thread.out: assgn1.cpp
	g++ -pthread assgn1.cpp -o thread.out
  
    if (pid > 0) 
        printf("in parent process"); 
  
    // Note that pid is 0 in child process 
    // and negative if fork() fails 
    else if (pid == 0) 
    { 
        sleep(5); 
        printf("in child process"); 
    } 
  
    return 0; 
} 