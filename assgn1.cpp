#include<bits/stdc++.h>
#include<unistd.h>
#include <sys/wait.h>

using namespace std;
const int inf = 1e8;

typedef struct{
    int hareTime;
    int turtleTime;
} result;

typedef struct {
    int hareDist;
    int turtleDist;
}godDecision;

typedef struct{
    int time;
    int dist;
} details;

int main(){
    int trackLength = 1000, pid, nByte;
    int hareToTurtle[2], turtleToHare[2];
    int godToTurtle[2], godToHare[2];
    int HareToReporter[2];
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
        pipe(HareToReporter) < 0||
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

    if( (harePid & turtlePid & godPid & reporterPid) > 0){  //parent... 
        int status;
        cout<<"Parent Process: "<<"pid = "<<getpid()<<endl;
        cout<<"Parent Process: "<<"harePid turtlePid godPid reporterPid\n";
        cout<<"Parent Process: "<<harePid<<" "<<turtlePid<<" "<<godPid<<" "<<reporterPid<<endl;
        int hareTime = -1, turtleTime = -1;
    }

    else if(harePid == 0){   //Hare Process
        cout<<"HareProces: "<<getpid()<<endl; 
        int sleepTime = 0;
        details hare = {0, 0}, turtle = {0, 0};
        write(hareToTurtle[1], &hare, sizeof(hare));   //say turtle to run
        while(hare.dist < trackLength && turtle.dist < trackLength){
            if(turtle.dist < trackLength)
                read(turtleToHare[0], &turtle, sizeof(turtle));
            if(hare.dist < trackLength){
                read(godToHare[0], &hare.dist, sizeof(hare.dist));
                if(hare.dist > turtle.dist + 40 && sleepTime == 0){
                    sleepTime = 60;
                }
                hare.time ++;
                if(sleepTime == 0) hare.dist+=3;
                else sleepTime--;
            }
            write(hareToTurtle[1], &hare, sizeof(hare));
        }

        result res = {hare.time, turtle.time};
        write(hareToMaster[1], &res, sizeof(res));
        return 0;
    }

    else if(turtlePid == 0){  //turtle process
        cout<<"turtle process: "<<getpid()<<endl;
        details hare = {0, 0}, turtle = {0, 0};
        while(turtle.dist < trackLength){
            read(hareToTurtle[0], &hare, sizeof(hare));
            read(godToHare[0], &turtle.dist, sizeof(turtle.dist));
            turtle.time++;
            turtle.dist+=1;
            write(turtleToHare[1], &turtle, sizeof(turtle));
        }
        return 0;
    }

    else if(godPid == 0){    //god process
        cout<<"god process: "<<getpid()<<endl;
        char status;
        while(true){
            if((cin>>status));
        }
    }

    else{      //reporter process
        cout<<"reporter process: "<<getpid()<<endl;

    }
    // exit(0);
}
