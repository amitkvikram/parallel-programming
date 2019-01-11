#include<bits/stdc++.h>
#include<unistd.h>
#include <sys/wait.h>

using namespace std;
const int inf = 1e8;

int main(){
    int trackLength = 1000, pid, nByte;
    int masterHare[2];   //materHare[0] for reading and masterHare[1] for writing
    int hareGod[2];
    int reporterHare[2];
    int reporterTurtle[2];
    pid_t harePid = -1, turtlePid = -1, godPid = -1, reporterPid = -1, masterPid= -1;
    
    masterPid = getpid();
    cout<<"Master Pid = "<<masterPid<<endl;

    //Pipes Creation
    if(pipe(masterHare) < 0){
        cout<<"Error in Creating pipe\n";
        return 0;
    }
    /*Pipes Creation End */

    /*Process Creation */
    if( getpid() == masterPid && (harePid = fork()) < 0){
        cout<<"Error in Hare Process Fork\n";
    }
    if(getpid() == masterPid && (turtlePid = fork()) < 0){
        cout<<"Error in Turtle Process Fork\n";
    }
    if(getpid() == masterPid && (godPid = fork()) < 0){
        cout<<"Error in God Process Fork\n";
    }
    if(getpid() == masterPid && (reporterPid = fork()) < 0){
        cout<<"Error in Reporter Process Fork\n";
    }
    /*Processes Created */

    if( (harePid & turtlePid & godPid & reporterPid) > 0){  //parent... 
        int status;
        cout<<"Parent Process: "<<"pid = "<<getpid()<<endl;
        cout<<"Parent Process: "<<"harePid turtlePid godPid reporterPid\n";
        cout<<"Parent Process: "<<harePid<<" "<<turtlePid<<" "<<godPid<<" "<<reporterPid<<endl;

        // waitpid(reporterPid, &status, WNOHANG);
        // signal(SIGCHLD, SIG_IGN);
        // int HareDist;
        // close(masterHare[1]);    //close write end of pipe
        // if( (nByte = read(masterHare[0], &HareDist, sizeof(int))) < 0 ){
        //     cout<<"Error while reading from pipe\n";
        // }

        // while(HareDist < inf){
        //     cout<<"Hare Distance = "<<HareDist<<endl;
        //     if( (nByte = read(masterHare[0], &HareDist, sizeof(int))) < 0 ){
        //         cout<<"Error while reading from pipe\n";
        //     }
        // }

        // cout<<"Hare Reached Destination\n";
    }

    else if(harePid == 0){   //Hare Process
        cout<<"HareProces: "<<getpid()<<endl;
        // sleep(2);
        // int HareDist = 0;
        // close(masterHare[0]);   //close read end of pipe
        // while(HareDist < trackLength){
        //     if(( nByte = write(masterHare[1], &HareDist, sizeof(int)) < 0)){
        //         cout<<"Error while writing to pipe\n";   
        //     }
        //     HareDist += 90;
        // }

        // if(( nByte = write(masterHare[1], &inf, sizeof(int)) < 0)){
        //     cout<<"Error while writing to pipe\n";   
        // }        
    }

    else if(turtlePid == 0){  //turtle process
        cout<<"turtle process: "<<getpid()<<endl;
    }

    else if(godPid == 0){    //god process
        cout<<"god process: "<<getpid()<<endl;
    }

    else{      //reporter process
        cout<<"reporter process: "<<getpid()<<endl;

    }
    // exit(0);
}
