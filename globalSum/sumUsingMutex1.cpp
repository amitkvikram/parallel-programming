#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

long long g_sum = 0;
long long g_n;
int g_threadCount;

pthread_mutex_t g_sumMtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    long long myStart_i;
    long long myEnd_i;
} ThreadData;

void *threadSum(void *argc){
    ThreadData myData = *(ThreadData *)argc;
    long long mySum = 0;
    for(int i = myData.myStart_i; i < myData.myEnd_i; i++){
        mySum += i;
    }

    pthread_mutex_lock(&g_sumMtx);
    g_sum += mySum;
    pthread_mutex_unlock(&g_sumMtx);

    return NULL;
}

void createThread(pthread_t &threadId, void *(*threadFunctionPtr)(void *), void *argc){
    if(pthread_create(&threadId, NULL, threadFunctionPtr, argc) != 0){
        cout<<"Error in thread Creation";
        exit(EXIT_FAILURE);
    }
}

int main(){
    cout<<"Number of threads: ";
    cin>>g_threadCount;
    long nPerThread;
    cout<<"number of calculation per thread: ";
    cin>>nPerThread;
    g_n = nPerThread * g_threadCount;
    pthread_t threadId[g_threadCount];
    ThreadData threadData[g_threadCount];

    chrono::time_point<std::chrono::system_clock> startTime, endTime;

    startTime = chrono::system_clock::now();
    for(int i = 0; i < g_threadCount; i++){
        threadData[i] = {nPerThread * i, nPerThread *(i + 1)};
        createThread(threadId[i], threadSum, (void *)&threadData[i]);
    }

    for(int i = 0; i < g_threadCount; i++){
        pthread_join(threadId[i], NULL);
    }

    cout<<"Sum = "<<g_sum<<endl;
    endTime = chrono::system_clock::now();

    chrono::duration<double> timeTaken = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
    cout<<"Time Taken = "<<timeTaken.count()<<" seconds";
}

