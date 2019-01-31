/* Implementing thread barrier using Counting semaphore 
 * For details see THREAD_BARRIER.md file.
**/
#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#ifndef O_CREAT
#define O_CREAT 0100
#endif

typedef long long ll;
using namespace std;

ll numThread = 5;   //Total number of thread to be created
ll counter = 0;    //Number of thread which reached the barrier point

/*Semphore File Names*/
char sem_barrier[] = "/barrierSemaphore", sem_count[] = "/countSemaphore", sem_terminal[] = "/semTerm";
sem_t *semBarrier, *semCount, *semTerm;

unordered_map<ll, ll> id_map;

void * func1(void * argc){
    ll id = *(ll*)argc;
    for(int i = 0; i < 10000000; i++){}
    sem_wait(semTerm);
    sem_post(semTerm);
    sem_wait(semCount);
    counter += 1;
    if(counter != numThread){
        sem_post(semCount);
        cout<<id<<": "<<"Barrier Starts\n";
        sem_wait(semBarrier);
    }
    else{
        sem_post(semCount);
        cout<<id<<": "<<"Barrier Starts\n";
        for(int i = 0; i < numThread - 1; i++){
            sem_post(semBarrier);
        }
    }
    sem_wait(semTerm);
    cout<<id<<": "<<"Barrier Ends\n";
    sem_post(semTerm);
}

//A helper function to create thread.
void createThread(pthread_t *tidp, void *(*fun_ptr)(void *), ll &num){
    if( pthread_create(tidp, NULL, fun_ptr, (void*)&num) != 0 ){
        cout<<"Error in Thread Creation\n";
        exit(EXIT_FAILURE);
    }
}

int main(){
    pthread_t tid[numThread];
    ll threadInd[numThread];  

    //Unlink semaphore
    sem_unlink(sem_barrier);
    sem_unlink(sem_count);
    sem_unlink(sem_terminal);

    //Initialize Semaphore
    semBarrier = sem_open(sem_barrier, O_CREAT, 0666, 0);
    semCount = sem_open(sem_count, O_CREAT, 0666, 1);
    semTerm = sem_open(sem_count, O_CREAT, 0666, 1);

    //Create Threads
    for(ll i = 0; i < numThread; i++){
        threadInd[i] = i + 1;
        createThread(&tid[i], func1, threadInd[i]);
    }

    //Join Threads
    for(int i = 0; i < numThread; i++){
        pthread_join(tid[i], NULL);
    }
    cout<<"Process Exiting\n";
}
