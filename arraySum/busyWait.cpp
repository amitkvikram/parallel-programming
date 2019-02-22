#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

long long g_sum = 0;
long long n;
int threadTurnFlag = 0;
int threadCount;

typedef struct{
    int myRank;
    long long myStart_i;
    long long myEnd_i;
} ThreadData;

void *threadSum(void *argc){
    ThreadData myData = *(ThreadData *)argc;
    for(int i = myData.myStart_i; i < myData.myEnd_i; i++){
        while(threadTurnFlag != myData.myRank);
        g_sum += i;
        threadTurnFlag = (threadTurnFlag + 1) % threadCount;
    }

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
    cin>>threadCount;
    long nPerThread;
    cout<<"number of calculation per thread: ";
    cin>>nPerThread;
    n = nPerThread * threadCount;
    pthread_t threadId[threadCount];
    ThreadData threadData[threadCount];

    chrono::time_point<std::chrono::system_clock> startTime, endTime;

    startTime = chrono::system_clock::now();
    for(int i = 0; i < threadCount; i++){
        threadData[i] = {i, nPerThread * i, nPerThread *(i + 1)};
        createThread(threadId[i], threadSum, (void *)&threadData[i]);
    }

    for(int i = 0; i < threadCount; i++){
        pthread_join(threadId[i], NULL);
    }

    cout<<"Sum = "<<g_sum<<endl;
    endTime = chrono::system_clock::now();

    chrono::duration<double> timeTaken = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
    cout<<"Time Taken = "<<timeTaken.count()<<" seconds";
}