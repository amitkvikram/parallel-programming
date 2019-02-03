#include<bits/stdc++.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>

using namespace std; 

long trackLength = 1e10;
long hareTime = 0, turtoiseTime = 0;
long hareDist = 0, turtoiseDist = 0;
long hareStep = 3, turtoiseStep = 2;

pthread_mutex_t terminalMutex = PTHREAD_MUTEX_INITIALIZER;   //Mutex for terminal ownership


void *hareFunction( void *argc ){
    long sleepTime = 0;

    while( hareDist < trackLength ){
        hareTime++;
        if( hareDist > turtoiseDist + ( rand() % 10 + 200000000 ) && sleepTime == 0){
            cout<<"Sleeping\n";
            sleepTime = rand() % 30 + 100000000;
        }

        if(sleepTime == 0) hareDist+=hareStep;
        else sleepTime--;

        //Sleep Thread with 0.1 probability
        // if(rand () % 100 < 10){
        //     usleep(100);
        // }
    }

    pthread_exit( (void *) 0 );
}

void *turtoiseFunction( void *argc ){
    while( turtoiseDist < trackLength ){
        turtoiseDist+=turtoiseStep;
        turtoiseTime++;

        //Sleep Thread with 0.1 probability
        // if(rand() % 100 < 10){
        //     usleep(100);
        // }
    }

    pthread_exit( (void*) 0 );
}

void *reporterFunction( void *argc ){
    while( turtoiseDist < trackLength || hareDist < trackLength ){
        pthread_mutex_lock(&terminalMutex);
        cout<<"\n---------------\n";
        cout<<"Hare Position: "<<hareDist<<endl<<"Turtoise Position: "<<turtoiseDist<<endl;
        pthread_mutex_unlock(&terminalMutex);
    }

    pthread_exit( (void*) 0 );
}

void *godFunction( void *argc ){

}

int createThread(pthread_t &tidp, void *(*fun_ptr)(void *)){
    if( pthread_create(&tidp, NULL, fun_ptr, NULL) != 0 ){
        cout<<"Error in Creating Thread\n";
        exit(EXIT_FAILURE);
    }

    return 0;
}

int main(){
    pthread_t tidp[4];

    srand (time(0));

    /*Reference for information*/
    pthread_t &hareThread = tidp[0], &turtoiseThread = tidp[1], 
                &reporterThread = tidp[2], &godThread = tidp[3];

    /*Initialize Thread*/
    createThread(tidp[0], hareFunction);
    createThread(tidp[1], turtoiseFunction);
    createThread(tidp[2], reporterFunction);
    createThread(tidp[3], godFunction);

    /*Join main thread with all other threads*/
    for(int i = 0; i < 4; i ++){
        if( pthread_join( tidp[i], NULL ) != 0 ){
            cout<<"Error in joining thread\n";
            exit(EXIT_FAILURE);
        }
    }

    /*Print Result of marathon */
    cout<<"HareTime: "<<hareTime<<" TurtoiseTime: "<<turtoiseTime<<endl;
    cout<<"Result: ";
    if(hareTime == turtoiseTime ){
        cout<<"Draw\n";
    }
    else if(hareTime > turtoiseTime){
        cout<<"Turtoise Wins\n";
    }
    else{
        cout<<"Hare Wins\n";
    }
}
