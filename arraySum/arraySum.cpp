#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;
typedef long long ll;

ll totSum = 0;
pthread_mutex_t sumMtx = PTHREAD_MUTEX_INITIALIZER;

class ThreadData{
    public:
        int numThreads;
        ll n, residue;
        ll p, rank = 0, start = 0;
        // vector<int> arr;
        vector<ll> sum;
        vector<pthread_t> tid;
        pthread_mutex_t accessMtx = PTHREAD_MUTEX_INITIALIZER;
    
    //Constructor
    ThreadData(){
        // cout<<"Enter number of Threads: ";
        // cin>>numThreads;
        // cout<<"Enter number of elements in array: ";
        // cin>>n;
        numThreads = 1;
        n = 1e8;
        sum.resize(numThreads);
        tid.resize(numThreads);
        // generateData();
        residue = n - (n/numThreads)*numThreads;
        p = numThreads;
    }

    vector<ll> getInfo(){
        pthread_mutex_lock(&accessMtx);
        vector<ll> v;
        if(p > 0){
            p--; rank++;
            if(residue > 0){
                residue--;
                v = {rank, start, start + (n/numThreads) + 1};
                start = start + (n/numThreads) + 1;
            }
            else{
                v = {};
                v = {rank, start, start + (n/numThreads)};
                start = start + (n/numThreads);
            }
        }
        else{
            v = {-1, -1, -1};
        }

        pthread_mutex_unlock(&accessMtx);
        return v;
    }
};

void * func(void *argc){
    ThreadData &master = *(ThreadData*) argc;
    vector<ll> info = master.getInfo();
    ll my_rank = info[0], my_start = info[1], my_end = info[2];
    ll my_sum = 0;
    cout<<my_rank<<" "<<my_start<<" "<<my_end<<endl;
    for(int i = my_start; i < my_end; i++){
        my_sum += (rand() % 10000);
    }

    master.sum[my_rank - 1] = my_sum;
}

void createThread(pthread_t &tid, void *(*funptr)(void *), void *argc){
    if(pthread_create(&tid, NULL, funptr, argc) != 0){
        cout<<"Error in thread Creation\n";
        exit(EXIT_FAILURE);
    }
}

int main(){
    ThreadData master;
    //Create threads
    for(int i = 0; i < master.numThreads; i++){
        createThread(master.tid[i], func, (void *)&master);
    }

    //Join Threads
    for(int i = 0; i < master.numThreads; i++){
        pthread_join(master.tid[i], NULL);
    }

    cout<<totSum<<endl;

}