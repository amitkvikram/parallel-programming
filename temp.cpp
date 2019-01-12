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
	int arr[2];
	arr[0] = 1;
	arr[1] = 2;
	int &temp = arr[0];
	temp = 23;
	cout<<arr[0]<<endl;
}
