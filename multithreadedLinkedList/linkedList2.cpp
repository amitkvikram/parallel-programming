//Lock Per List
#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

typedef struct{
    int myRank;
    long long myStart_i;
    long long myEnd_i;
} ThreadData;

typedef struct{
    string op;
    int val;
}ListOperations;

vector<ListOperations> operationsList;
double g_totTime;
pthread_mutex_t g_totTimeMutex = PTHREAD_MUTEX_INITIALIZER;
int g_threadCount, g_counter = 0;
pthread_cond_t g_condVar;
pthread_mutex_t g_mutex;

class ListNode{
public:
    int data;
    ListNode *next;

    ListNode(const int x = -1, ListNode *p = nullptr){
        data = x;
        next = p;
    }
};

class LinkedList{
private:
    pthread_rwlock_t q_lock;

public: 
    ListNode *head;

    LinkedList(){
        head = new ListNode;
        pthread_rwlock_init(&q_lock, NULL);
    }

    ~LinkedList(){
        ListNode *currP = head->next;
        pthread_rwlock_destroy(&q_lock);
        while(currP != nullptr){
            ListNode *tempP = currP->next;
            delete currP;
            currP = tempP;
        }

        delete head;
    }

    bool member(int val);
    bool insert(int val);
    bool deleteFromList(int val);
    void readLock(){
        pthread_rwlock_rdlock(&q_lock);
    }

    void writeLock(){
        pthread_rwlock_wrlock(&q_lock);
    }

    void unlock(){
        pthread_rwlock_unlock(&q_lock);
    }
};

bool LinkedList::member(int val){
    readLock();
    ListNode *currP = head->next;
    while(currP != nullptr && currP->data < val){
        currP = currP->next;
    }

    if(currP == nullptr || currP->data > val){
        unlock();
        return false;
    }
    else{
        unlock();
        return true;
    }
}

bool LinkedList::insert(int val){
    writeLock();
    ListNode *currP = head;
    while(currP->next != nullptr && currP->next->data < val){
        currP = currP->next;
    }

    if(currP->next == nullptr || currP->next->data > val){
        ListNode *nextNode = new ListNode(val);
        nextNode->next =currP->next;
        currP->next = nextNode;
        unlock();
        return true;
    }
    else{
        unlock();
        return false;
    }
}

bool LinkedList::deleteFromList(int val){
    writeLock();
    ListNode *currP = head;
    while(currP -> next != nullptr && currP->next->data < val){
        currP = currP ->next;
    }

    if(currP -> next == nullptr || currP->next->data > val){
        unlock();
        return false;
    }
    else{
        ListNode *tempNode = currP->next;
        currP->next = currP->next->next;
        delete tempNode;
        unlock();
        return true;
    }
}


LinkedList linkedList;

void *threadFunction(void *argc){
    ThreadData myData = *(ThreadData *)argc;

    chrono::time_point<std::chrono::system_clock> my_startTime, my_endTime;

    pthread_mutex_lock(&g_mutex);
    g_counter++;
    if(g_counter == g_threadCount){
        g_counter = 0;
        pthread_cond_broadcast(&g_condVar);
    }
    else{
        while( pthread_cond_wait(&g_condVar, &g_mutex) !=0 );
    }
    pthread_mutex_unlock(&g_mutex);
    my_startTime = chrono::system_clock::now();

    for(int i = myData.myStart_i; i < myData.myEnd_i; i++){

        if(operationsList[i].op == "insert"){
            linkedList.insert(operationsList[i].val);
        }else if(operationsList[i].op == "member"){
            linkedList.member(operationsList[i].val);
        }else{
            linkedList.deleteFromList(operationsList[i].val);
        }

    }

    my_endTime = chrono::system_clock::now();
    chrono::duration<double> timeTaken = 
                            chrono::duration_cast<chrono::duration<double>>(my_endTime - my_startTime);

    pthread_mutex_lock(&g_totTimeMutex);
    g_totTime = max(g_totTime, timeTaken.count());
    pthread_mutex_unlock(&g_totTimeMutex);
}

void createThread(pthread_t &tid, void *(*fun_ptr)(void *), void *argc){
    if( pthread_create(&tid, NULL, fun_ptr, argc) != 0 ){
        cout<<"Error in Thread Creation\n";
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){
    if(argc >=2){
        g_threadCount = atoi(argv[1]);
        // cout<<"ThreadCount = "<<g_threadCount<<endl;
    }else{
        // cout<<"threadCount Not Passed";
        exit(EXIT_FAILURE);
    }

    int initialNum, val, numOperations;
    cin>>initialNum;
    for(int i = 0; i < initialNum; i++){
        cin>>val;
        linkedList.insert(val);
    }

    pthread_t threadId[g_threadCount];
    ThreadData threadData[g_threadCount];

    cin>>numOperations;
    operationsList.resize(numOperations);
    for(int i = 0; i < numOperations; i++){
        cin>>operationsList[i].op>>operationsList[i].val;
    }

    for(int i = 0; i < g_threadCount; i++){
        threadData[i] = {i, (numOperations/g_threadCount) * i, (numOperations/g_threadCount) *(i + 1)};
        createThread(threadId[i], threadFunction, (void *)&threadData[i]);
    }

    for(int i = 0; i < g_threadCount; i++){
        pthread_join(threadId[i], NULL);
    }

    // cout<<"Total Time Taken = "<<g_totTime<<endl;
    cout<<g_totTime<<endl;
}