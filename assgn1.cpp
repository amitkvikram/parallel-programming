#include<bits/stdc++.h>
#include<unistd.h>
#include <sys/wait.h>

using namespace std;
const int inf = 1e8;

typedef struct{
    int haredist;
    int turtleDist;
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
        pipe(godtoTurtle) < 0   ||
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
        while(true){
            if(hareTime == -1) read(masterHare[0], &hareTime, sizeof(hareTime));
            if(turtleTime == -1) read(masterTurtle[0], &turtleTime, sizeof(turtleTime));
            if(hareRunning && hareTime > 0){
                hareRunning = false;
            }
            if(turtleRunning && turtleTime > 0){
                turtleRunning = false;
            }

            if(!hareRunning && !turtleRunning){
                break;
            }
        }
        int status;
        kill(godPid, SIGTERM);
        kill(reporterPid, SIGTERM);
        /*Wait for Child Process*/
        for(int i = 0; i < 4; i ++){
            waitpid(pids[i], &status, 0);
        }

    }

    else if(harePid == 0){   //Hare Process
        cout<<"HareProces: "<<getpid()<<endl;  
        int hareDist = 0, hareTime = 0, turtleTime = -1, turtleDist = 0;
        write(hareToTurtle, &hareDist, sizeof(hareDist));   //say turtle to run
        while(hareDist < trackLength && turtleDist < trackLength){
            read(turtleToHare[0], &turtleDist, sizeof(turtleDist));
            if(haredist < trackLength){
                read(godToHare, &hareDist, sizeof(hareDist));
                hareTime ++;
                hareDist+=3;
            }
        }

        score s;
        s.hareTime = hareTime;
        s.turtleTime = turtleTime
        write(hareToMaster, )
    }

    else if(turtlePid == 0){  //turtle process
        cout<<"turtle process: "<<getpid()<<endl;
        int turtleDist = 0, time, tempDist;
        int time = 0;
        while(turtleDist < trackLength){
            int nByte = read(hareGod[0], &turtleDist, sizeof(turtleDist));
            if(nByte < 0){    //pipe is empty
                cout<<"pipe Empty\n";
            }
            turtleDist += 1;
            time++;
        }

        write(masterTurtle[1], &time, sizeof(time));
        return 0;
    }

    else if(godPid == 0){    //god process
        cout<<"god process: "<<getpid()<<endl;
    }

    else{      //reporter process
        cout<<"reporter process: "<<getpid()<<endl;

    }
    // exit(0);
}
