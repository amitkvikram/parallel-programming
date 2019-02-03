#include<bits/stdc++.h>
#include<unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // library for fcntl function 

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

//semaphore for input and output on terminal
char terminalSemaphore[] = "/sem_terminal";
char iterSemaphore[] = "/sem_iter";

//Semaphore pointers
sem_t *mutex_iter;
sem_t *mutex1;

//SIGTERM hadler for reporter process
void handle_sigterm(int sig){
    sem_unlink(terminalSemaphore);
    sem_close(mutex1);
    exit(0);
}

//SIGTERM handler for god process
void handle_sigtermGod(int sig){
    sem_unlink(iterSemaphore);
    sem_close(mutex_iter);
    exit(0);
}

int main(){
    int trackLength = 30, pid, nByte;
    int hareToTurtle[2], turtleToHare[2];
    int godToTurtle[2], godToHare[2];
    int hareToReporter[2];
    int hareToMaster[2];

    pid_t pids[4];
    pid_t &harePid = pids[0], &turtlePid = pids[1], 
            &godPid = pids[2], &reporterPid = pids[3], masterPid= -1;
    bool processRunning[4];
    bool &hareRunning = processRunning[0], &turtleRunning = processRunning[1], 
            &godRunning = processRunning[2], &reporterRunning = processRunning[3];

    masterPid = getpid();

    //Ignore SIGCHLD signal
    signal(SIGCHLD, SIG_IGN);

    //Pipes Creation
    if( pipe(hareToTurtle) < 0  || 
        pipe(turtleToHare) < 0  ||
        pipe(godToTurtle) < 0   ||
        pipe(godToHare) < 0     ||
        pipe(hareToReporter) < 0||
        pipe(hareToMaster) < 0    ){
        cout<<"Error in Creating pipe\n";
        return 0;
    }
    /*Pipes Creation End */

    //Semaphore initialization
    mutex1 = sem_open(terminalSemaphore, O_CREAT, 0666, 1);
    mutex_iter = sem_open(iterSemaphore, O_CREAT, 0666, 1);
    sem_trywait(mutex_iter);
    sem_post(mutex_iter);
    sem_trywait(mutex1);
    sem_post(mutex1);
    /*-------------------------*/
    cout<<"Track Length = "<<trackLength<<endl;

    /*Process Creation */
    for(int i = 0; i < 4; i++){
        if( getpid() == masterPid && (pids[i] = fork()) < 0){
            cout<<"Error in Process Fork\n";
        }
        else{
            processRunning[i] = true;
        }
    }
    /*Processes Created */

    /*Some Initalization work*/
    srand (time(NULL));
    fcntl(hareToReporter[0], F_SETFL, O_NONBLOCK);
    /************************/

    if( (harePid & turtlePid & godPid & reporterPid) > 0){  //parent... 
        int status;
        result res;
        read(hareToMaster[0], &res, sizeof(res));
        cout<<"Time Taken: [Hare: "<<res.hareTime<<"][Turtle: "<<res.turtleTime<<"]\n";
        if(res.hareTime < res.turtleTime){
            cout<<"Hare is Winner\n";
        }
        else if(res.hareTime > res.turtleTime){
            cout<<"Turtle is Winner\n";
        }
        else{
            cout<<"Match Draw\n";
        }
        //Stop all the processes
        kill(reporterPid, SIGTERM);
        kill(godPid, SIGTERM);
        //Processes Stopped
    }

    else if(harePid == 0){   //Hare Process
        int sleepTime = 0;
        score s;
        details hare = {0, 0}, turtle = {0, 0};
        int temp;
        write(hareToTurtle[1], &hare, sizeof(hare));   //say turtle to run; turtle->hare->
        while(hare.dist < trackLength || turtle.dist < trackLength){
            if(turtle.dist < trackLength)
                read(turtleToHare[0], &turtle, sizeof(turtle));
            if(hare.dist < trackLength){
                read(godToHare[0], &temp, sizeof(temp));
                if(temp!=-1){
                    hare.dist = temp;
                }
                if(hare.dist > turtle.dist + (rand() % 30 + 10) && sleepTime == 0){
                    sleepTime = rand() % 30 + 20;
                }
                hare.time ++;
                if(sleepTime == 0) hare.dist+=3;
                else sleepTime--;
            }
            s = {hare.dist, turtle.dist};
            write(hareToReporter[1], &s, sizeof(s));
            write(hareToTurtle[1], &hare, sizeof(hare));
            sem_trywait(mutex_iter);
            sem_post(mutex_iter);
        }
        result res = {hare.time, turtle.time};
        write(hareToMaster[1], &res, sizeof(res));
        return 0;
    }

    else if(turtlePid == 0){  //turtle process
        details hare = {0, 0}, turtle = {0, 0};
        int temp;
        while(turtle.dist < trackLength){
            read(hareToTurtle[0], &hare, sizeof(hare));
            read(godToTurtle[0], &temp, sizeof(temp));
            if(temp!=-1){
                turtle.dist = temp;
            }
            turtle.time++;
            turtle.dist+=1;
            write(turtleToHare[1], &turtle, sizeof(turtle));
        }
        return 0;
    }

    else if(godPid == 0){    //god process
        char status;
        int newHareDist, newTurtleDist;
        signal(SIGTERM, handle_sigtermGod);
        char ch;
        while(true){
            sem_wait(mutex_iter);
            sem_wait(mutex1);
            cout<<"Want to change Position(y/n): ";
            cin>>ch;
            if(ch == 'y'){
                cout<<"GOD: Enter New Positions of Hare and turtle(space separated): ";
                cin>>newHareDist>>newTurtleDist;
            }
            else{
                newHareDist = -1;
                newTurtleDist = -1;
            }
            int n1 = write(godToHare[1], &newHareDist, sizeof(newHareDist));
            int n2 = write(godToTurtle[1], &newTurtleDist, sizeof(newTurtleDist));
            sem_post(mutex1);
        }
    }


    else{      //reporter process
        score s;
        signal(SIGTERM, handle_sigterm);
        bool moseRecent = true;
        int nByte;
        while(true){
            if((nByte = read(hareToReporter[0], &s, sizeof(s))) < 0 && !(moseRecent)){
                sem_wait(mutex1);
                cout<<"-----------------\n";
                cout<<"Hare Postion: "<<s.hareDist<<"\nTurtle Position: "<<s.turtleDist<<endl;
                moseRecent = true;
                sem_post(mutex1);
            }
            else if(nByte > 0){
                moseRecent = false;
            }
        }
    }
}
