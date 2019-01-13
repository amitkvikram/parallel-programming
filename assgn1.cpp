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
    int trackLength = 100, pid, nByte;
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
    cout<<"Master Pid = "<<masterPid<<endl;

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

    /*Process Creation */
    for(int i = 0; i < 4; i++){
        if( getpid() == masterPid && (pids[i] = fork()) < 0){
            cout<<"Error in Hare Process Fork\n";
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
        write(hareToTurtle[1], &hare, sizeof(hare));   //say turtle to run; turtle->hare->
        mutex_iter = sem_open(iterSemaphore, O_CREAT, 0644, 1);
        while(hare.dist < trackLength || turtle.dist < trackLength){
            cout<<"hare Scheduled\n";
            if(turtle.dist < trackLength)
                read(turtleToHare[0], &turtle, sizeof(turtle));
            if(hare.dist < trackLength){
                read(godToHare[0], &hare.dist, sizeof(hare.dist));
                if(hare.dist > turtle.dist + (rand() % 30 + 10) && sleepTime == 0){
                    // cout<<"sleeping\n";
                    sleepTime = rand() % 30 + 20;
                }
                hare.time ++;
                if(sleepTime == 0) hare.dist+=3;
                else sleepTime--;
            }
            cout<<"no\n";
            s = {hare.dist, turtle.dist};
            write(hareToReporter[1], &s, sizeof(s));
            write(hareToTurtle[1], &hare, sizeof(hare));
            sem_trywait(mutex_iter);
            sem_post(mutex_iter);
            cout<<"hare1\n";
        }
        result res = {hare.time, turtle.time};
        write(hareToMaster[1], &res, sizeof(res));
        cout<<"Hare Exited\n";
        return 0;
    }

    else if(turtlePid == 0){  //turtle process
        cout<<"turtle process: "<<getpid()<<endl;
        details hare = {0, 0}, turtle = {0, 0};
        while(turtle.dist < trackLength){
            cout<<"Turtle Sheduled\n";
            read(hareToTurtle[0], &hare, sizeof(hare));
            read(godToHare[0], &turtle.dist, sizeof(turtle.dist));
            turtle.time++;
            turtle.dist+=1;
            write(turtleToHare[1], &turtle, sizeof(turtle));
        }
        cout<<"Turtle Exited\n";
        return 0;
    }

    else if(godPid == 0){    //god process
        cout<<"god process: "<<getpid()<<endl;
        char status;
        int newHareDist, newTurtleDist;
        mutex1 = sem_open(terminalSemaphore, O_CREAT, 0644, 1);
        mutex_iter = sem_open(iterSemaphore, O_CREAT, 0644, 1);
        signal(SIGTERM, handle_sigtermGod);
        while(true){
            cout<<"god scheduled\n";
            // if(sem_trywait(mutex_iter) == -1){
            //     cout<<"god in trouble\n";
            // }
            sem_wait(mutex_iter);
            cout<<"god1\n";
            sem_wait(mutex1);
            cout<<"god turn\n";
            cout<<"Enter New Positions of Hare and turtle(space separated): ";
            cin>>newHareDist>>newTurtleDist;
            write(godToHare[1], &newHareDist, sizeof(newHareDist));
            write(godToTurtle[1], &newTurtleDist, sizeof(newTurtleDist));
            sem_post(mutex1);
        }
    }


    else{      //reporter process
        cout<<"reporter process: "<<getpid()<<endl;
        score s;
        mutex1 = sem_open(terminalSemaphore, O_CREAT, 0644, 1);
        signal(SIGTERM, handle_sigterm);
        bool moseRecent = true;
        int nByte;
        while(true){
            // while(())
            // cout<<"reporter Scheduled\n";
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
            // break;
        }
        // signal()
    }
    // exit(0);
}
