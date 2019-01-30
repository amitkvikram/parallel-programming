#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;
typedef long long ll;

typedef struct{
    long long START;
    long long END;
} threadData;

int bins = 100;
ll binArr[100] = {0};

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;   //Mutex for terminal ownership

void * func(void *threadArgc){
    threadData *tdData = (threadData *)threadArgc;
    long long ind;
    for(ll i = tdData -> START; i < tdData -> END; i++){
        ind = (rand() % 100);
        pthread_mutex_lock(&mtx);
        binArr[ind]++;
        pthread_mutex_unlock(&mtx);
    }

    pthread_exit((void *)0);
}

int main(){
    int numThread = 2;
    ll n = 1e9;

    pthread_t tid[numThread];
    threadData tdData[numThread];

    for(int i = 0; i < numThread; i ++){
        tdData[i].START = i * (n/numThread);
        tdData[i].END = (i + 1) * ( n/numThread );
        cout<<tdData[i].START<<" "<<tdData[i].END<<endl;
    }

    /*Thread Creation*/
    for(int i = 0; i < numThread; i++){
        pthread_create(&tid[i], NULL, func, (void *)&tdData[i]);
    }
 
    /*Block Main Thread*/
    for(int i = 0; i < numThread; i++){
        pthread_join(tid[i], NULL);
    }
}