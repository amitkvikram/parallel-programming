/* Problem statement: Message passing between threads. thread x sends message to thread y. 
                    Each thread have a shared memory queue, when source 
                    thread wants to send message to destination it enqueues in the destination thread's queue.

    Library Used: Unnamed semaphore, std::queue.
 */

#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>

using namespace std;

int numThreads = 4;
vector<queue<string>> MessageQueue;

//Terminal semaphore to avoid intermixing of output of two or more threads
//countSem semaphore to increment the couter
sem_t terminalSem, countSem;
//Semaphore for each queue
vector<sem_t> queueSem;
int counter = 0;   //keeps track of number of threads which have finished sending messages

//Barrier semaphore
sem_t barrierSem, barrierCountSem;
int barrierCount = 0;

void *func1(void *argc){
    int src = *(int *)argc;
    int numMessages = max(2, rand() % 6);

    sem_wait(&terminalSem);
    cout<<("Thread" + to_string(src) + " sends "+ to_string(numMessages) + " messages\n");
    sem_post(&terminalSem);

    /* --------Barrier-------------*/
    sem_wait(&barrierCountSem);
    barrierCount++;
    if(barrierCount == numThreads){
        barrierCount = 0;
        sem_post(&barrierCountSem);
        for(int i = 0; i < numThreads - 1; i++){
            sem_post(&barrierSem);
        }
    }
    else{
        sem_post(&barrierCountSem);
        sem_wait(&barrierSem);
    }
    /*-----------------------------*/

    for(int i = 0; i < numMessages; i++){ 
        //Choose random destination
        int dest = (rand() % numThreads);
        if(dest == src) dest = (dest + 1) % numThreads;

        //Send Message
        string info = "Thread"+to_string(src) + "--> Thread"+ to_string(dest);
        string msg = info + ": Message" + to_string(i);

        sem_wait(&queueSem[dest]);
        MessageQueue[dest].push(msg);
        sem_post(&queueSem[dest]);

        //Receive Message if any
        sem_wait(&queueSem[src]);
        if( !MessageQueue[src].empty() ){
            msg = MessageQueue[src].front();
            MessageQueue[src].pop();
            sem_wait(&terminalSem);
            cout<<msg<<endl;
            sem_post(&terminalSem);
        }
        sem_post(&queueSem[src]);
    }
    sem_wait(&countSem);
    counter++;
    sem_post(&countSem);
    //Wait until other threads have finished sending messages
    //and keep receiving messages if any
    while(true){
        if(counter == numThreads && MessageQueue[src].empty()){
            break;
        }

        //Receive message if any
        sem_wait(&queueSem[src]);
        if( !MessageQueue[src].empty()){
            string msg = MessageQueue[src].front();
            MessageQueue[src].pop();
            sem_wait(&terminalSem);
            cout<<msg<<endl;
            sem_post(&terminalSem);
        }
        sem_post(&queueSem[src]);
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
    MessageQueue.resize(numThreads);
    queueSem.resize(numThreads);

    //seed 
    srand(time(0));

    //Initialize unnamed semaphores
    sem_init(&terminalSem, 0, 1);
    for(int i = 0; i < numThreads; i++){
        sem_init(&queueSem[i], 0, 1);;
    }
    sem_init(&countSem, 0, 1);
    sem_init(&barrierSem, 0, 0);
    sem_init(&barrierCountSem, 0, 1);

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

