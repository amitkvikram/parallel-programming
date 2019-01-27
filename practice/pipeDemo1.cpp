#include<bits/stdc++.h>
#include<unistd.h>
#include <fcntl.h> // library for fcntl function 
extern int errno;
#define EAGAIN 11
using namespace std;

typedef struct{
    int time;
    int dist;
} Str;

int main(){
    int n, fd[2];  //fd[0] is open for reading, and fd[1] is open for writing
    pid_t pid;
    char line[33];
    int dist = 0;
    int *buffer;
    Str s;
    cout<<"size of s = "<<sizeof(s)<<endl;

    if(pipe(fd) < 0){
        cout<<"pipe error\n";
    }
    if(fcntl(fd[0], F_SETFL, O_NONBLOCK) >=0){
        "Nonblocking mode set\n";
    }
    if((pid = fork()) < 0){
        cout<<"fork error\n";
    }
    if(pid > 0){    //parent  writes
        cout<<"parent starts\n";
        dist = 10;
        s.dist = 10;
        s.time = 2;
        close(fd[0]);
        // write(fd[1], "hello world\n", 12);
        // int n1 = write(fd[1], &s, sizeof(s));
        // int n2 = write(fd[1], &s, sizeof(s));
        // cout<<"written = "<<n1<<" "<<n2<<endl;
        cout<<"parent ends\n";
    }   
    else{          // child reads
        cout<<"Child starts\n";
        close(fd[1]);
        int temp = 10;
        // buffer = &dist;
        // n = read(fd[0], &s, sizeof(s));
        // cout<<"read "<<n<<" bytes\n";
        // write(STDOUT_FILENO, line, n);
        // cout<<endl;
        // n = read(fd[0], line, 6);
        n = read(fd[0], &temp, sizeof(temp));
        cout<<n<<" bytes read\n";
        cout<<"temp = "<<temp<<endl;
        // fflush(stdout);
        // n = write(STDOUT_FILENO, line, 4);
        // write(STDOUT_FILENO, buffer, n);
        // cout<<"written "<<n<<endl;
        // cout<<dist<<endl;
        // cout<<"Data = "<<s.time<<" "<<s.dist<<endl;
        cout<<"Child ends\n";
    }   
    exit(0);
}
