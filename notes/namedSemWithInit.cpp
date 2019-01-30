#include<bits/stdc++.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdlib.h>

#ifndef O_CREAT
# define O_CREAT 0100
#endif

using namespace std;

const int SEM_INITIAL_VAL = 1;

/*	sem_trywait:
 * Return -1 if semaphore is locked
 * otherwise locks the semaphore
*/

char sem_name[] = "/sem_file";

int main(){
	//Open semaphore with initial value set to 1.
	sem_t *sem_mtx = sem_open(sem_name, O_CREAT, 0666, 0);
	
	//Decrease the value of semaphore to 0
	while(sem_trywait(sem_mtx) != -1){
	}
	
	//increase the value of semaphore to SEM_INITIAL_VAL
	for(int i = 0; i < SEM_INITIAL_VAL; i ++){
		sem_post(sem_mtx);
	}
	
	int status = sem_trywait(sem_mtx);
	if(status == -1){
		cout<<"Can not lock semaphore"<<endl;
	}
	else{
		cout<<"Successfully locked semaphore"<<endl;
	}
	
	char x;
	while(!(cin>>x)){
	
	}
	
	sem_unlink(sem_name);
	return 0;	
}
	
