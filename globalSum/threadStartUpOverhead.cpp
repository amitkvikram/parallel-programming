#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

void *threadFunction(void *argc){
    return NULL;
}

void createThread(pthread_t &threadId, void *(*threadFunctionPtr)(void *), void *argc){
    if(pthread_create(&threadId, NULL, threadFunctionPtr, argc) != 0){
        cout<<"Error in thread Creation";
        exit(EXIT_FAILURE);
    }
}

int main(){
    pthread_t threadId;
    createThread(threadId, threadFunction, NULL);
}