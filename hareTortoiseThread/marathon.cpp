#include<bits/stdc++.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>

using namespace std; 

typedef struct{
    bool update;
    int hareDist;
    int turtoiseDist;
} updateData;

updateData newVal;
long const trackLength = 1e9;
long hareTime = 0, turtoiseTime = 0;
long hareDist = 0, turtoiseDist = 0;
long const hareStep = 3, turtoiseStep = 1;

long const minIntervalRequired = 100000;
long const minHareSleeps = 1000;

pthread_mutex_t hareDistMtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t turtoiseDistMtx = PTHREAD_MUTEX_INITIALIZER;


//Input to god 
void getNewVal(){
    newVal = {false, -1, -1};
    if(rand() % 10 >=8){    //update with probability 0.2
        newVal.update = true;
        newVal.hareDist = rand() % (trackLength);
        newVal.turtoiseDist = rand() % (trackLength);
    }
}

void *hareFunction( void *argc ){
    long sleepTime = 0;

    while( true ){
        if(sleepTime == 0){
            pthread_mutex_lock(&hareDistMtx);
            pthread_mutex_lock(&turtoiseDistMtx);
            if (hareDist >= trackLength){
                pthread_mutex_unlock(&turtoiseDistMtx);
                pthread_mutex_unlock(&hareDistMtx);
                break;
            }
            if( hareDist > turtoiseDist + ( rand() % 10 + minIntervalRequired)){
                sleepTime = rand() % minHareSleeps;
            }
            else{
                hareDist+=hareStep;
            }
            pthread_mutex_unlock(&turtoiseDistMtx);
            pthread_mutex_unlock(&hareDistMtx);
        }
        else {
            sleepTime--;
        }
        hareTime++;
    }

    pthread_exit( (void  *) 0 );
}

void *turtoiseFunction( void *argc ){
    while( true ){
        pthread_mutex_lock(&turtoiseDistMtx);
        if(turtoiseDist >= trackLength){
            pthread_mutex_unlock(&turtoiseDistMtx);
            break;
        }
        turtoiseDist+=turtoiseStep;
        pthread_mutex_unlock(&turtoiseDistMtx);
        turtoiseTime++;
    }

    pthread_exit( (void*) 0 );
}

void *reporterFunction( void *argc ){
    while( true ){
        if( turtoiseDist >= trackLength && hareDist >= trackLength ){
            break;
        }
        cout<<"\n---------------\n";
        cout<<"Hare Position: "<<hareDist<<endl<<"Turtoise Position: "<<turtoiseDist<<endl;
    }

    pthread_exit( (void*) 0 );
}

void *godFunction( void *argc ){
    while(true){
        getNewVal();
        pthread_mutex_lock(&hareDistMtx);
        pthread_mutex_lock(&turtoiseDistMtx);
        if( turtoiseDist >= trackLength && hareDist >= trackLength ){
            pthread_mutex_unlock(&turtoiseDistMtx);
            pthread_mutex_unlock(&hareDistMtx);
            break;
        }
        if(newVal.update){
            if(hareDist < trackLength) hareDist = newVal.hareDist;
            if(turtoiseDist < trackLength) turtoiseDist = newVal.turtoiseDist;
        }
        pthread_mutex_unlock(&turtoiseDistMtx);
        pthread_mutex_unlock(&hareDistMtx);
        usleep(500);
    }
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

    /*Reference for information purpose only*/
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
