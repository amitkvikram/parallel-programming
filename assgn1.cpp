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

//SIGTERM hadler for reporter process
void handle_sigterm(int sig){
    // cout<<"hadling termination\n";
    sem_unlink(terminalSemaphore);
    // cout<<"handled\n";
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

    fcntl(hareToReporter[0], F_SETFL, O_NONBLOCK);

    /************************/

    if( (harePid & turtlePid & godPid & reporterPid) > 0){  //parent... 
        int status;
        cout<<"Parent Process: "<<"pid = "<<getpid()<<endl;
        cout<<"Parent Process: "<<"harePid turtlePid godPid reporterPid\n";
        cout<<"Parent Process: "<<harePid<<" "<<turtlePid<<" "<<godPid<<" "<<reporterPid<<endl;
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
        // cout<<"god killed\n";
        waitpid(reporterPid, &status, 0);
        waitpid(godPid, &status, 0);
        waitpid(harePid, &status, 0);
        waitpid(turtlePid, &status, 0);
        //Processes Stopped
    }

    else if(harePid == 0){   //Hare Process
        cout<<"HareProces: "<<getpid()<<endl; 
        int sleepTime = 0;
        score s;
        details hare = {0, 0}, turtle = {0, 0};
        write(hareToTurtle[1], &hare, sizeof(hare));   //say turtle to run; urtle->hare->
        while(hare.dist < trackLength || turtle.dist < trackLength){
            // cout<<"hare Scheduled\n";
            if(turtle.dist < trackLength)
                read(turtleToHare[0], &turtle, sizeof(turtle));
            if(hare.dist < trackLength){
                //read(godToHare[0], &hare.dist, sizeof(hare.dist));
                if(hare.dist > turtle.dist + 1 && sleepTime == 0){
                    cout<<"sleeping\n";
                    sleepTime = 60;
                }
                hare.time ++;
                if(sleepTime == 0) hare.dist+=3;
                else sleepTime--;
            }
            s = {hare.dist, turtle.dist};
            write(hareToReporter[1], &s, sizeof(s));
            write(hareToTurtle[1], &hare, sizeof(hare));
        }
        result res = {hare.time, turtle.time};
        write(hareToMaster[1], &res, sizeof(res));
        // cout<<"Hare Exited\n";
        return 0;
    }

    else if(turtlePid == 0){  //turtle process
        cout<<"turtle process: "<<getpid()<<endl;
        details hare = {0, 0}, turtle = {0, 0};
        while(turtle.dist < trackLength){
            // cout<<"Turtle Sheduled\n";
            read(hareToTurtle[0], &hare, sizeof(hare));
            //read(godToHare[0], &turtle.dist, sizeof(turtle.dist));
            turtle.time++;
            turtle.dist+=1;
            write(turtleToHare[1], &turtle, sizeof(turtle));
        }
        // cout<<"Turtle Exited\n";
        return 0;
    }

    else if(godPid == 0){    //god process
        cout<<"god process: "<<getpid()<<endl;
        char status;
        sem_t *mutex = sem_open(terminalSemaphore, O_CREAT, 0644, 1);
        while(true){
            
        }
    }


    else{      //reporter process
        cout<<"reporter process: "<<getpid()<<endl;
        score s;
        sem_t *mutex = sem_open(terminalSemaphore, O_CREAT, 0644, 1);
        signal(SIGTERM, handle_sigterm);
        bool moseRecent = true;
        int nByte;
        while(true){
            // while(())
            // cout<<"reporter Scheduled\n";
            if((nByte = read(hareToReporter[0], &s, sizeof(s))) < 0 && !(moseRecent)){
                // sem_wait(mutex);
                cout<<"-----------------\n";
                cout<<"Hare Postion: "<<s.hareDist<<"\nTurtle Position: "<<s.turtleDist<<endl;
                moseRecent = true;
                // sem_post(mutex);
            }
            else if(nByte > 0){
                moseRecent = false;
            }
        }
        // signal()
    }
    // exit(0);
}
