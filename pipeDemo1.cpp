#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

int main(){
    int n, fd[2];  //fd[0] is open for reading, and fd[1] is open for writing
    pid_t pid;
    char line[33];
    int dist = 0;
    int *buffer;

    if(pipe(fd) < 0){
        cout<<"pipe error\n";
    }
    if((pid = fork()) < 0){
        cout<<"fork error\n";
    }
    if(pid > 0){    //parent  writes
        cout<<"parent starts\n";
        dist = 10;
        close(fd[0]);
        // write(fd[1], "hello world\n", 12);
        write(fd[1], &dist, sizeof(int));
        cout<<"parent ends\n";
    }   
    else{          // child reads
        cout<<"Child starts\n";
        close(fd[1]);
        // buffer = &dist;
        n = read(fd[0], &dist, sizeof(int));
        cout<<"read "<<n<<" bytes\n";
        // write(STDOUT_FILENO, line, n);
        // cout<<endl;
        // n = read(fd[0], line, 6);
        // fflush(stdout);
        // n = write(STDOUT_FILENO, line, 4);
        // write(STDOUT_FILENO, buffer, n);
        // cout<<"written "<<n<<endl;
        cout<<dist<<endl;
        cout<<"Child ends\n";
    }   
    exit(0);
}
