// C program to illustrate 
// non I/O blocking calls 
#include <stdio.h> 
#include <bits/stdc++.h>
using namespace std;
#include <unistd.h> 
#include <fcntl.h> // library for fcntl function 
#define MSGSIZE 6 
extern int errno;
#define EAGAIN 11

int main() 
{ 
	// int arr[2];
	// arr[0] = 1;
	// arr[1] = 2;
	// int &temp = arr[0];
	// temp = 23;
	// cout<<arr[0]<<endl;

	int pid;
	pid = fork();
	if(pid > 0){
		int x;
		while(cin>>x){
			cout<<x<<endl;
			cout<<"god\n";
			cout<<getpid()<<" "<<pid<<endl;
		}
	}
	else{
		while(true){
			cout<<"child\n";
			sleep(2);
		}
	}
}
