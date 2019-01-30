#include<bits/stdc++.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

using namespace std;

float sum1 = 0, sum2 = 0;

typedef struct{
    long long START;
    long long END;
    float SUM;
} threadData;

void *func1(void *threadArgc){
    threadData *myData = (threadData *) threadArgc;
    // cout<<myData->START<<" "<< myData->END<<endl;
    for(long long i = myData -> START; i < myData -> END; i++){
        myData -> SUM += ((i % 2)?-1.0:1.0)/(2*i + 1);
    }
    pthread_exit((void*) 0);
}

int main(){
    long long numThread = 2, n = 4e9;
    pthread_t tid[numThread];
    threadData tdData[numThread];

    for(long long i = 0; i < numThread; i++){
        tdData[i].START = i * (n/numThread);
        tdData[i].END = (i + 1) * ( n/numThread );
        cout<<tdData[i].START<<" "<<tdData[i].END<<endl;
        tdData[i].SUM = 0;
    }

    /*Thread Creation*/
    for(int i = 0; i < numThread; i++){
        pthread_create(&tid[i], NULL, func1, (void *)&tdData[i]);
    }
 
    /*Block Main Thread*/
    for(int i = 0; i < numThread; i++){
        pthread_join(tid[i], NULL);
    }
    
    /*Print Sum*/
    float SUM = 0;
    for(int i = 0; i < numThread; i ++){
        SUM += tdData[i].SUM;
    }
    cout<<4*SUM<<endl;
}