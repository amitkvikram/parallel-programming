/* Problem statement: Message passing between threads. thread x sends message to thread y. 
                    Each thread have a shared memory queue, when source 
                    thread wants to send message to destination it enqueues in the destination thread's queue.

    Library Used: Unnamed semaphore, std::queue.
    Solution: For mutual exclusion we do busy waiting with the help of semaphore
 */

#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>

using namespace std;

int numThreads = 7;
vector<queue<string>> Message;

//Terminal semaphore to avoid intermixing of output of two or more threads
//countSem semaphore to increment the couter
sem_t terminalSem, countSem;

//There is possibility of deadlock in the case when
//thread x sends message to thread y and thread y sends message to thread x
vector<sem_t> queueSem;

int counter = 0;   //keeps track of number of threads which have finished sending messages

void *func1(void *argc){
    int src = *(int *)argc;
    int numMessages = max(2, rand() % 20);

    sem_wait(&terminalSem);
    cout<<("Thread" + to_string(src) + " sends "+ to_string(numMessages) + " messages\n");
    sem_post(&terminalSem);
    /* --------Barrier-------------*/
    /*-----------------------------*/

    for(int i = 0; i < numMessages; i++){ 
        //Choose random destination
        int dest = (rand() % numThreads);
        if(dest == src) dest = (dest + 1) % numThreads;

        //Send Message
        string info = "Thread"+to_string(src) + "--> Thread"+ to_string(dest);
        string msg = info + ": Message" + to_string(i);
        while( sem_trywait(&queueSem[dest]) != 0 ){}    //Busy Wait
        Message[dest].push(msg);
        sem_post(&queueSem[dest]);

        //Receive Message if any
        while( sem_trywait(&queueSem[src]) != 0 ){}    //Busy Wait
        if( !Message[src].empty() ){
            msg = Message[src].front();
            Message[src].pop();
            sem_wait(&terminalSem);
            cout<<msg<<endl;
            sem_post(&terminalSem);
        }
        sem_post(&queueSem[src]);
    }

    //Wait until other threads have finished sending messages
    //and keep receiving messages if any
    while(true){
        sem_wait(&countSem);
        if(counter == 6){
            sem_post(&countSem);
            break;
        }
        sem_post(&countSem);

        //Receive message if any
        sem_wait(&queueSem[src]);
        if( !Message[src].empty()){
            string msg = Message[src].front();
            Message[src].pop();
        }
        sem_post(&queueSem[src]);
    }

    //Receive all the messges in the source queue
    while(!Message[src].empty()){
        string msg = Message[src].front();
        Message[src].pop();
        sem_wait(&terminalSem);
        cout<<msg<<endl;
        sem_post(&terminalSem);
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

