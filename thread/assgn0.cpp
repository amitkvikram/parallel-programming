#include<bits/stdc++.h>
#include<unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // library for fcntl function 
#include<pthread.h>


#ifndef O_CREAT
# define O_CREAT           0100        /* Not fcntl.  */
#endif

using namespace std;
const int inf = 1e8;

typedef struct{
    int hareTime;
    int turtleTime;
} result;

typedef struct {
    int hareDist;
    int turtleDist;
} score;

typedef struct{
    int time;
    int dist;
} details;

int hareDist = 0, hareTime = 0, turtleDist = 0, turtleTime = 0;
int trackLength = 300000;

char terminalSemaphore[] = "/sem_terminal2";
sem_t *mutex1;

void handle_sigterm(int sig){
    sem_unlink(terminalSemaphore);
    sem_close(mutex1);
    exit(0);
}

void *hareFunction(void *){
    int sleepTime = 0;
    while(true){
        cout<<"hare\n";
        sem_wait(mutex1);
        if(hareDist > turtleDist + (rand() % 30 + 10) && sleepTime == 0){
            sleepTime = rand() % 30 + 20;
        }
        hareTime ++;
        if(sleepTime == 0) hareDist+=3;
        else sleepTime--;
        sem_post(mutex1);
        usleep(500);
    }
}
void *turtleFunction(void *){
    while(turtleDist < trackLength){
        // cout<<"turtle\n";
        sem_wait(mutex1);
        turtleTime++;
        turtleDist+=3;
        sem_post(mutex1);
        usleep(500);
    }
}

void *godFunction(void *){
    char ch;
    int tempHare, tempTurtle;
    cout<<"God Starts\n";
    while(turtleDist < trackLength || hareDist < trackLength){
        sem_wait(mutex1);
        // cout<<"god1\n";
        sem_wait(mutex1);
        // cout<<"god2\n";
        sem_wait(mutex1);
        // cout<<"god3\n";
        cout<<"God: Want to Change Position(y/n): ";
        cin>>ch;
        if(ch == 'y'){
            cout<<"GOD: Enter New Positions of Hare and turtle(space separated): ";
            cin>>tempHare>>tempTurtle;
            if(turtleDist < trackLength){
                turtleDist = tempTurtle;
            }
            if(hareDist < trackLength){
                hareDist = tempHare;
            }
        }
        sem_post(mutex1);
        sem_post(mutex1);
        sem_post(mutex1);
        sleep(1);
    }
}

void *reporterFunction(void *){
    while(turtleDist < trackLength || hareDist < trackLength){
        // cout<<"reporter\n";
        sem_wait(mutex1);
        cout<<"-----------------\n";
        cout<<"Hare Postion: "<<hareDist<<"\nTurtle Position: "<<turtleDist<<endl;
        sem_post(mutex1);
        usleep(100);
    }
}

int main(){
    cout<<"Pid = "<<getpid()<<endl;
    pthread_t hareTid, turtleTid, godTid, reporterTid;

    //Semaphore for terminal use
    mutex1 = sem_open(terminalSemaphore, O_CREAT, 0666, 3);
    // sem_trywait(mutex1);
    // sem_post(mutex1);
    /*-----------------*/
    srand (time(NULL));

    signal(SIGTERM, handle_sigterm);
    signal(SIGINT, handle_sigterm);
    /*Thread Creation*/
    pthread_create(&hareTid, NULL, hareFunction, NULL);
    pthread_create(&turtleTid, NULL, turtleFunction, NULL);
    pthread_create(&godTid, NULL, godFunction, NULL);
    pthread_create(&reporterTid, NULL, reporterFunction, NULL);
    /*---------------*/

    /*Block main thread*/
    // pthread_join(hareTid, NULL);
    // pthread_join(turtleTid, NULL);
    // pthread_join(godTid, NULL);
    // pthread_join(reporterTid, NULL);
    /*-----------------*/

    if(hareTime > turtleTime){
        cout<<"Winner is Hare\n";
    }
    else if(turtleTime > hareTime){
        cout<<"Winnre is Turtle\n";
    }
    else{
        cout<<"Match Draw\n";
    }
}
