/* Problem statement: Message passing between threads. thread x sends message to thread y. 
                    Each thread have a shared memory queue, when source 
                    thread wants to send message to destination it enqueues in the destination thread's queue.

    Library Used: Unnamed semaphore, std::queue.
 */

#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>

using namespace std;

int numThreads = 7;
vector<queue<string>> Message;

sem_t terminalSem;
vector<sem_t> queueSem;

void *func1(void *argc){
    int src = *(int *)argc;
    int dest = (rand() % numThreads);
    int numMessages = rand() % 20;
    if(dest == src) dest = (dest + 1)%numThreads;

    sem_wait(&terminalSem);
    cout<<("Thread" + to_string(src) + " sends "+ to_string(numMessages) + " message to Thread" 
                            + to_string(dest) + "\n");
    sem_post(&terminalSem);
    /* --------Barrier-------------*/
    /*-----------------------------*/

    string info = "Thread"+to_string(src) + "--> Thread"+ to_string(dest);
    for(int i = 0; i < numMessages; i++){ 
        string msg = info + ": Message" + to_string(i) + "\n";
        Message[dest].push(msg);

        w
    }
}

void createThread(pthread_t &tid, void *(*funcptr)(void *), void *index){
    if(pthread_create(&tid, NULL, funcptr, index) != 0){
        cout<<"Error in thread creation\n";
        exit(EXIT_FAILURE);
    }
}

int main(){
    pthread_t tid[numThreads];
    int threadInd[numThreads];
    Message.resize(numThreads);
    queueSem.resize(numThreads);

    //Initialize unnamed semaphores
    sem_init(&terminalSem, 0, 1);
    for(int i = 0; i < numThreads; i++){
        sem_init(&queueSem[i], 0, 1);;
    }

    //Create Threads
    for(int i = 0; i < numThreads; i++){
        threadInd[i] = i;
        createThread(tid[i], func1, (void *)&threadInd[i]);
    }

    //Join threads
    for(int i = 0; i < numThreads; i++){
        pthread_join(tid[i], NULL);
    }
}

