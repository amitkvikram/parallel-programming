#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>


typedef long long ll;
using namespace std;

ll threadCount;   
ll counter = 0;    //Number of thread which reached the barrier point

pthread_mutex_t g_counterMutex = PTHREAD_MUTEX_INITIALIZER;

void * threadFunction(void * argc){
    ll id = *(ll*)argc;
    pthread_mutex_lock(&g_counterMutex);
    counter++;
    pthread_mutex_unlock(&g_counterMutex);

    while(counter < threadCount);
}

void createThread(pthread_t *tidp, void *(*fun_ptr)(void *), ll &num){
    if( pthread_create(tidp, NULL, fun_ptr, (void*)&num) != 0 ){
        cout<<"Error in Thread Creation\n";
        exit(EXIT_FAILURE);
    }
}

int main(){
    pthread_t tid[threadCount];
    ll threadInd[threadCount];  

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

    cout<<"Process Exiting\n";

    chrono::duration<double> timeTaken = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
    cout<<"Time Taken = "<<timeTaken.count()<<" seconds";
}

