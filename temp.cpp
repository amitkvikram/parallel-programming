#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

void *func1(void *argc){
    cout<<"Exiting\n";

    return (void*)0;
}

int main(){
    pthread_t tid;
    if(pthread_create(&tid, NULL, func1, NULL) != 0){
        cout<<"Error in creating thread\n";
    }
    int x;
    while(!(cin>>x)){

    }
    cout<<"Here\n";

    if(pthread_detach(tid) != 0){
        cout<<errno<<endl;
    }
    else{
        cout<<"Detaching Successful\n";
    }
}