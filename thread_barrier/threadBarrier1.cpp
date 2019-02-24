/* Implementing thread barrier using Counting semaphore 
 * For details see README.md file.
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

ll threadCount;   
ll counter = 0;    //Number of thread which reached the barrier point

/*Semphore File Names*/
char sem_barrier[] = "/barrierSemaphore", sem_count[] = "/countSemaphore", sem_terminal[] = "/semTerm";
sem_t *semBarrier, *semCount, *semTerm;

void * threadFunction(void * argc){
    ll id = *(ll*)argc;

    // sem_wait(semTerm);
    // cout<<id<<": "<<"Barrier Starts\n";
    // sem_post(semTerm);
    sem_wait(semCount);
    counter += 1;
    if(counter != threadCount){
        sem_post(semCount);
        sem_wait(semBarrier);
    }
    else{
        sem_post(semCount);
        for(int i = 0; i < threadCount - 1; i++){
            sem_post(semBarrier);
        }
    }
    // sem_wait(semTerm);
    // cout<<id<<": "<<"Barrier Ends\n";
    // sem_post(semTerm);
}

//A helper function to create thread.
void createThread(pthread_t *tidp, void *(*fun_ptr)(void *), ll &num){
    if( pthread_create(tidp, NULL, fun_ptr, (void*)&num) != 0 ){
        cout<<"Error in Thread Creation\n";
        exit(EXIT_FAILURE);
    }
}

int main(){
    cout<<"Number of threads: ";
    cin>>threadCount;
    pthread_t tid[threadCount];
    ll threadInd[threadCount];  

    //Unlink semaphore
    sem_unlink(sem_barrier);
    sem_unlink(sem_count);
    sem_unlink(sem_terminal);

    //Initialize Semaphore
    semBarrier = sem_open(sem_barrier, O_CREAT, 0666, 0);
    semCount = sem_open(sem_count, O_CREAT, 0666, 1);
    semTerm = sem_open(sem_count, O_CREAT, 0666, 1); 

    double totTimeTaken = 0, maxTimeTaken = 0.0, minTimeTaken = 1e8;
    int numExperiment = 7;

    for(int exp_i = 0; exp_i < numExperiment; exp_i ++){
        counter = 0;
        chrono::time_point<std::chrono::system_clock> startTime, endTime;
        startTime = chrono::system_clock::now();

        for(ll i = 0; i < threadCount; i++){
            threadInd[i] = i + 1;
            createThread( &tid[i], threadFunction, threadInd[i] );
        }

        for(int i = 0; i < threadCount; i++){
            pthread_join(tid[i], NULL);
        }

        endTime = chrono::system_clock::now();


        chrono::duration<double> timeTaken = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
        totTimeTaken += timeTaken.count()/threadCount;
        maxTimeTaken = max(maxTimeTaken, timeTaken.count()/threadCount);
        minTimeTaken = min(minTimeTaken, timeTaken.count()/threadCount);
    }

    cout<<"Average time Taken = "<<totTimeTaken/numExperiment<<endl;
    cout<<"Minimum time Taken = "<<minTimeTaken<<endl;
    cout<<"Maximum time Taken = "<<maxTimeTaken<<endl;
}
