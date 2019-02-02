/*  Problem Statement: Threre are n number of threads and thread0 sends a message to thread1,
    *thread1 sends a message to thread2, .... , thread t-2 sends a message to thread t-1 and
    *thread t-1 sends a message to thread t. After a thread sends a message it prints the message
    *and terminate.

    *Solution: Problem is solved using unnamed semaphore. 
            For details Read MESSAGE_PASSING.md.
    */

#include<bits/stdc++.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<pthread.h>
#include<semaphore.h>

using namespace std;

typedef long long ll;

int numThreads = 6;
vector<string*> Messages;
vector<sem_t> sem;

void exiting(){
    for(int i = 0; i < numThreads; i++){
        sem_destroy(&sem[i]);
    }
}

void *func( void * argc){
    int index = *(int *)argc;
    Messages[(index + 1)%numThreads] = new string("Thread" + to_string(index) + " to Thread" 
                                + to_string((index + 1) % numThreads) + "\n");
    sem_post( &sem[(index + 1)%numThreads]);
    sem_wait( &sem[index] );
    cout<<*(Messages[index]);
    sem_post( &sem[index] );
}

void createThread(pthread_t &tid, void *(*funcptr)(void *), int &index){
    if(pthread_create( &tid, NULL, funcptr, (void *) &index) != 0){
        cout<<"Error in thread creation\n";
        exit(EXIT_FAILURE);
    }
}

int main(){
    pthread_t tid[numThreads];
    int threadInd[numThreads];
    Messages.resize(numThreads);

    //In beginnig each message pointer is set to null
    for(int i = 0; i < numThreads; i++){
        Messages[i] = nullptr;
    }

    //Initialize Semaphore
    sem.resize(numThreads);
    for(int i = 0; i < numThreads; i++){
        sem_init(&sem[i], 0, 0);     //(sem_t *, pshared, initial_value) (pshared=0)=>shared between threads
    }

    //Create thread
    for(int i = 0; i < numThreads; i++){
        threadInd[i] = i;
        createThread(tid[i], func, threadInd[i]);
    }   

    //Join Thread
    for(int i = 0; i < numThreads; i++){
        if(pthread_join(tid[i], NULL) != 0){
            cout<<"Error in joining thread\n";
            exit(EXIT_FAILURE);
        }
    }

    //at exit
    atexit(exiting);
}