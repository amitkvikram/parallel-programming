#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

int main(){
    int var = 1;
    int pid;

    cout<<"Current Process Pid = "<<getpid()<<endl;
    cout<<"Before Fork\n";
    cout<<"You took hell of a shot\n";

    pid = fork();
    if(pid == 0){   //Child Process
        var++;
        cout<<"(We are in child) Pid = "<<getpid()<<endl;
    }else{
        cout<<"(We are in parent)Child Pid = "<<pid<<endl;
    }
    
    cout<<"Pid = "<<getpid()<<" "<<"var = "<<var<<endl;
}